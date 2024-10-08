#include <bits/stdc++.h>
#include <iomanip>

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

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double x1, y1, x2, y2, p;
    while (cin >> x1 >> y1 >> x2 >> y2 >> p) {
        double d1 = pow(abs(x1 - x2), p);
        double d2 = pow(abs(y1 - y2), p);
        cout << fixed << setprecision(10) << pow(d1 + d2, 1 / p) << "\n";
    }
    return 0;
}