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

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n;
    cin >> n;
    vector<pair<i32, string>> v;
    for (i32 i = 0; i < n; i++) {
        string s1, s2;
        cin >> s1 >> s2;
        if (isalpha(s1[0])) {
            v.emplace_back(stoi(s2), s1);
        } else {
            v.emplace_back(stoi(s1) / 2, s2);
        }
    }
    sort(v.begin(), v.end());
    stringstream ss;
    for (auto&[_, s] : v) {
        ss << s << "\n";
    }
    return ss.str();
}