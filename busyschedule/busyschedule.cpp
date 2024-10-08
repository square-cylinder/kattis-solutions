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

int cmp_date(const tuple<i32, i32, string>& l, const tuple<i32, i32, string>& r) {
    if (get<2>(l) != get<2>(r)) {
        return get<2>(l) < get<2>(r);
    }
    if (get<0>(l) != get<0>(r)) {
        return get<0>(l) < get<0>(r);
    }
    return get<1>(l) < get<1>(r);
}

string solve(i32 n) {
    vector<tuple<i32, i32, string>> v;
    while (n--) {
        string a1, a2;
        cin >> a1 >> a2;
        a1.at(a1.find(':')) = ' ';
        i32 h, m;
        stringstream(a1) >> h >> m;
        v.emplace_back(h % 12, m, a2);
    }
    sort(v.begin(), v.end(), cmp_date);
    stringstream ss;
    for (auto&[h, m, a] : v) {
        ss << (h == 0 ? 12 : h) << ":";
        if (m < 10) {
            ss << "0";
        }
        ss << m << " " << a << "\n";
    }
    return ss.str();
}