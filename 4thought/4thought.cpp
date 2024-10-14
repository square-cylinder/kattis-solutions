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
void preprocess();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    preprocess();
#ifdef MULTIPLE_CASES
i32 n;
cin >> n;
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////


i32 eval(vector<char> ops) {
    vector<i32> expr = {4,4,4,4};
    for (i32 i = 0; i < 3; i++) {
        for (i32 j = 0; j < ops.size() && !ops.empty(); j++) {
            if (ops[j] == '*') {
                expr[j] = expr[j] * expr[j+1];
                expr.erase(expr.begin() + j + 1);
                ops.erase(ops.begin() + j);
                break;
            }
            if (ops[j] == '/') {
                expr[j] = expr[j] / expr[j+1];
                expr.erase(expr.begin() + j + 1);
                ops.erase(ops.begin() + j);
                break;
            }
        }
    }
    for (i32 i = 0; i < 3 && !ops.empty(); i++) {
        for (i32 j = 0; j < ops.size(); j++) {
            if (ops[j] == '+') {
                expr[j] = expr[j] + expr[j+1];
                expr.erase(expr.begin() + j + 1);
                ops.erase(ops.begin() + j);
                break;
            }
            if (ops[j] == '-') {
                expr[j] = expr[j] - expr[j+1];
                expr.erase(expr.begin() + j + 1);
                ops.erase(ops.begin() + j);
                break;
            }
        }
    }
    return expr[0];
}

map<i32, string> results;
void preprocess() {
    vector<char> ops = {'+', '-', '*', '/'};
    for (auto& op1 : ops) for (auto& op2 : ops) for (auto& op3 : ops) {
        i32 result = eval({op1, op2, op3});
        stringstream equation;
        equation << 4 << " " << op1 << " " << 4 << " " << op2 << " " << 4 << " " << op3 << " " << 4 << " = " << result;
        results[result] = equation.str();
    }
}



string solve() {
    i32 n;
    cin >> n;
    if (results.find(n) == results.end()) {
        return "no solution";
    }
    return results[n];
}
