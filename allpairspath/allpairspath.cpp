#include <bits/stdc++.h>

/* Common std library items */
using namespace std;


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

string solve(i32 n, i32 m, i32 q);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n, m, q;
    while (cin >> n >> m >> q) {
        if (n == 0 && m == 0 && q == 0) {
            break;
        }
        cout << solve(n, m, q) << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

vector<i32> bellmanford(i32 n, vector<vector<pair<i32, i32>>> &adjacent, i32 start) {
    vector<i32> dist(n, INT_MAX);
    dist[start] = 0;
    for (i32 i = 0; i < n - 1; i++) {
        for (i32 u = 0; u < n; u++) {
            for (auto [v, w] : adjacent[u]) {
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    for (i32 i = 0; i < n - 1; i++) {
        for (i32 u = 0; u < n; u++) {
            for (auto [v, w] : adjacent[u]) {
                if (dist[u] != INT_MAX && (dist[u] + w < dist[v] || dist[u] == INT_MIN)) {
                    dist[v] = INT_MIN;
                }
            }
        }
    }
    return dist;
}

string solve(i32 n, i32 m, i32 q) {
    vector<vector<pair<i32, i32>>> adjacent(n);
    for (i32 i = 0; i < m; i++) {
        i32 u, v, w;
        cin >> u >> v >> w;
        adjacent[u].emplace_back(v, w);
    }
    vector<vector<i32>> distances(n);
    for (i32 i = 0; i < n; i++) {
        distances[i] = bellmanford(n, adjacent, i);
    }
    stringstream ans;
    for (i32 i = 0; i < q; i++) {
        i32 u, v;
        cin >> u >> v;
        if (distances[u][v] == INT_MAX) {
            ans << "Impossible\n";
        } else if (distances[u][v] == INT_MIN) {
            ans << "-Infinity\n";
        } else {
            ans << distances[u][v] << "\n";
        }
    }
    return ans.str();
}