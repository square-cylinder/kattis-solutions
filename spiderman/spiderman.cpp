#include <bits/stdc++.h>
#include <iterator>

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
    i32 n;
    cin >> n;
    for (i32 i = 0; i < n; i++) 
        cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

constexpr i32 MAX_HEIGHT = 1000;
constexpr i32 MAX_SESS = 40;

string solve() {
    i32 n;
    cin >> n;
    i32 vals[40];
    for (i32 i = 0; i < n; i++) {
        cin >> vals[i];
    }
    i32 table[MAX_SESS+1][MAX_HEIGHT+1];
    i32 deltas[MAX_SESS+1][MAX_HEIGHT+1];
    for (i32 i = 0; i <= MAX_SESS; i++)
        memset(table[i], -1, sizeof(table[i]));
    table[0][0] = 0;
    for (i32 i = 0; i < n; i++) {
        for (i32 j = 0; j <= MAX_HEIGHT / 2; j++) {
            if (table[i][j] != -1) {
                const i32 this_path_worst = table[i][j];
                const i32 d_i = n-1 - i;

                const i32 climbed_up = j - vals[d_i];
                if (climbed_up >= 0 && (table[i+1][climbed_up] > this_path_worst || table[i+1][climbed_up] == -1)) {
                    table[i+1][climbed_up] = this_path_worst;
                    deltas[i+1][climbed_up] = vals[d_i];
                }

                const i32 climbed_down = j + vals[d_i];
                const i32 cost = max(climbed_down, this_path_worst);
                assert(climbed_down <= MAX_HEIGHT);
                if (table[i+1][climbed_down] > cost || table[i+1][climbed_down] == -1) {
                    table[i+1][climbed_down] = cost;
                    deltas[i+1][climbed_down] = -vals[d_i];
                }
            }
        }
    }

    if (table[n][0] == -1)
        return "IMPOSSIBLE";

    
    stringstream path;
    i32 cur_height = 0;
    for (i32 i = n; i > 0; i--) {
        path << (deltas[i][cur_height] > 0 ? "U" : "D");
        cur_height += deltas[i][cur_height];
    }

    return path.str();
}