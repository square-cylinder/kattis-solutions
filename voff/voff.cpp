#include <bits/stdc++.h>
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

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 n, k;
    cin >> n >> k;
    map<i32, i32> events;
    for (i32 i = 0; i < n; i++) {
        i32 a_i;
        cin >> a_i;
        events[a_i] += 1;
        events[a_i + k] -= 1;
    }
    i32 current = 0;
    i32 most = 0;
    for (auto& [time, delta] : events) {
        current += delta;
        most = max(most, current);
    }
    return to_string(most);
}