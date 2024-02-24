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
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n;
    vector<i32> numbers = input_vec<i32>(n);
}