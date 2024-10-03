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
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 l, k, s;
    stringstream ss;
    string str;
    getline(cin, str);
    ss << str;
    ss >> l >> k >> s;
    vector<umap<i32, i32>> laps(k);
    while (l--) {
        getline(cin, str);
        ss.clear();
        ss << str;
        i32 contestant;
        ss >> contestant;
        ss >> str;
        i32 minute = (str[0] - '0') * 10 + (str[1] - '0');
        i32 second = (str[3] - '0') * 10 + (str[4] - '0');
        i32 tot_time = minute * 60 + second;
        i32 lap = 0;
        while (lap < laps.size() && contains(laps[lap], contestant)) {
            lap++;
        }
        if (lap != 0) {
            i32 prev_lap = laps[lap - 1][contestant];
            tot_time += prev_lap;
        }
        laps[lap][contestant] = tot_time;
    }
    vector<pair<i32, i32>> results;
    for (auto&[k, v] : laps[k - 1]) {
        results.emplace_back(v, k);
    }
    sort(results.begin(), results.end());
    stringstream out;
    for (auto&[time, contestant] : results) {
        out << contestant << "\n";
    }
    return out.str();
}