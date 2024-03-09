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
    i32 n, k;
    cin >> n >> k;
    map<i32, i32> entries;
    map<i32, i32> exits;
    for (i32 i = 0; i < n; i++) {
        i32 a, b;
        cin >> a >> b;
        entries[a]++;
        exits[b+1]++;
    }
    i32 best = 0;
    i32 count = 0;
    auto from = exits.begin();
    auto to = entries.begin();
    for (; to != entries.end(); to++) {
        i32 passed = to->first - from->first + 1;
        while (passed > k) {
            count -= from->second;
            from++;
            passed = to->first - from->first;
        } 
        count += to->second;
        if (count > best) best = count;
    }
    return to_string(best);
}