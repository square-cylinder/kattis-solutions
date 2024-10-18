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

constexpr u32 col_mask = 0x7ff;
constexpr u32 row_mask = 0x7ff << 11;
constexpr u32 rot_mask = 0x1 << 22;
constexpr u32 id_mag = 1 << 11;

u32 id_at(i32 r, i32 c, bool horiz) {
    return c + id_mag * (r + id_mag * (u32)horiz);
}

vector<u32> id_blocks(u32 id) {
    u32 row = (id & row_mask) >> 11;
    u32 col = (id & col_mask);
    bool horiz = id & rot_mask;
    vector<u32> bruh;
    if (horiz) {
        if (col > 0) {
            bruh.emplace_back(id_at(row, col - 1, true));
        }
        bruh.emplace_back(id_at(row, col, false));
        bruh.emplace_back(id_at(row, col+1, false));
        if (row > 0) {
            bruh.emplace_back(id_at(row - 1, col, false));
            bruh.emplace_back(id_at(row - 1, col+1, false));
        }
        bruh.emplace_back(id_at(row, col + 1, true));
    } else {
        if (row > 0) {
            bruh.emplace_back(id_at(row - 1, col, false));
        }
        bruh.emplace_back(id_at(row + 1, col, false));
        if (col > 0) {
            bruh.emplace_back(id_at(row, col - 1, true));
            bruh.emplace_back(id_at(row + 1, col - 1, true));
        }
        bruh.emplace_back(id_at(row, col, true));
        bruh.emplace_back(id_at(row + 1, col, true));
    }
    return bruh;
}

struct DLListNode {
    u32 next, prev;
    u64 value;
    bool is_deleted;
};

struct DLList {
    private:
    vector<DLListNode> items;
    vector<u32> history;

    void hide_item(u32 pos) {
        assert(pos != 0);
        items[items[pos].next].prev = items[pos].prev;
        items[items[pos].prev].next = items[pos].next;
        items[pos].is_deleted = true;
    }

    void show_item(u32 pos) {
        assert(pos != 0);
        items[items[pos].next].prev = pos;
        items[items[pos].prev].next = pos;
        items[pos].is_deleted = false;
    }

    public:
    DLList() {
        DLListNode root = DLListNode();
        root.next = root.prev = 0;
        items.emplace_back(root);
    }

    u32 preview_undo() {
        return history.back();
    }

    u32 undo() {
        if (history.empty()) return 0;
        u32 to_undo = history.back();
        history.pop_back();
        show_item(to_undo);
        return to_undo;
    }

    bool is_deleted(u32 pos) {
        return items[pos].is_deleted;
    }

    void delete_item(u32 pos) {
        history.emplace_back(pos);
        assert(items[items[pos].next].prev == pos && items[items[pos].prev].next == pos);
        hide_item(pos);
    }

    u32 append_item(u64 val) {
        DLListNode node;
        node.prev = items[0].prev;
        node.next = 0;
        node.value = val;
        items.emplace_back(node);
        show_item(items.size() - 1);
        return items.size() - 1;
    }

    u32 next(u32 pos) const {
        return items[pos].next;
    }

    u32 prev(u32 pos) const {
        return items[pos].prev;
    }

    u32 begin() const {
        return items[0].next;
    }

    u32 end() const {
        return 0;
    }

    u64 get(u32 pos) const {
        return items[pos].value;
    }

    u32 size() const {
        return items.size() - 1;
    }

};

struct Solver {
    vector<vector<u32>> removes;
    set<u32> ignore_forever;
    DLList items;
    u32 num_picks;
    vector<i32> cur_picks;
    u64 cur_val;
    u32 best = 0;

    void select(u32 pos) {
        cur_picks.emplace_back(pos);
        cur_val += items.get(pos);
        items.delete_item(pos);
        for (i32 i = 0; i < removes[pos].size(); i++) {
            if (!items.is_deleted(removes[pos][i])) {
                items.delete_item(removes[pos][i]);
            }
        }
    }

    void unselect(u32 pos) {
        assert(pos == cur_picks.back());
        cur_picks.pop_back();
        for (i32 i = removes[pos].size() - 1; i >= 0; i--) {
            if (items.preview_undo() == removes[pos][i]) items.undo();
        }
        u32 item = items.undo();
        assert(item == pos);
        cur_val -= items.get(pos);
    }

    Solver(const vector<pair<u64, u32>>& alternatives, u32 k) {
        cur_val = 0;
        num_picks = k;
        map<u32, u32> id_conversion;
        items = DLList();
        removes.emplace_back();
        for (auto&[val, id] : alternatives) {
            id_conversion[id] = items.append_item(val);
            removes.emplace_back();
        }
        for (auto&[_val, id] : alternatives) {
            vector<u32> blocks = id_blocks(id);
            u32 internal_id = id_conversion[id];
            // cerr << internal_id << ": " << _val << " deletes";
            for (auto b : blocks) {
                if (id_conversion.find(b) != id_conversion.end()) {
                    u32 to_remove = id_conversion[b];
                    assert(to_remove != 0);
                    //cerr << " " << to_remove;
                    removes[internal_id].emplace_back(id_conversion[b]);
                }
            }
            //cerr << endl;
        }
    }

    u32 solve(bool a) {
        if (num_picks == 0) return cur_val;
        set<u32> ignore;
        for (i32 i = items.begin(); i != items.end(); i = items.next(i)) {
            if (ignore.find(i) != ignore.end() || ignore_forever.find(i) != ignore_forever.end()) continue;
            if (!items.is_deleted(i)) {
                select(i);
                num_picks--;
                u32 s = solve(a);
                best = max(best, s);
                num_picks++;
                unselect(i);
                // If a better solution exists, then it has to include one of the items this item prevented, since they are sorted from largest to smallest
                if (a) {
                    for (i32 j = 1; j <= items.size(); j++) {
                        if (find(removes[i].begin(), removes[i].end(), j) == removes[i].end()) {
                            ignore.emplace(j);
                        }
                    }
                }
            }
        }
        return best;
    }
};

string solve() {
    i32 n, k;
    cin >> n >> k;
    vector<pair<u64, u32>> alternatives;
    vector<vector<u64>> grid(n, vector<u64>(n));
    u64 sum = 0;
    for (i32 i = 0; i < n; i++) for (i32 j = 0; j < n; j++) {
        cin >> grid[i][j];
        sum += grid[i][j];
    }
    for (i32 r = 0; r < n; r++) for (i32 c = 0; c < n; c++) {
        if (c != n - 1) {
            alternatives.emplace_back(grid[r][c] + grid[r][c+1], id_at(r, c, true));
        }
        if (r != n - 1) {
            alternatives.emplace_back(grid[r][c] + grid[r+1][c], id_at(r, c, false));
        }
    }
    sort(alternatives.begin(), alternatives.end(), greater<pair<u64, u32>>());
    if (7*k < alternatives.size()) {
        alternatives.resize(7 * k);
    }
    Solver s(alternatives, k);
    //Solver s_alt(alternatives, k);
    u32 ans = s.solve(true);
    //u32 ans_alt = s_alt.solve(false);
    //cerr << "GOT: " << ans << " and " << ans_alt << endl;
    //assert(ans == ans_alt);
    return to_string(sum - ans);
}
