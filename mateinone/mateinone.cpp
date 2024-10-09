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

typedef vector<string> Board;
typedef pair<string, Board> Move;

struct V2 {
    i32 r, c;
    V2() : r(0), c(0) {}
    V2(i32 r, i32 c) : r(r), c(c) {}

    bool in_bounds() {
        return 0 <= r && r < 8 && 0 <= c && c < 8;
    }

    char in(const Board& board) {
        assert(in_bounds());
        return board[r][c];
    }

    void set(Board& board, char piece) {
        assert(in_bounds());
        board[r][c] = piece;
    }

    V2 operator+(const V2& other) {
        return V2(r + other.r, c + other.c);
    }

    V2 operator+=(const V2& other) {
        r += other.r;
        c += other.c;
        return *this;
    }

    string board_string() {
        string out = "";
        out.push_back('a' + c);
        out.push_back('8' - r);
        return out;
    }
};

const vector<V2> horse_moves = {
    V2(1, 2), V2(1, -2),
    V2(-1, 2), V2(-1, -2),
    V2(2, 1), V2(2, -1),
    V2(-2, 1), V2(-2, -1)
};

const vector<V2> king_moves = {
    V2(1, 0), V2(1, 1), V2(1, -1),
    V2(0, 1), V2(0, -1),
    V2(-1, 0), V2(-1, 1), V2(-1, -1)
};

const vector<V2> bishop_steps = {
    V2(1, 1), V2(1, -1),
    V2(-1, 1), V2(-1, -1)
};

const vector<V2> rook_steps = {
    V2(1, 0), V2(0, 1),
    V2(-1, 0), V2(0, -1)
};

const vector<V2> queen_steps = {
    V2(1, 1), V2(1, -1),
    V2(-1, 1), V2(-1, -1),
    V2(1, 0), V2(0, 1),
    V2(-1, 0), V2(0, -1)
};

// Pawns are dealt with separately

V2 find_king(const Board& board) {
    V2 k;
    for (k.r = 0; k.r < 8; k.r++) for (k.c = 0; k.c < 8; k.c++) {
        if (k.in(board) == 'K') {
            return k;
        }
    }
    assert(false);
}

vector<string> change_perspective(const Board& board) {
    vector<string> out;
    for (i32 i = 0; i < 8; i++) {
        out.emplace_back("");
        for (i32 j = 0; j < 8; j++) {
            char c = board[7-i][7-j];
            if (c == '.') {
                out.back().push_back(c);
            } else if (islower(c)) {
                out.back().push_back(toupper(c));
            } else {
                out.back().push_back(tolower(c));
            }
        }
    }
    return out;
}


bool has_piece(const Board& board, V2 pos, char piece) {
    return pos.in_bounds() && pos.in(board) == piece;
}

bool has_enemy(const Board& board, V2 pos) {
    return pos.in_bounds() && islower(pos.in(board));
}

// Check for one of the pieces in a line described by (dr, dc) from (r, c)
bool line_check(const Board& board, V2 from, const vector<V2>& changes, char piece) {
    for (const V2& change : changes) {
        for (V2 cur = from + change; cur.in_bounds(); cur += change) {
            if (cur.in(board) == piece) {
                return true;
            } else if (cur.in(board) != '.') {
                break;
            }
        }
    }
    return false;
} 

vector<pair<char, V2>> king_threats;
bool is_in_check(const vector<string>& board) {
    V2 king = find_king(board);
    assert(!king_threats.empty());

    if (line_check(board, king, bishop_steps, 'b')) {
        return true;
    }
    if (line_check(board, king, rook_steps, 'r')) {
        return true;
    }
    if (line_check(board, king, queen_steps, 'q')) {
        return true;
    }
    
    for (const auto&[piece, move] : king_threats) {
        if (has_piece(board, king + move, piece)) {
            return true;
        }
    }
    return false;
}


