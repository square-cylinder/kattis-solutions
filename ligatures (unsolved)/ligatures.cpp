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

constexpr i32 LUTSZ = 26 * 26;

string solve() {
    i32 n, q, k;
    string s;
    cin >> n >> q >> k >> s;
    vector<bool> ligs(LUTSZ * q, false);
    for (i32 i = 0; i < q; i++) {
        string t;
        cin >> t;
        for (i32 j = 0; j < k * 2; j += 2) {
            i32 index = (t[j] - 'a') * 26 + (t[j+1] - 'a') + i * LUTSZ;
            ligs[index] = true;
        }
    }

    stringstream ans;
    for (i32 qi = 0; qi < q; qi++) {
        i32 answer = 0;
        bool didnot = true;
        for (i32 i = 0; i < n-1; i++) {
            i32 index = (s[i] - 'a') * 26 + (s[i+1] - 'a');
            bool islig = ligs[index + qi * LUTSZ];
            answer += islig & didnot;
            didnot = !(didnot & islig);
        }
        ans << answer << '\n';
    }

    return ans.str();
}