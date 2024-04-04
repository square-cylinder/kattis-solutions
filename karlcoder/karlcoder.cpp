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

void solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

i64 guess(i64 x) {
    cout << "buf[" << x << "]" << std::endl;
    i64 ans;
    cin >> ans;
    return ans;
}

void solve() {
    i64 hi = 1;
    i64 ans;
    i64 lo;
    do {
        lo = hi;
        hi *= 2;
        ans = guess(hi);
    } while (ans != 0);
    while (lo < hi) { // l-----+++++h
        i64 mid = (lo + hi) / 2;
        ans = guess(mid);
        if (ans != 0) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    cout << "strlen(buf) = " << lo << std::endl;
}