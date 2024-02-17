#include <bits/stdc++.h>

/*
The most amount of sets can be found by just counting the strongly connected components within the
loose edges since those are the ones that have to be equal.

This can be done using Kosaraju's algorithm which runs in O(E + V)

Idea for finding least amount of sets:
1. Convert the graph to a new graph where we combine all
strongly components found for the upper bound because they
must be the same set.

When we combine two nodes we basically make a node which
has both nodes outgoing edges (excluding those to itself)

Now we should have a graph that contains no cycles which
we can use to identify the largest sets

2.
Find the nodes with no ingoing edges and set their number to be 0

For every numbered node a, b. If a > b, then a is a strict subset of b

3.
Now go through all nodes in graph to find their number with dfs postorder.
For a given node, find the maximum number from its loose parents
and from its strict parents. Its number is then max(max{loose},1+max{strict})

4.
The least number of sets needed should then be the largest number of the nodes + 1
*/

using namespace std;

struct ProblemInput {
    ProblemInput(int num_nodes) : num_nodes(num_nodes) {
        adj_loose.resize(num_nodes);
        adj_loose_back.resize(num_nodes);
        adj_strict.resize(num_nodes);
        adj_strict_back.resize(num_nodes);
    }

    void add_loose_edge(int from, int to) {
        adj_loose[from].emplace_back(to);
        adj_loose_back[to].emplace_back(from);
    }

    void add_strict_edge(int from, int to) {
        adj_strict[from].emplace_back(to);
        adj_strict_back[to].emplace_back(from);
    }

    int num_nodes;
    vector<vector<int>> adj_loose;
    vector<vector<int>> adj_loose_back;
    vector<vector<int>> adj_strict;
    vector<vector<int>> adj_strict_back;
};

int solve_lower_bound(const ProblemInput& problem, vector<vector<int>> sccs) {
    if (problem.adj_strict.empty()) {
        return 1;
    }

    vector<const vector<int>*> scc_mappings;
    scc_mappings.resize(problem.num_nodes);
    for (const auto& v : sccs) {
        for (int i : v) {
            scc_mappings[i] = &v;
        }
    }

    // Map nodes
    vector<int> mapping;
    int num_new_nodes = 0;
    mapping.resize(problem.num_nodes, -1);
    for (int i = 0; i < problem.num_nodes; i++) {
        if (mapping[i] != -1)
            continue;
        const int new_map = num_new_nodes++;
        for (auto x : *scc_mappings[i]) {
            mapping[x] = new_map;
        }
    }

    // Map edges
    vector<vector<int>> edges_sb, edges_sf, edges_lb, edges_lf;
    edges_sb.resize(num_new_nodes);
    edges_sf.resize(num_new_nodes);
    edges_lb.resize(num_new_nodes);
    edges_lf.resize(num_new_nodes);
    for (int i = 0 ; i < problem.num_nodes; i++) {
        int cur = mapping.at(i);
        assert(cur >= 0 && cur < num_new_nodes);
        for (auto edge : problem.adj_loose[i]) {
            const int mapped = mapping[edge];
            if (cur == mapped)
                continue;
            edges_lf.at(cur).emplace_back(mapped);
        }
        for (auto edge : problem.adj_loose_back[i]) {
            const int mapped = mapping[edge];
            if (cur == mapped)
                continue;
            edges_lb.at(cur).emplace_back(mapped);
        }
        for (auto edge : problem.adj_strict[i]) {
            const int mapped = mapping[edge];
            if (cur == mapped)
                continue;
            edges_sf.at(cur).emplace_back(mapped);
        }
        for (auto edge : problem.adj_strict_back[i]) {
            const int mapped = mapping[edge];
            if (cur == mapped)
                continue;
            edges_sb.at(cur).emplace_back(mapped);
        }
    }

    vector<int> numberings;
    numberings.resize(num_new_nodes, -1);
    bool found_something = false;
    for (int i = 0; i < num_new_nodes; i++) {
        if (edges_lb[i].empty() && edges_sb[i].empty()) {
            numberings[i] = 0;
            found_something = true;
        }
    }
    assert(found_something);

    int biggest_number = 0;
    for (int i = 0; i < num_new_nodes; i++) {
        if (numberings[i] != -1) {
            continue;
        }
        vector<pair<int, bool>> stack;
        stack.emplace_back(i, true);
        while (!stack.empty()) {
            auto [cur, first_visit] = stack.back();
            if (numberings[cur] != -1) {
                stack.pop_back();
                continue;
            }
            if (first_visit) {
                stack.back().second = false;
                for (auto edge : edges_lb[cur]) {
                    if (numberings[i] == -1)
                        stack.emplace_back(edge, true);
                }
                for (auto edge : edges_sb[cur]) {
                    if (numberings[i] == -1)
                        stack.emplace_back(edge, true);
                }
                continue;
            }
            int max_strict = -1;
            int max_loose = 0;
            for (auto edge : edges_lb[cur]) {
                assert(numberings[edge] != -1);
                max_loose = max(numberings[edge], max_loose);
            }
            for (auto edge : edges_sb[cur]) {
                assert(numberings[edge] != -1);
                max_strict = max(numberings[edge], max_strict);
            }

            numberings[cur] = max(max_loose, max_strict + 1);
            biggest_number = max(biggest_number, numberings[cur]);

            stack.pop_back();
        }
    }

    return biggest_number + 1;
}

