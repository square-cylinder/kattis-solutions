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
    i32 t;
    cin >> t;
    while (t--)
        cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

i32 solve_arr(vector<i32>& arr, i32 m)
{
    vector<i32> prefixsum;
    prefixsum.reserve(arr.size() + 1);
    prefixsum.emplace_back(0);
    for (i32 i : arr) {
        prefixsum.push_back(prefixsum.back() + i);
    }
    i32 best = 0;
    i32 prevprev_m = 0;
    i32 prev_m = 0;
    for (i32 i = 0; i < arr.size(); i++) {
        if (arr[i] == m) {
            if (prev_m != 0) {
                // Calculate sum of largest interval containing exactly one m
                i32 total = prefixsum[i] - prefixsum[prevprev_m];
                best = max(best, total);
            }
            prevprev_m = prev_m;
            prev_m = i+1;
        }
    }
    return max(best, prefixsum.back() - prefixsum[prevprev_m]);
}

string solve() {
    i32 n, m;
    cin >> n >> m;
    vector<vector<i32>> arrs(1);
    bool contains_m = false;
    for (i32 i = 0; i < n; i++) {
        i32 x;
        cin >> x;
        if (x < m) {
            if (arrs.back().size() > 0) {
                if (contains_m) {
                    arrs.emplace_back();
                    contains_m = false;
                } else {
                    arrs.back().clear();
                }
            }
        } else {
            arrs.back().emplace_back(x);
            if (x == m) {
                contains_m = true;
            }
        }
    }
    i32 best = -1;
    for (auto& arr : arrs) {
        i32 res = solve_arr(arr, m);
        best = max(best, res);
    }
    return to_string(best);
}