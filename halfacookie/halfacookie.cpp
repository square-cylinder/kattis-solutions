#include <bits/stdc++.h>
#include <iostream>

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

string solve(double r, double x, double y);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double r, x, y;
    while (cin >> r >> x >> y) {
        cout << solve(r, x, y) << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve(double r, double x, double y) {
    double xn, yn;
    xn = x / r;
    yn = y / r;
    double x_l = sqrt(xn * xn + yn * yn);
    if (x_l >= 1) {
        return "miss";
    }
    double theta = acos(x_l);
    double p = (theta - x_l * sin(theta)) / M_PI;
    double a = r * r * M_PI;
    double a1, a2;
    a1 = p * a;
    a2 = (1-p) * a;
    return to_string(a2) + " " + to_string(a1);
}