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
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

map<char, i32> meaning;

i64 interpret(const string& s, i32 base) {
    i64 x = 0;
    for (i32 i = 0; i < s.size(); i++) {
        x *= base;
        x += meaning[s[i]];
        if (x >= (1LL << 32)) return -1;
    }
    return x;
}

string solve() {
    for (i32 i = 0; i < 10; i++) meaning['0' + i] = i;
    for (char c = 'a', i = 10; c <= 'z'; c++, i++) meaning[c] = i;
    string a, b, op, ans, _;
    cin >> a >> op >> b >> _ >> ans;
    bool has_zero = false;
    i32 highest_val = 0;
    for (char c : a) {
        if (c == '0') has_zero = true;
        highest_val = max(highest_val, meaning[c]);
    }
    for (char c : b) {
        if (c == '0') has_zero = true;
        highest_val = max(highest_val, meaning[c]);
    }
    for (char c : ans) {
        if (c == '0') has_zero = true;
        highest_val = max(highest_val, meaning[c]);
    }
    vector<i32> bases;
    if (!has_zero && highest_val == 1) {
        if (op == "+" && a.size() + b.size() == ans.size()) bases.emplace_back(1);
        else if (op == "-" && a.size() - b.size() == ans.size()) bases.emplace_back(1);
        else if (op == "*" && a.size() * b.size() == ans.size()) bases.emplace_back(1);
        else if (op == "/" && a.size() / b.size() == ans.size()) bases.emplace_back(1);
    }
    for (i32 base = highest_val + 1; base <= 36; base++) {
        i64 av, bv, ansv;
        av = interpret(a, base);
        bv = interpret(b, base);
        ansv = interpret(ans, base);
        if (av <= 0 || bv <= 0 || ansv <= 0) continue;
        if (op == "+" && av + bv == ansv) bases.emplace_back(base);
        else if (op == "*" && av * bv == ansv) bases.emplace_back(base);
        else if (op == "-" && av - bv == ansv) bases.emplace_back(base);
        else if (op == "/" && av == ansv * bv) bases.emplace_back(base);
    }
    if (bases.empty()) {
        return "invalid";
    }
    stringstream out;
    for (auto i : bases) {
        if (i < 10) {
            out << i;
        } else if (i == 36) {
            out << 0;
        } else {
            out << (char)('a' + i - 10);
        }
    }
    return out.str();
}
