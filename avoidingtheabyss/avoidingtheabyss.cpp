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
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

i64 out_x(i64 x, i64 x_p) {
    if (x < x_p) return -100000;
    return 100000;
}

string solve() {
    i64 x_s, y_s, x_t, y_t, x_p, y_p;
    cin >> x_s >> y_s >> x_t >> y_t >> x_p >> y_p;
    i64 from_x = out_x(x_s, x_p);
    i64 to_x = out_x(x_t, x_p);
    stringstream ans;
    if (from_x == to_x) {
        ans << 2 << "\n";
        ans << from_x << " " << y_s << "\n";
        ans << to_x << " " << y_t << "\n";
    } else {
        ans << 4 << "\n";
        ans << from_x << " " << y_s << "\n";
        ans << from_x << " " << -100000 << "\n";
        ans << to_x << " " << -100000 << "\n";
        ans << to_x << " " << y_t << "\n";
    }
    return ans.str();
}