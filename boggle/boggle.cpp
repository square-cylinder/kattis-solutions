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

string solve();
void preprocess();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    preprocess();
    i32 n;
    cin >> n;
    while (n--)
        cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

struct TrieNode {
    bool is_end;
    bool has_more;
    TrieNode *children[26];
    TrieNode() : is_end(false), has_more(false) {
        memset(children, 0, sizeof(children));
    }

    ~TrieNode() {
        for (i32 i = 0; i < 26; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
    
    bool continues_with(char c) {
        assert(isupper(c));
        return children[c-'A'] != nullptr;
    }
    
    void insert(const string& s, i32 from = 0) {
        if (from == s.size()) {
            is_end = true;
            return;
        }
        has_more = true;
        char c = s[from];
        assert(isupper(c));
        i32 i = c - 'A';
        if (!children[i]) {
            children[i] = new TrieNode();
        }
        children[i]->insert(s, from + 1);
    }

    TrieNode *get(char c) {
        assert(isupper(c) && children[c-'A']);
        return children[c-'A'];
    }
};

TrieNode dict;
set<string> results;
string board;

void preprocess() {
    i32 n;
    cin >> n;
    for (i32 i = 0; i < n; i++) {
        string s;
        cin >> s;
        assert(s.size() <= 8);
        dict.insert(s);
    }
}

string so_far = "";
void explore(i32 from, i32 been, TrieNode *word) {
    so_far.push_back(board[from]);
    if (word->is_end) {
        results.emplace(so_far);
        if (!word->has_more) {
            so_far.pop_back();
            return;
        }
    }
    i32 x = from % 4, y = from / 4;
    for (i32 dy = -1; dy <= 1; dy++) for (i32 dx = -1; dx <= 1; dx++) {
        i32 xx = x + dx, yy = y + dy;
        if (xx < 0 || xx >= 4 || yy < 0 || yy >= 4) continue;
        i32 new_pos = xx + yy * 4;
        if (!(been & (1 << new_pos))) {
            char c = board[new_pos];
            if (word->continues_with(c)) {
                explore(new_pos, been | (1 << new_pos), word->get(c));
            }
        }
    }
    so_far.pop_back();
}

string solve() {
    results.clear();
    board.clear();
    string line;
    for (i32 i = 0; i < 4; i++) {
        cin >> line;
        board += line;
    }
    for (i32 i = 0; i < 16; i++) {
        if (dict.continues_with(board[i])) 
            explore(i, (1 << i), dict.get(board[i]));
    }
    i32 s = 0;
    i32 best = -1;
    string bestword;
    for (auto& w : results) {
        i32 score = 0;
        if (w.size() == 3 || w.size() == 4) score = 1;
        else if (w.size() == 5) score = 2;
        else if (w.size() == 6) score = 3;
        else if (w.size() == 7) score = 5;
        else if (w.size() == 8) score = 11;
        s += score;
        if (score > best) {
            best = score;
            bestword = w;
        }
    }
    stringstream out;
    out << s << " " << bestword << " " << results.size();
    return out.str();
}
