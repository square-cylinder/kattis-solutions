#include <bits/stdc++.h>

/*
 * We can recognize that in order to assign one edge to every
 * node we have to have as many connected nodes as we have
 * edges for every subgraph. This means every subgraph will
 * be a tree with exactly one cycle, so we can just label
 * one edge of the cycle first and then label everything else
 * in the remaining tree pretty easily.
 *
 * With this in mind our algorithm becomes:
 * 1. Identify all the subgraphs
 * 2. Run the solver for everysubgraph as:
 *    - identify the cycle
 *    - remove one edge from the cycle
 *    - do a dfs from one of the nodes of that edge
 *    - label every edge to the new node that we arrive to
 * 3. Combine the results into one table and output
*/

using namespace std;
using intint = pair<int, int>;

class SubGraph {
    public:
    SubGraph(const unordered_set<int>& nodes, 
             const vector<vector<int>>& adj,
             optional<intint> duplicate_edge)
             : nodes(nodes), adjacent(adj), dup(duplicate_edge) {}

    void label_edges(vector<intint>& output) {
        vector<intint> dfs2;
        int youmaynot;
        if (dup.has_value()) {
            auto [owner, other] = dup.value();
            output.emplace_back(owner, other);
            youmaynot = owner;
            for (int rootnb : adjacent[owner]) {
                dfs2.emplace_back(owner, rootnb);
            }
        } else {
            unordered_set<int> vis;
            int start = *nodes.begin();
            vis.emplace(start);
            vector<intint> dfs1;
            dfs1.emplace_back(-1, start);
            while (!dfs1.empty()) {
                auto [prev, cur] = dfs1.back();
                dfs1.pop_back();
                for (int nb : adjacent[cur]) {
                    if (prev == nb) 
                        continue;
                    if (vis.find(nb) != vis.end()) {
                        output.emplace_back(cur, nb);
                        youmaynot = cur;
                        for (int rootnb : adjacent[cur]) {
                            if (rootnb != nb)
                                dfs2.emplace_back(cur, rootnb);
                        }
                        goto END_DFS1;
                    }
                    dfs1.emplace_back(cur, nb);
                    vis.emplace(nb);
                }
            }
        }

        END_DFS1:
        while (!dfs2.empty()) {
            auto [prev, cur] = dfs2.back();
            output.emplace_back(cur, prev);
            dfs2.pop_back();

            for (int nb : adjacent[cur]) {
                if (nb == prev || nb == youmaynot)
                    continue;
                dfs2.emplace_back(cur, nb);
            }
        }
    }

    private:
    const unordered_set<int>& nodes;
    const vector<vector<int>>& adjacent;
    optional<intint> dup;
};

unordered_set<int> find_subgraph(const vector<vector<int>>& adjacent, int start) {
    unordered_set<int> found;
    vector<int> dfs;
    dfs.emplace_back(start);
    found.emplace(start);
    while (!dfs.empty()) {
        int x = dfs.back();
        dfs.pop_back();
        for (auto y : adjacent[x]) {
            if (found.find(y) == found.end()) {
                dfs.emplace_back(y);
                found.emplace(y);
            }
        }
    }
    return found;
}

int main(int argc, char** argv) {
    int n;
    cin >> n;
    set<intint> setofedges;
    vector<vector<int>> edges;
    edges.resize(n);
    vector<intint> answer;
    vector<intint> duplicate_edges;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        auto e = make_pair(min(a,b), max(a,b));
        if (setofedges.find(e) == setofedges.end()) {
            edges[a].emplace_back(b);
            edges[b].emplace_back(a);
            setofedges.emplace(e);
        } else {
            duplicate_edges.emplace_back(a,b);
        }
    }

    vector<bool> done;
    done.resize(n, false);
    for (int i = 0; i < n; i++) {
        if (done[i])
            continue;
        unordered_set<int> nodes = find_subgraph(edges, i);
        optional<intint> dup = {};
        for (auto [a,b] : duplicate_edges) {
            if (nodes.find(a) != nodes.end()) {
                dup = make_pair(a, b);
                break;
            }
        }
        SubGraph sg(nodes, edges, dup);
        sg.label_edges(answer);
        for (int thing : nodes) {
            done[thing] = true;
        }
    }

    for (auto [a,b] : answer) {
        cout << a+1 << " " << b+1 << "\n";
    }

    return 0;
}