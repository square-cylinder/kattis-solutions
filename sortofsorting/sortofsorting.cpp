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
    cin >> n;
    while (n) {
        cout << solve(n) << "\n";
        cin >> n;
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

int cmp(const string& l, const string& r) {
    if (l[0] != r[0]) {
        return l[0] < r[0];
    }
    if (l[1] == r[1]) return 0;
    return l[1] < r[1];
}

string solve(i32 n) {
    vector<string> v = input_vec<string>(n);
    stable_sort(v.begin(), v.end(), cmp);
    stringstream out;
    for (auto& name : v) {
        out << name << "\n";
    }
    return out.str();
}