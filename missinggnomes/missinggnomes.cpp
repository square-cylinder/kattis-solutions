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
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n, m;
    cin >> n >> m;
    set<i32> s;
    for (i32 i = 1; i <= n; i++) {
        s.emplace(i);
    }
    vector<i32> g = input_vec<i32>(m);
    for (auto i : g) {
        s.erase(i);
    }
    vector<i32> ans;
    auto it = s.begin();
    for (i32 i = 0; i < m; i++) {
        while (it != s.end() && *it < g[i]) {
            ans.emplace_back(*it++);
        } 
        ans.emplace_back(g[i]);
    }
    while (it != s.end()) {
        ans.emplace_back(*it++);
    }
    stringstream out;
    for (auto i : ans) {
        out << i << "\n";
    }
    return out.str();
}
