#include <bits/stdc++.h>
#include <charconv>

/*
We can solve this problem by first finding all the subgraphs,
using union-find, and then finding the maximal shortest path 
(radius) in each subgraph by taking its diameter divided by two.

The diameter of a tree can easily be found using two dfs's. First
one from any node to the farthest node, and then another from that
node to the farthest node. The distance between the two farthest nodes
is the diameter of the tree.

After this we will have all the maximal shortest paths in each subgraph.
We can connect the network by taking the worst case network in the middle,
and then connecting all the other networks around the worst case networks.
This means our worst case path is going to be the worst case path in the
largest subgraph combined with the worst case path in the second largest
subgraph or the sum of the worst case paths in the second and third largest
subgraphs plus 2.

Another edge case to consider is when the shortest path is in a single
subgraph. In this case we can just take the worst case path in the subgraph
which is the diameter of the subgraph.

The time complexity of this solution is O(n) for the union-find, O(n) for
the diameter finding, and O(n) for the worst case path finding. This means
the total time complexity is O(n).
*/

/* Common std library items */
using std::cin;
using std::cout;
using std::cerr;

using std::string;
using std::vector;
using std::pair;
using std::tuple;
using std::optional;
using std::map;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::queue;

using std::max;
using std::min;
using std::to_string;
using std::sqrt;
using std::hypot;

/* Less verbose names for common types */
#define umap unordered_map
#define uset unordered_set

/* More convenient integer types */
using i8  = int8_t;
using u8  = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

/* Introduce a less insane way to check for an element in a set or map */
template<class T1, class T2>
bool contains(const T1& c, T2 e) { return c.find(e) != c.end(); }
/* Convenient function to read a list of things */
template<class T>
vector<T> input_vec(int length) {
    vector<T> v; v.reserve(length);
    for (int i = 0; i < length; i++) {
        T x;
        cin >> x;
        v.emplace_back(x);
    }
    return v;
}

class UnionFind {
private:
    mutable vector<i32> parents;
    vector<i32> sizes;
public:
    UnionFind(i32 n) : parents(n, -1), sizes(n, 1) {}

    i32 find(i32 x) const {
        if (parents[x] < 0) return x;
        vector<i32> path;
        while (parents[x] >= 0) {
            path.push_back(x);
            x = parents[x];
        }
        const i32 parent = x;
        for (i32 node : path) {
            parents[node] = parent;
        }
        return parent;
    }

    void join(i32 x, i32 y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sizes[x] < sizes[y]) {
            parents[x] = y;
            sizes[y] = sizes[x];
        } else {
            parents[y] = x;
            sizes[x] += sizes[y];
        }
    }
};

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

pair<i32, i32> find_furthest_node(const vector<vector<i32>>& adj, i32 start) {
    vector<tuple<i32,i32, i32>> dfs;
    i32 greatest_dist = 0;
    i32 greatest_node = start;
    dfs.emplace_back(start, -1, 0);
    while (!dfs.empty()) {
        auto [cur, prev, distance] = dfs.back();
        dfs.pop_back();
        if (distance > greatest_dist) {
            greatest_dist = distance;
            greatest_node = cur;
        }
        for (auto nb : adj[cur]) {
            if (nb == prev)
                continue;
            dfs.emplace_back(nb, cur, distance + 1);
        }
    }
    return {greatest_node, greatest_dist};
}

i32 find_diameter(const vector<vector<i32>>& adj, i32 start) {
    start = find_furthest_node(adj, start).first;
    return find_furthest_node(adj, start).second;
}

string solve() {
    i32 num_nodes, num_edges;
    cin >> num_nodes >> num_edges;
    UnionFind uf(num_nodes);
    vector<vector<i32>> adj(num_nodes);
    adj.resize(num_nodes);
    for (int i = 0; i < num_edges; i++) {
        i32 a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        uf.join(a, b);
    }
    uset<i32> done;
    i32 worst_total = 0;
    i32 absoluteworst = 0;
    i32 secondworst = 0;
    i32 thirdworst = 0;
    i32 num_subgraphs = 0;
    for (i32 i = 0; i < num_nodes; i++) {
        if (contains(done, uf.find(i)))
            continue;
        num_subgraphs++;
        done.emplace(uf.find(i));
        const i32 diameter = find_diameter(adj, i);
        const i32 radius = (diameter + 1) / 2;
        worst_total = max(worst_total, diameter);
        if (radius > absoluteworst) {
            thirdworst = secondworst;
            secondworst = absoluteworst;
            absoluteworst = radius;
        } else if (radius > secondworst) {
            thirdworst = secondworst;
            secondworst = radius;
        } else if (radius > thirdworst) {
            thirdworst = radius;
        }
    }
    if (num_subgraphs > 1)
        worst_total = max(worst_total, absoluteworst + secondworst + 1);
    if (num_subgraphs > 2)
        worst_total = max(worst_total, secondworst + thirdworst + 2);

    return to_string(worst_total);
}