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

bool in_range(i32 x1, i32 y1, i32 r, i32 x2, i32 y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) <= r * r;
}

string solve() {
    i32 l, w, n, r;
    cin >> l >> w >> n >> r;
    r *= 2;
    vector<pair<i32, i32>> cranes;
    for (i32 i = 0; i < n; i++) {
        i32 x, y;
        cin >> x >> y;
        x *= 2;
        y *= 2;
        cranes.emplace_back(x, y);
    }
    for (i32 pick = 1; pick <= min(4, n); pick++) {
        vector<bool> picked(n, false);
        fill(picked.end() - pick, picked.end(), true);
        do {
            bool walls[4] = {};
            for (i32 i = 0; i < n; i++) {
                if (picked[i]) {
                    i32 x = cranes[i].first;
                    i32 y = cranes[i].second;
                    if (in_range(x, y, r, -l, 0)) walls[0] = true;
                    if (in_range(x, y, r, l, 0)) walls[1] = true;
                    if (in_range(x, y, r, 0, -w)) walls[2] = true;
                    if (in_range(x, y, r, 0, w)) walls[3] = true;
                }
            }
            if (walls[0] && walls[1] && walls[2] && walls[3]) {
                return to_string(pick);
            }
        } while (next_permutation(picked.begin(), picked.end()));
    }
    return "Impossible";
}
