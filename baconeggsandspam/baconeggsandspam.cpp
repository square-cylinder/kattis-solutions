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

string solve(i32 n);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n;
    while (cin >> n && n) {
        cin.ignore();
        cout << solve(n) << "\n";
    }
    cout << solve(n) << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve(i32 n) {
    map<string, vector<string>> items;
    while (n--) {
        string s;
        getline(cin, s);
        stringstream in(s);
        string name;
        in >> name;
        while (in >> s) {
            items[s].emplace_back(name);
        }
    }
    stringstream out;
    for (auto&[k, v] : items) {
        sort(v.begin(), v.end());
        out << k;
        for (auto& name : v) {
            out << " " << name;
        }
        out << "\n";
    }
    return out.str();
}