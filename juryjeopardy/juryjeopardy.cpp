#include <bits/stdc++.h>

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
cout << n << "\n";
while(n--)
#endif
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

// dx dy right up left down
pair<i32, i32> delta[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

string solve() {
    string input;
    cin >> input;
    set<pair<i32, i32>> vis;
    i32 x = 0, y = 0, d = 0;
    i32 min_y = 0, max_x = 0, max_y = 0;
    for (char c : input) {
        switch (c) {
        case 'F':
            break;
        case 'R':
            d = (d + 3) % 4;
            break;
        case 'L':
            d = (d + 1) % 4;
            break;
        case 'B':
            d = (d + 2) % 4;
            break;
        default:
            assert(false);
        }
        x += delta[d].first;
        y += delta[d].second;
        max_x = max(max_x, x);
        min_y = min(min_y, y);
        max_y = max(max_y, y);
        vis.emplace(x, y);
    }
    assert(x == 0 && y == 0);
    i32 width = max_x + 2;
    i32 height = max_y - min_y + 3;
    stringstream out;
    out << height << " " << width << "\n";
    out << string(width, '#') << "\n";
    for (i32 i = min_y; i < max_y + 1; i++) {
        for (i32 j = 0; j < max_x + 2; j++) {
            out << (vis.count({j, max_y - (i - min_y)}) ? '.' : '#');
        }
        out << "\n";
    }
    out << string(width, '#') << "\n";
    return out.str();
}
