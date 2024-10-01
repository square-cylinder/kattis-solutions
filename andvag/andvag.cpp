#include <bits/stdc++.h>
#include <memory>
#include <unordered_map>

/* Common std library items */
using std::cin;
using std::cout;
using std::cerr;

using std::string;
using std::stringstream;
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
using std::abs;
using std::make_pair;


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

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n_ponds, n_channels, n_queries;
    cin >> n_ponds >> n_channels >> n_queries;
    vector<vector<pair<i32, u32>>> adj(n_ponds);
    for (i32 i = 0; i < n_channels; i++) {
        i32 a, b;
        u32 cleansing_mask;
        cin >> a >> b >> cleansing_mask;
        a--; b--;
        adj[a].emplace_back(b, cleansing_mask);
        adj[b].emplace_back(a, cleansing_mask);
    }
    umap<i32, pair<std::shared_ptr<uset<i32>>, u32>> pond_info;
    for (i32 start = 0; start < n_ponds; start++) {
        if (contains(pond_info, start)) continue;
        queue<i32> q;
        q.push(start);
        std::shared_ptr<uset<i32>> visited = std::make_shared<uset<i32>>();
        visited->insert(start);
        u32 cleanse = 0;
        while (!q.empty()) {
            i32 cur = q.front();
            q.pop();
            for (auto&[next, mask] : adj[cur]) {
                cleanse |= mask;
                if (visited->find(next) == visited->end())  {
                    visited->insert(next);
                    q.push(next);
                }
            }
        }
        for (auto& pond : *visited) {
            pond_info[pond] = {visited, cleanse};
        }
    }
    stringstream ss;
    while (n_queries--) {
        i32 a, b;
        cin >> a >> b;
        a--; b--;
        if (pond_info[a].first->find(b) != pond_info[a].first->end()) {
            i32 count = 0;
            u32 mask = pond_info[a].second;
            for (u32 i = 1; i != 0; i <<= 1) {
                count += (mask & i) != 0;
            }
            ss << count << "\n";
        } else {
            ss << "-1\n";
        }
    }

    return ss.str();
}