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
    string line;
    do {
        cout << solve() << endl;
    } while (getline(cin, line));
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

struct HNode {
    i32 left, right;
    i32 base;
    i32 num_items;
};

struct Node {
    i32 up, down;
    i32 index, header;
};

struct DLX {
private:
    i32 tot_cols;
    vector<HNode> headers;
    vector<Node> nodes;
    vector<vector<i32>> solutions;
    i32 break_after;
    vector<i32> picked;
    vector<i32> separator_indicies;

    void hide_col(i32 c) {
        headers[headers[c].left].right = headers[c].right;
        headers[headers[c].right].left = headers[c].left;
    }

    void unhide_col(i32 c) {
        headers[headers[c].left].right = c;
        headers[headers[c].right].left = c;
    }

    void hide_node(i32 i) {
        headers[nodes[i].header].num_items--;
        nodes[nodes[i].down].up = nodes[i].up;
        nodes[nodes[i].up].down = nodes[i].down;
    }

    void unhide_node(i32 i) {
        headers[nodes[i].header].num_items++;
        nodes[nodes[i].down].up = i;
        nodes[nodes[i].up].down = i;
    }

    i32 beginning(i32 i) {
        while (nodes[i-1].header != 0) i--;
        return i;
    }

    i32 ending(i32 i) {
        while (nodes[i+1].header != 0) i++;
        return i;
    }

    void cover_row(i32 first_element) {
        deleted_rows.emplace_back(-1);
        for (i32 i = first_element; nodes[i].header != 0; i++) {
            i32 h_index = headers[nodes[i].header].base;
            for (i32 j = nodes[h_index].down; j != h_index; j = nodes[j].down) {
                if (i == j) continue;
                i32 k = beginning(j);
                deleted_rows.emplace_back(separator_indicies[nodes[k-1].index+1]-1);
                for (; nodes[k].header != 0; k++) {
                    hide_node(k);
                }
            }
            hide_col(nodes[i].header);
        }
    }

    void uncover_row(i32 last_element) {
        for (i32 i = last_element; nodes[i].header != 0; i--) {
            unhide_col(nodes[i].header);
        }
        while (deleted_rows.back() != -1) {
            for (i32 k = deleted_rows.back(); nodes[k].header != 0; k--) {
                unhide_node(k);
            }
            deleted_rows.pop_back();
        }
        deleted_rows.pop_back();
    }

public:
    vector<i32> deleted_rows;
    DLX(i32 num_items) {
        tot_cols = num_items;
        break_after = -1;
        // Root header, does not need a base node since we won't be traveling up or down it
        headers.emplace_back();
        headers.back().num_items = INT_MAX;
        for (i32 i = 0; i < num_items; i++) {
            nodes.emplace_back();
            nodes.back().down = nodes.size() - 1;
            nodes.back().up = nodes.size() - 1;
            nodes.back().index = nodes.size() - 1;

            headers.emplace_back();
            headers.back().base = nodes.size() - 1;
            headers.back().num_items = 0;
            headers[headers.size()-2].right = headers.size() - 1;
            headers[headers.size()-1].left = headers.size() - 2;

            nodes.back().header = headers.size() - 1;
        }
        headers[headers.size() - 1].right = 0;
        headers[0].left = headers.size() - 1;
        // First separator node
        nodes.emplace_back();
        nodes.back().index = 0;
        nodes.back().header = 0;
        separator_indicies.emplace_back(nodes.size() - 1);
    }

    void add_row(vector<i32> items) {
        i32 row_index = nodes.back().index + 1;
        sort(items.begin(), items.end());
        for (auto item : items) {
            //cerr << "Adding item: " << item << " to row " << row_index - 1 << "\n";
            i32 header_index = item + 1;
            nodes.emplace_back();
            nodes.back().index = nodes.size() - 1;
            nodes.back().down = headers[header_index].base;
            nodes.back().up = nodes[headers[header_index].base].up;
            nodes.back().header = header_index;
            unhide_node(nodes.size() - 1);
        }
        nodes.emplace_back();
        nodes.back().index = row_index;
        nodes.back().header = 0;
        separator_indicies.emplace_back(nodes.size() - 1);
        //for (i32 i = 1; i <= tot_cols; i++) {
            //cerr << "Column " << i << " has " << headers[i].num_items << " items.\n";
        //}
    }

    bool unpick_latest() {
        if (picked.empty()) return false;
        uncover_row(separator_indicies[picked.back()+1] - 1);
        picked.pop_back();
        return true;
    }

    void pick_row(i32 i) {
        picked.emplace_back(i);
        cover_row(separator_indicies[i] + 1);
    }

    void set_desired_solutions(i32 n) {
        break_after = n;
    }

    void reset() {
        while (unpick_latest());

        solutions.clear();
    }

    void solve() {
        if (break_after != -1 && solutions.size() >= break_after) return;
        if (headers[0].right == 0) {
            solutions.emplace_back();
            for (i32 r : picked) {
                solutions.back().emplace_back(r);
            }
            return;
        }
        i32 col = 0;
        for (i32 i = headers[0].right; i != 0; i = headers[i].right) {
            if (headers[i].num_items < headers[col].num_items) col = i;
        }
        i32 col_base = headers[col].base;
        for (i32 r = nodes[col_base].down; r != col_base; r = nodes[r].down) {
            i32 row_to_delete = beginning(r);
            cover_row(row_to_delete);
            picked.emplace_back(nodes[row_to_delete-1].index);
            solve();
            unpick_latest();
        }
    }

    const vector<vector<i32>>& get_solutions() {
        return solutions;
    }

    static DLX sudoku_solver() {
        DLX s = DLX(324);
        for (i32 r = 0; r < 9; r++) for (i32 c = 0; c < 9; c++) for (i32 n = 0; n < 9; n++) {
            i32 box = (r/3)*3 + c/3;
            s.add_row({r * 9 + c, 81 + r * 9 + n, 81 * 2 + c * 9 + n, 81 * 3 + box * 9 + n});
        }
        return s;
    }
};

map<i32, tuple<i32, i32, i32>> rcn;
void preprocess() {
    for (i32 r = 0; r < 9; r++) for (i32 c = 0; c < 9; c++) for (i32 n = 0; n < 9; n++) {
        rcn[n + 9 * (c + 9 * r)] = {r, c, n};
    }
}

string get_board(const vector<i32>& rows) {
    vector<vector<i32>> board(9, vector<i32>(9));
    for (auto r : rows) {
        board[get<0>(rcn[r])][get<1>(rcn[r])] = 1 + get<2>(rcn[r]);
    }
    stringstream out;
    for (const auto& r : board) {
        for (i32 i = 0; i < r.size(); i++) {
            out << r[i];
            if (i != r.size() - 1) {
                out << " ";
            }
        }
        out << "\n";
    }
    return out.str();
}

string solve() {
    DLX solver = DLX::sudoku_solver();
    solver.set_desired_solutions(2);
    for (i32 r = 0; r < 9; r++) {
        for (i32 c = 0; c < 9; c++) {
            i32 num;
            cin >> num;
            if (num != 0) {
                i32 row = 81 * r + 9 * c + num - 1;
                // ???? this broke the code??
                //if (find(solver.deleted_rows.begin(), solver.deleted_rows.end(), row) != solver.deleted_rows.end()) {
                    //return "Find another job\n";
                //}
                solver.pick_row(row);
            }
        }
    }
    cin.ignore();
    solver.solve();
    const vector<vector<i32>> sols = solver.get_solutions();
    if (sols.size() == 0) return "Find another job\n";
    if (sols.size() == 2) return "Non-unique\n";
    return get_board(sols[0]);
}
