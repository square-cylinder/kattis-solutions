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
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

typedef vector<string> Board;

string stringify_board(const Board& board) {
    stringstream out;
    for (i32 i = 0; i < 9; i++) out << board[i] << "\n";
    return out.str();
}

struct V2 {
    i32 r, c;
    V2() : r(0), c(0) {}
    V2(i32 r, i32 c) : r(r), c(c) {}

    V2 base_block() {
        return V2((r / 3) * 3, (c / 3) * 3);
    }

    V2 operator+(const V2& other) {
        return V2(r + other.r, c + other.c);
    }

    V2 operator+=(const V2& other) {
        r += other.r;
        c += other.c;
        return *this;
    }

    bool operator==(const V2& other) const {
        return r == other.r && c == other.c;
    }

    bool operator<(const V2& other) const {
        return r < other.r || (r == other.r && c < other.c);
    }

    void next(i32 w, i32 d = 1) {
        c += d;
        if (c == w) {
            c = 0;
            r += d;
        }
    }

    string to_string() {
        return "(" + std::to_string(r) + ", " + std::to_string(c) + ")";
    }
};
 
void cross_block(set<V2>& availible, V2 block) {
    V2 offset;
    for (offset.r = 0; offset.r < 3; offset.r++) {
        for (offset.c = 0; offset.c < 3; offset.c++) {
            availible.erase(block + offset);
        }
    }
}
 
void cross_position(set<V2>& availible, V2 pos) {
    cross_block(availible, pos.base_block());
    for (i32 i = 0; i < 9; i++) {
        availible.erase({pos.r, i});
        availible.erase({i, pos.c});
    }
}

vector<V2> deducable_in_block(const set<V2>& availible, V2 block, char c) {
    vector<V2> result;
    for (V2 offset = V2(0, 0); offset.r < 3; offset.next(3)) {
        V2 pos = block + offset;
        if (availible.count(pos)) {
            result.emplace_back(pos);
        }
    }
    return result;
}

bool exists_in_block(const Board& board, i32 block_x, i32 block_y, char c) {
    for (i32 i = 0; i < 3; i++) for (i32 j = 0; j < 3; j++) {
        i32 x = block_x * 3 + i;
        i32 y = block_y * 3 + j;
        if (board[y][x] == c) return true;
    }
    return false;
}

bool cross_hatch(Board& board, char c) {
    set<V2> availible;
    for (V2 i = V2(0, 0); i.r < 9; i.next(9)) {
        if (board[i.r][i.c] == '.') {
            availible.insert(i);
        }
    }
    for (V2 i = V2(0, 0); i.r < 9; i.next(9)) {
        if (board[i.r][i.c] == c) {
            cross_position(availible, i);
        }
    }
    for (V2 i = V2(0, 0); i.r < 9; i.next(9, 3)) {
        i32 found = 0;
        for (V2 j = V2(0, 0); j.r < 3; j.next(3)) {
            V2 p = i + j;
            if (board[p.r][p.c] == c) {
                found++;
            }
        }
        auto result = deducable_in_block(availible, i, c);
        if (found == 0 && result.size() == 0) {
            return false;
        } else if (result.size() == 1) {
            board[result[0].r][result[0].c] = c;
            cross_position(availible, result[0]);
        }
    }
    return true;
}

bool board_is_valid(const Board& b) {
    for (i32 i = 0; i < 3; i++) {
        for (i32 j = 0; j < 3; j++) {
            uset<char> s;
            for (i32 x = 0; x < 3; x++) {
                for (i32 y = 0; y < 3; y++) {
                    char c = b[i*3 + y][j*3 + x];
                    if (c != '.' && s.count(c)) {
                        return false;
                    }
                    s.emplace(x);
                }
            }
        }
    }
    for (i32 i = 0; i < 9; i++) for (i32 j = 0; j < 9; j++) {
        char c = b[i][j];
        if (c == '.') continue;
        for (i32 k = 0; k < 9; k++) {
            if (k != j && b[i][k] == c) return false;
            if (k != i && b[k][j] == c) return false;
        }
    }
    return true;
}

string solve() {
    Board b(9);
    for (i32 i = 0; i < 9; i++) {
        cin >> b[i];
    }
    if (!board_is_valid(b)) {
        return "ERROR";
    }
    for (i32 i = 0; i < 9; i++) {
        for (char c = '1'; c <= '9'; c++) {
            if (!cross_hatch(b, c)) {
                //cerr << "problem with " << c << "\n" << stringify_board(b) << "\n";
                return "ERROR";
            }
        }
    }
    return stringify_board(b);
}