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

string solve(vector<i32>& precomputed);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<i32> precomputed;
    precomputed.reserve(1001);
    precomputed.emplace_back(0);
    for (i32 i = 1; i < 1001; i++) {
        precomputed.emplace_back(precomputed.back() ^ i);
    }
    i32 t;
    cin >> t;
    for (i32 i = 0; i < t; i++) {
        cout << solve(precomputed);
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve(vector<i32>& precomputed) {
    i32 m;
    cin >> m;
    i32 x = precomputed[m] ^ m;
    stringstream ss;
    ss << (x == 0 ? m : m - 1) << "\n";
    for (i32 i = 1; i <= m; i++) {
        if (i != x) {
            ss << i << " ";
        }
    }
    ss.seekp(-1, ss.cur);
    ss << "\n";
    return ss.str();
}