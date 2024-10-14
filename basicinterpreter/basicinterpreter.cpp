#include <bits/stdc++.h>
#include <stdexcept>

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

i32 get_val(const string& arg, umap<string, i32>& vars) {
    if (isalpha(arg[0])) {
        return vars[arg];
    }
    return stoi(arg);
}

string solve() {
    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        lines.emplace_back(line);
    }
    sort(lines.begin(), lines.end(), [](const string& a, const string& b) {
        i32 l1, l2;
        stringstream(a) >> l1;
        stringstream(b) >> l2;
        return l1 < l2;
    });
    map<string, i32> label_index;
    for (i32 i = 0; i < lines.size(); i++) {
        string label;
        stringstream(lines[i]) >> label;
        label_index[label] = i;
    }
    stringstream output;
    i32 pc = 0;
    umap<string, i32> vars;
    while (pc < lines.size()) {
        stringstream instr(lines[pc++]);
        //instr.ignore(numeric_limits<streamsize>::max(), ' ');
        string _label;
        instr >> _label;
        string ignore;
        //cerr << _label << "\n";
        string op;
        instr >> op;
        if (op == "LET") {
            string assign;
            instr >> assign;
            instr >> ignore;
            string arg_1;
            instr >> arg_1;
            i32 v1 = get_val(arg_1, vars);
            string math_op;
            if (instr >> math_op) {
                string arg_2;
                instr >> arg_2;
                i32 v2 = get_val(arg_2, vars);
                if (math_op == "+") {
                    vars[assign] = v1 + v2;
                } else if (math_op == "-") {
                    vars[assign] = v1 - v2;
                } else if (math_op == "*") {
                    vars[assign] = v1 * v2;
                } else if (math_op == "/") {
                    vars[assign] = v1 / v2;
                }
            } else {
                vars[assign] = v1;
            }
        } else if (op == "IF") {
            string arg1, arg2, comp;
            instr >> arg1 >> comp >> arg2;
            i32 v1, v2;
            v1 = get_val(arg1, vars);
            v2 = get_val(arg2, vars);
            instr >> ignore >> ignore;
            string label;
            instr >> label;
            i32 pc_next = label_index[label];
            if (comp == "=") {
                if (v1 == v2) {
                    pc = pc_next;
                }
            } else if (comp == ">") {
                if (v1 > v2) {
                    pc = pc_next;
                }
            } else if (comp == "<") {
                if (v1 < v2) {
                    pc = pc_next;
                }
            } else if (comp == "<>") {
                if (v1 != v2) {
                    pc = pc_next;
                }
            } else if (comp == "<=") {
                if (v1 <= v2) {
                    pc = pc_next;
                }
            } else if (comp == ">=") {
                if (v1 >= v2) {
                    pc = pc_next;
                }
            } else {
                assert(false);
            }
        } else if (op == "PRINT") {
            string to_print;
            instr.ignore(1);
            getline(instr, to_print);
            if (to_print[0] == '"') {
                string text = to_print.substr(1, to_print.size()-2);
                output << text;
            } else {
                i32 num = vars[to_print];
                output << num;
            }
        } else if (op == "PRINTLN") {
            string to_print;
            instr.ignore(1);
            getline(instr, to_print);
            if (to_print[0] == '"') {
                string text = to_print.substr(1, to_print.size()-2);
                output << text << "\n";
            } else {
                i32 num = vars[to_print];
                output << num << "\n";
            }
        }
    }
    return output.str();
}
