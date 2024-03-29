#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>

/* Common std library items */
using std::cin;
using std::cout;
using std::cerr;

using std::string;
using std::stringstream;
using std::vector;
using std::pair;
using std::tuple;
using std::optional;
using std::map;
using std::set;
using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::priority_queue;

using std::max;
using std::min;
using std::to_string;
using std::sqrt;
using std::hypot;
using std::abs;
using std::make_pair;


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

/* Introduce a less insane way to check for an element in a set or map */
template<class T1, class T2>
bool contains(const T1& c, T2 e) { return c.find(e) != c.end(); }
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
    cout.tie(nullptr);
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve() {
    i32 num_things, the_target;
    cin >> num_things >> the_target;
    i32 costs[501];
    i32 diffs[501];
    costs[0] = 1;
    diffs[0] = 1;
    umap<i32, i32> pos, neg;
    pos[1] = 0;
    for (i32 i = 1; i <= num_things; i++) {
        cin >> diffs[i] >> costs[i];
        if (costs[i] >= 2 * the_target) continue;
        if (diffs[i] > 0 && (!contains(pos, diffs[i]) || costs[pos[diffs[i]]] > costs[i])) {
            pos[diffs[i]] = i;
        }
        else if (diffs[i] < 0 && (!contains(neg, diffs[i]) || costs[neg[diffs[i]]] > costs[i])) {
            neg[diffs[i]] = i;
        }
    }

    i32 optimal_costs[400001];
    i32 optimal_index[400001];
    for (i32 i = 0; i <= the_target * 2; i++) optimal_costs[i] = INT_MAX;
    optimal_costs[0] = 0;

    for (auto [diff, index] : pos) {
        for (i32 i = 0; i + diff <= the_target * 2; i++) {
            if (optimal_costs[i] == INT_MAX) continue;
            const i32 new_value = i + diff;
            const i32 new_cost = optimal_costs[i] + costs[index];
            if (optimal_costs[new_value] > new_cost) {
                optimal_costs[new_value] = new_cost;
                optimal_index[new_value] = index;
            }
        }
    }

    for (auto [diff, index] : neg) {
        for (i32 i = the_target * 2; i + diff >= the_target; i--) {
            const i32 new_value = i + diff;
            const i32 new_cost = optimal_costs[i] + costs[index];
            if (optimal_costs[new_value] > new_cost) {
                optimal_costs[new_value] = new_cost;
                optimal_index[new_value] = index;
            }
        }
    }

    vector<i32> path;
    i32 cur = the_target;
    while (cur != 0) {
        path.emplace_back(optimal_index[cur] + 1);
        cur -= diffs[optimal_index[cur]];
    }

    stringstream ss;
    ss << path.size() << "\n";
    ss << path[0];
    for (i32 i = 1; i < path.size(); i++) {
        ss << " " << path[i];
    }

    return ss.str();
}