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
    string ipt;
    cin >> ipt;
    vector<i32> as, bs, cs;
    for (i32 i = 0; i < ipt.size(); i++) {
        switch (ipt[i]) {
            case 'A': as.emplace_back(i); break;
            case 'B': bs.emplace_back(i); break;
            case 'C': cs.emplace_back(i); break;
            default: assert(false);
        }
    }
    assert(as.size() == bs.size() && bs.size() == cs.size());
    vector<i32> thing(ipt.size() + 1, 0);
    for (i32 i = 0; i < as.size(); i++) {
        i32 m = min(as[i], min(bs[i], cs[i]));
        i32 M = max(as[i], max(bs[i], cs[i]));
        thing[m]++;
        thing[M + 1]--;
    }
    i32 maxim = 0;
    i32 sum = 0;
    for (i32 i = 0; i < ipt.size(); i++) {
        sum += thing[i];
        maxim = max(maxim, sum);
    }
    return to_string(maxim);
}