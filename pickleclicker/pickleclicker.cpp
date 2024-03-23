#include <bits/stdc++.h>
#include <string>

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
    i32 n, t;
    cin >> n >> t;
    pair<i32,i32> buildings[6];
    for (i32 i = 0; i < n; i++) {
        i32 p, c;
        cin >> p >> c;
        buildings[i] = {c, p};
    }
    for (i32 i = n; i < 6; i++) {
        buildings[i] = {INT_MAX, 0};
    }
    vector<i32> v1, v2;
    v1.resize(t+1, 0);
    v2.resize(t+1, 0);
    vector<i32>& cur = v1;
    vector<i32>& next = v2;

    cur[0] = buildings[0].second;
    i32 time;
    for (time = 0 ;; time++) {
        for (i32 i = t; i >= 0; i--) {
            if (cur[i] == 0) continue;
            if (i + cur[i] >= t) {
                return to_string(time+1);
            }
            next[i+cur[i]] = max(next[i+cur[i]], cur[i]);
            for (i32 j = 0; j < 6; j++) {
                auto [c, p] = buildings[j];
                if (c <= i) {
                    i32 nextprofit = cur[i] + p;
                    i32 nextmoney = i - c + nextprofit;
                    next[nextmoney] = max(next[nextmoney], nextprofit);
                }
            }
        }
        swap(cur, next);
    }
}