vector<vector<int>> solve_upper_bound(const ProblemInput& problem) {
    vector<bool> vis;
    vector<bool> revvis;
    vis.resize(problem.num_nodes, false);
    revvis.resize(problem.num_nodes, false);
    vector<vector<int>> sccs;
    for (int start = 0; start < problem.num_nodes; start++) {
        if (vis[start])
            continue;
        vector<int> res;
        vector<int> dfs;
        vector<int> postorder;
        dfs.emplace_back(start);
        while (!dfs.empty()) {
            int cur = dfs.back();
            vis[cur] = true;
            bool visitedthings = false;
            for (auto& nb : problem.adj_loose[cur]) {
                if (vis[nb])
                    continue;
                visitedthings = true;
                dfs.emplace_back(nb);
            }
            if (!visitedthings) {
                postorder.emplace_back(cur);
                dfs.pop_back();
            }
        }
        while (!postorder.empty()) {
            int revstart = postorder.back();
            postorder.pop_back();
            if (revvis[revstart])
                continue;
            sccs.emplace_back();
            dfs.emplace_back(revstart);
            while (!dfs.empty()) {
                int cur = dfs.back();
                sccs.back().emplace_back(cur);
                revvis[cur] = true;
                dfs.pop_back();
                for (auto& nb : problem.adj_loose_back[cur]) {
                    if (!vis[nb] || revvis[nb])
                        continue;
                    dfs.emplace_back(nb);
                }
            }
        }
    }
    return sccs;
}

int translate(unordered_map<string, int>& translations, string s) {
    if (translations.find(s) == translations.end()) {
        translations.emplace(s, translations.size());
    }
    return translations[s];
}

pair<int, int> read_edge(unordered_map<string, int>& translations) {
    string as, bs;
    cin >> as >> bs;
    int a, b;
    a = translate(translations, as);
    b = translate(translations, bs);
    return make_pair(a, b);
}

int main(int argc, char **argv) {
    int m, n;
    cin >> m >> n;

    unordered_map<string, int> translations;
    vector<pair<int, int>> loose_edges;
    vector<pair<int, int>> strict_edges;
    loose_edges.reserve(m);
    strict_edges.reserve(n);
    for (int i = 0; i < m; i++) {
        loose_edges.emplace_back(read_edge(translations));
    }
    for (int i = 0; i < n; i++) {
        strict_edges.emplace_back(read_edge(translations));
    }

    ProblemInput problem(translations.size());

    for (auto [from, to] : loose_edges) {
        problem.add_loose_edge(from, to);
    }
    for (auto [from, to] : strict_edges) {
        problem.add_strict_edge(from, to);
    }

    int lower_bound;
    vector<vector<int>> sccs;
    sccs = solve_upper_bound(problem);
    lower_bound = solve_lower_bound(problem, sccs);

    cout << lower_bound << " " << sccs.size() << "\n";
}