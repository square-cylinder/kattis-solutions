#include <bits/stdc++.h>
#include <climits>

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

string solve(i32 w, i32 h);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 w, h, i = 1;
    while(cin >> w >> h && w && h) {
        cout << "HOUSE " << i++ << "\n" << solve(w, h);
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

pair<i32, i32> delta[4] = {{1,0},{0,-1},{-1,0},{0,1}};

constexpr u64 RIGHT = 0;
constexpr u64 UP = 1;
constexpr u64 LEFT = 2;
constexpr u64 DOWN = 3;

string solve(i32 w, i32 h) {
    vector<string> grid(h);
    u64 x, y = ULLONG_MAX;
    for (u64 i = 0; i < h; i++) {
        cin >> grid[i];
    }
    for (u64 i = 0; i < h; i++) {
        x = grid[i].find("*");
        if (x != string::npos) {
            y = i;
            break;
        }
    }
    assert(y != ULLONG_MAX && x != string::npos);
    i32 d;
    if (x == 0) {
        d = 0;
    } else if (y == 0) {
        d = 3;
    } else if (x == w - 1) {
        d = 2;
    } else {
        d = 1;
    }
    while (grid[y][x] != 'x') {
        x += delta[d].first;
        y += delta[d].second;
        assert(0 <= x && x < w && 0 <= y && y < h);
        if (grid[y][x] == '/') {
            switch (d) {
            case RIGHT:
                d = UP;
                break;
            case UP:
                d = RIGHT;
                break;
            case LEFT:
                d = DOWN;
                break;
            case DOWN:
                d = LEFT;
                break;
            default:
                assert(false);
            }
        } else if (grid[y][x] == '\\') {
            switch (d) {
            case RIGHT:
                d = DOWN;
                break;
            case UP:
                d = LEFT;
                break;
            case LEFT:
                d = UP;
                break;
            case DOWN:
                d = RIGHT;
                break;
            default:
                assert(false);
            }
        }
    }
    grid[y][x] = '&';
    stringstream out;
    for (auto& s : grid) {
        out << s << "\n";
    }
    return out.str();
}
