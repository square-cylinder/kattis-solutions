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
    i32 n, h;
    cin >> n >> h;
    vector<i32> obst_floor, obst_ceil;
    obst_floor.reserve(n/2);
    obst_ceil.reserve(n/2);
    for (i32 i = 0; i < n; i++) {
        i32 x;
        cin >> x;
        if (i % 2 == 0) {
            obst_floor.push_back(x);
        } else {
            obst_ceil.push_back(x);
        }
    }
    sort(obst_floor.begin(), obst_floor.end());
    sort(obst_ceil.begin(), obst_ceil.end());
    i32 n_floor = n / 2;
    i32 n_ceil = 0;
    i32 floor_index = 0, ceil_index = obst_ceil.size() - 1;
    vector<i32> sols;
    for (i32 i = 1; i <= h; i++) {
        while (floor_index < obst_floor.size() && obst_floor[floor_index] < i) {
            n_floor--;
            floor_index++;
        }
        while (ceil_index >= 0 && i > h - obst_ceil[ceil_index]) {
            n_ceil++;
            ceil_index--;
        }
        sols.emplace_back(n_floor + n_ceil);
    }
    sort(sols.begin(), sols.end());
    i32 best = sols[0];
    i32 count = 1;
    for(i32 i = 1; i < sols.size(); i++) {
        if (sols[i] == best) {
            count++;
        } else {
            break;
        }
    }
    stringstream out;
    out << best << " " << count;
    return out.str();
}