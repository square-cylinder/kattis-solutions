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
    i32 num_rows, num_cols;
    cin >> num_rows >> num_cols;
    vector<string> grid = input_vec<string>(num_rows);

    vector<vector<int>> time_req(num_rows, vector<int>(num_cols, -1));
    queue<pair<i32, i32>> q;
    q.emplace(0, 0);
    time_req[0][0] = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        i32 nexttime = time_req[r][c] + 1;
        if (r == num_rows - 1) {
            return to_string(nexttime);
        }
        // Wait
        i32 stillcol = c == 0 ? num_cols - 1 : c - 1;
        if (grid[r][stillcol] != 'M') {
            if (time_req[r][stillcol] == -1) {
                time_req[r][stillcol] = nexttime;
                q.emplace(r, stillcol);
            }
            // Move left (will only be possible if waiting is possible)
            i32 leftcol = stillcol == 0 ? num_cols - 1 : stillcol - 1;
            if (time_req[r][leftcol] == -1 && grid[r][leftcol] != 'M') {
                time_req[r][leftcol] = nexttime;
                q.emplace(r, leftcol);
            }
        }
        // Move up
        if (r > 0 && time_req[r-1][stillcol] == -1 && grid[r-1][stillcol] != 'M' && grid[r-1][c] != 'M') {
            time_req[r-1][stillcol] = nexttime;
            q.emplace(r-1, stillcol);
        }
        // Move down
        if (time_req[r+1][stillcol] == -1 && grid[r+1][stillcol] != 'M' && grid[r+1][c] != 'M') {
            time_req[r+1][stillcol] = nexttime;
            q.emplace(r+1, stillcol);
        }
    }

    return "-1";
}