#include <bits/stdc++.h>

/* Don't want to type std:: everywhere */
using namespace std;

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
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

i32 dp[11][101][101] = {};
string solve() {
    for (i32 l = 1; l < 101; l++) {
        for (i32 h = l; h < 101; h++) {
            dp[1][l][h] = (l + h) * (h - l + 1) / 2;
        }
    }
    for (i32 k = 2; k < 11; k++) {
        for (i32 l = 100; l >= 0; l--) {
            for (i32 h = 100; h >= l; h--) {
                i32 best = INT_MAX;
                for (i32 x = l; x <= h; x++) {
                    best = min(best, x + max(dp[k - 1][l][x - 1], dp[k][x + 1][h]));
                }
                dp[k][l][h] = best;
            }
        }
    }

    i32 t;
    stringstream output;
    cin >> t;
    while (t--) {
        i32 k, m;
        cin >> k >> m;
        output << dp[k][1][m] << "\n";
        // solve it
    }
    return output.str();
}