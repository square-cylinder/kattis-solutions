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

string solve() {
    priority_queue<i32> low;
    priority_queue<i32, vector<i32>, greater<i32>> high;
    string s;
    stringstream out;
    while (cin >> s) {
        if (s == "#") {
            if (low.size() > high.size()) {
                out << low.top() << "\n";
                low.pop();
            } else {
                out << high.top() << "\n";
                high.pop();
            }
        } else {
            i32 x = stoi(s);
            if (low.size() <= high.size()) {
                low.emplace(x);
            } else {
                high.emplace(x);
            }
            if (low.size() > 0 && high.size() > 0 && low.top() > high.top()) {
                i32 l = low.top();
                i32 h = high.top();
                low.pop();
                high.pop();
                low.emplace(h);
                high.emplace(l);
            }
        }
    }
    return out.str();
}