void try_move(vector<Move>& out, const Board& board, V2 from, V2 to, char piece) {
    vector<string> new_board = board;

    to.set(new_board, piece);
    from.set(new_board, '.');

    if (!is_in_check(new_board)) {
        out.emplace_back(from.board_string() + to.board_string(), new_board);
    }
}

void try_pawn_moves(vector<Move>& out, const Board& board, V2 at, char piece) {
    // Try to move up (will be blocked by friendly and enemy pieces)
    V2 to = at + V2(-1, 0);
    if (has_piece(board, to, '.')) {
        try_move(out, board, at, to, piece);
        to = at + V2(-2, 0);
        if (at.r == 6 && has_piece(board, to, '.')) {
            try_move(out, board, at, to, piece);
        }
    }

    // Try to eliminate an enemy up to the left
    to = at + V2(-1, -1);
    if (has_enemy(board, to)) {
        try_move(out, board, at, to, piece);
    }

    // Try to eliminate an enemy up to the right
    to = at + V2(-1, 1);
    if (has_enemy(board, to)) {
        try_move(out, board, at, to, piece);
    }
}

void line_moves(vector<Move>& out, const Board& board, V2 from, const vector<V2>& changes) {
    for (const V2& change : changes) {
        // Go in the direction of the change until we hit a friendly piece or the edge of the board
        for (V2 cur = from + change; cur.in_bounds() && !isupper(cur.in(board)); cur += change) {
            char piece = cur.in(board);
            try_move(out, board, from, cur, from.in(board));
            // If we hit an enemy piece, we can't go further after that
            if (islower(piece)) {
                break;
            }
        }
    }
} 

// Find all possible next states from the current board with the associated move
vector<Move> get_legal_moves(const Board& board) {
    vector<Move> out;
    V2 pos;
    // Go through all the pieces on the board
    for (pos.r = 0; pos.r < 8; pos.r++) for (pos.c = 0; pos.c < 8; pos.c++) if (isupper(pos.in(board))) {
        switch (pos.in(board)) {
        case 'P':
            // If the pawn is on the last row, we will promote it after moving
            if (pos.r == 1) {
                for (char promo : {'Q', 'N'}) {
                    try_pawn_moves(out, board, pos, promo);
                }
            } else {
                try_pawn_moves(out, board, pos, 'P');
            }
            break;
        case 'N':
            for (const V2& move : horse_moves) {
                // Can move if the position is inside the board and there is no friendly piece
                V2 to = pos + move;
                if (to.in_bounds() && !isupper(to.in(board))) {
                    try_move(out, board, pos, to, 'N');
                }
            }
            break;
        case 'B':
            line_moves(out, board, pos, bishop_steps);
            break;
        case 'R':
            line_moves(out, board, pos, rook_steps);
            break;
        case 'Q':
            line_moves(out, board, pos, queen_steps);
            break;
        case 'K':
            for (const V2& move : king_moves) {
                V2 to = pos + move;
                if (to.in_bounds() && !isupper(to.in(board))) {
                    try_move(out, board, pos, to, 'K');
                }
            }
            break;
        default:
            assert(false);
        }
    }
    return out;
}

string solve() {
    Board board(8);
    king_threats.emplace_back('p', V2(-1, -1));
    king_threats.emplace_back('p', V2(-1, 1));
    for (const V2& move : horse_moves) {
        king_threats.emplace_back('n', move);
    }
    for (const V2& move : king_moves) {
        king_threats.emplace_back('k', move);
    }
    for (i32 i = 0; i < 8; i++) {
        cin >> board[i];
    }
    vector<string> good;
    vector<Move> moves = get_legal_moves(board);
    for (auto&[move, new_board] : moves) {
        Board other = change_perspective(new_board);
        vector<Move> other_moves = get_legal_moves(other);
        if (other_moves.empty() && is_in_check(other)) {
            good.emplace_back(move);
        }
    }
    if (good.size() > 1) {
        for (string s : good) {
            cout << s << " ";
        }
        cout << "\n";
        exit(1);
    }
    if (good.size() == 1) {
        return good[0];
    }
    // Gets to this point in testcase 17
    assert(false); // should have found one single solution
}