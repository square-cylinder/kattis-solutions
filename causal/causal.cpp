#include <bits/stdc++.h>

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
    i32 num_cases;
    cin >> num_cases;
    for (i32 i = 0; i < num_cases; i++) {
        cout << "Case " << i + 1 << ": " << solve() << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

bool is_in_cone(i32 t, i32 x, pair<i32, i32> point) {
    i32 t_off = point.second - t;
    i32 x_off = point.first - x;
    return abs(x_off) <= t_off;
}

bool is_possible_with_t(i32 t, i32 m, const vector<pair<i32, i32>>& coords) {
    if (coords[0].second < t) return false;
    i32 cur_x = coords[0].first - t + coords[0].second;
    m--;
    for (i32 i = 1; i < coords.size(); i++) {
        if (!is_in_cone(t, cur_x, coords[i])) {
            m--;
            if (m < 0) return false;
            if (coords[i].second < t) return false;
            cur_x = coords[i].first - t + coords[i].second;
        }
    }
    return true;
}

string solve() {
    i32 n, m;
    cin >> n >> m;
    vector<pair<i32, i32>> coords;
    coords.reserve(n);
    for (i32 i = 0; i < n; i++) {
        i32 t, x;
        cin >> t >> x;
        coords.emplace_back(x, t);
    }
    std::sort(coords.begin(), coords.end(), 
        [](const pair<i32, i32>& a, const pair<i32, i32>& b) {
            return a.first + a.second < b.first + b.second;
        });

    i32 lo, hi;
    lo = -10000000;
    hi = 10000000;
    while (lo != hi) {
        i32 mid = (lo + hi + 1) / 2;
        if (is_possible_with_t(mid, m, coords)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return to_string(lo);
}