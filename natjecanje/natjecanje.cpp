#include <bits/stdc++.h>

//#define MULTIPLE_CASES

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
#ifdef MULTIPLE_CASES
i32 n;
cin >> n;
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n, s, r;
    cin >> n >> s >> r;
    vector<i32> k(n, 0);
    for (i32 i = 0; i < s; i++) {
        i32 x;
        cin >> x;
        k[x-1]--;
    }
    for (i32 i = 0; i < r; i++) {
        i32 x;
        cin >> x;
        k[x-1]++;
    }
    for (i32 i = 0; i < n; i++) {
        if (k[i] < 0) {
            if (i + 1 < n && k[i+1] > 0) {
                k[i+1]--;
                k[i]++;
            }
        } else if (k[i] > 0) {
            if (i + 1 < n && k[i+1] < 0) {
                k[i+1]++;
                k[i]--;
            }
        }
    }
    i32 t = 0;
    for (auto i : k) {
        if (i < 0) {
            t++;
        }
    }
    return to_string(t);
}
