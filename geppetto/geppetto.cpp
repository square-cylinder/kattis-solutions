#include <bits/stdc++.h>
#include <string>

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
    i32 n, m;
    cin >> n >> m;
    vector<i32> restrictions;
    for (i32 i = 0; i < m; i++) {
        i32 a, b;
        cin >> a >> b;
        a--; b--;
        restrictions.emplace_back((1 << a) | (1 << b));
    }
    i32 count = 0;
    for (i32 pizza = 0; pizza < (1 << n); pizza++) {
        bool doable = true;
        for (i32 r : restrictions) {
            if ((pizza & r) == r) {
                doable = false;
                break;
            }
        }
        if (doable) count++;
    }
    return to_string(count);
}
