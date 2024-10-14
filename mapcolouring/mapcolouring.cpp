#include <bits/stdc++.h>
#include <climits>

#define MULTIPLE_CASES

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

vector<vector<u64>> borders;

u64 extract_color(u64 coloring, u64 country) {
    return (coloring & (3uLL << (2*country))) >> (2*country);
}

u64 color(u64 at, u64 coloring, u64 num_colors) {
    if (at == borders.size()) {
        return coloring;
    }
    for (u64 i = 0; i < num_colors; i++) {
        bool yes = true;
        for (u64 c : borders[at]) {
            if (c >= at) continue;
            u64 ccol = extract_color(coloring, c);
            if (ccol == i) {
                yes = false;
                break;
            }
        }
        if (yes) {
            u64 bruh = color(at + 1, coloring | (i << (2*at)), num_colors);
            if (bruh != ULLONG_MAX)
                return bruh;
        }
    }
    return ULLONG_MAX;
}

string solve() {
    i32 c, b;
    cin >> c >> b;
    borders = vector<vector<u64>>(c);
    for (i32 i = 0; i < b; i++) {
        u64 c1, c2;
        cin >> c1 >> c2;
        borders[c1].emplace_back(c2);
        borders[c2].emplace_back(c1);
    }
    for (u64 i = 1; i <= 4; i++) {
        u64 coloring = color(0, 0, i);
        if (coloring != ULLONG_MAX) {
            return to_string(i);
        }
    }
    return "many";
}
