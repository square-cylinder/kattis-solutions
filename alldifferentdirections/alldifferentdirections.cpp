#include <bits/stdc++.h>
#include <sstream>
#include <string>

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
    while (true) {
        string line;
        getline(cin, line);
        i32 n;
        stringstream(line) >> n;
        if (n == 0) break;
        cout << solve(n) << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

pair<double, double> follow_directions() {
    string s;
    getline(cin, s);
    stringstream in(s);
    double x, y, angle;
    double dir_x, dir_y;
    in >> x >> y >> s >> angle;
    dir_x = cos(angle * 2 * M_PI / 360);
    dir_y = sin(angle * 2 * M_PI / 360);
    while (in >> s) {
        if (s == "walk") {
            double dist;
            in >> dist;
            x += dir_x * dist;
            y += dir_y * dist;
        } else { // turn
            double d_angle;
            in >> d_angle;
            angle += d_angle;
            dir_x = cos(angle * 2 * M_PI / 360);
            dir_y = sin(angle * 2 * M_PI / 360);
        }
    }
    return {x, y};
}

string solve(i32 n) {
    vector<pair<double, double>> positions;
    double avg_x = 0, avg_y = 0;
    for (i32 i = 0; i < n; i++) {
        positions.emplace_back(follow_directions());
        avg_x += positions.back().first;
        avg_y += positions.back().second;
    }
    avg_x /= n;
    avg_y /= n;
    double max_dist = 0;
    for (i32 i = 0; i < n; i++) {
        double dist = sqrt(pow(positions[i].first - avg_x, 2) + pow(positions[i].second - avg_y, 2));
        max_dist = max(max_dist, dist);
    }
    stringstream out;
    out << fixed << setprecision(6) << avg_x << " " << avg_y << " " << max_dist;
    return out.str();
}