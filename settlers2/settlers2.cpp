#include <bits/stdc++.h>

#define MULTIPLE_CASES

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
void preprocess();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    preprocess();
#ifdef MULTIPLE_CASES
i32 n;
cin >> n;
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

vector<pair<i32, i32>> delta = {
    {0, -1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 0},
    {-1, -1}
};

vector<i32> solution;

void preprocess() {
    i32 n = 10000;
    map<pair<i32, i32>, i32> m;
    i32 res[5] = {};
    i32 from = 3;
    i32 x, y;
    x = y = 0;
    while (n--) {
        set<i32> possible = {0, 1, 2, 3, 4};
        for (auto&[dx, dy] : delta) {
            auto it = m.find({x + dx, y + dy});
            if (it != m.end()) {
                possible.erase(it->second);
            }
        }
        vector<pair<i32, i32>> v;
        for (auto& i : possible) {
            v.emplace_back(res[i], i);
        }
        sort(v.begin(), v.end());
        assert(v.size() > 0);
        i32 chosen = v[0].second;
        m[{x, y}] = chosen;
        res[chosen]++;
        solution.emplace_back(chosen);
        for (i32 i = 0; i < 6; i++) {
            pair<i32, i32> d = delta[(from+i)%6];
            pair<i32, i32> new_pos = {x + d.first, y + d.second};
            if (m.find(new_pos) == m.end()) {
                x = new_pos.first;
                y = new_pos.second;
                from = (from + i + 3) % 6;
                break;
            }
        }
    }
}

string solve() {
    i32 n;
    cin >> n;
    return to_string(solution[n-1]+1);
}
