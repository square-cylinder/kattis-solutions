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

i32 save(i32 x) {
    i32 m10 = x % 10;
    if (m10 < 5) return m10;
    return m10 - 10;
}

string solve() {
    i32 n, d;
    cin >> n >> d;
    vector<i32> v = input_vec<i32>(n);
    vector<i32> ps(n + 1);
    for (i32 i = 0; i < n; i++) {
        ps[i+1] = ps[i] + v[i];
    }
    i32 dp[2001] = {};
    for (i32 i = 0; i <= n; i++) {
        dp[i] = save(ps[n] - ps[i]);
    }
    for (i32 i = 0; i < d; i++) {
        for(i32 j = 0; j < n; j++) {
            for (i32 k = j + 1; k <= n; k++) {
                dp[j] = max(dp[j], save(ps[k] - ps[j]) + dp[k]);
            }
        }
    }
    return to_string(ps[n] - dp[0]);
}