#include <bits/stdc++.h>
#include <numeric>

/* Common std library items */
using std::cin;
using std::cout;
using std::cerr;

using std::vector;
using std::pair;
using std::optional;
using std::map;
using std::set;
using std::unordered_map;
using std::unordered_set;

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
template<class T>
vector<T> input_vec(int length) { vector<T> v; v.reserve(length); for (int i = 0; i < length; i++) { T x; cin >> x; v.emplace_back(x); } return v; }

void solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

struct MetaItem {
    MetaItem(double sum, i32 count) : sum(sum), count(count) {}
    double sum;
    i32 count;
};

double solve_axis(const vector<i32>& values) {
    vector<MetaItem> items;
    for (auto val : values) {
        items.emplace_back(val, 1);
        i32 i = items.size() - 1;
        while (i > 0) {
            if (items[i].sum / items[i].count < items[i-1].sum /items[i-1].count) {
                int newcount = items[i].count + items[i-1].count;
                double newsum = items[i].sum + items[i-1].sum;
                items.pop_back();
                i--;
                items[i].count = newcount;
                items[i].sum = newsum;
            } else {
                break;
            }
        }
        
    }
    double square_distances = 0;
    i32 i = 0;
    for (auto item : items) {
        double position = item.sum / item.count;
        for (int j = 0; j < item.count; j++) {
            square_distances += (values[i] - position) * (values[i] - position);
            i++;
        }
    }
    return square_distances;
}

void solve() {
    i32 n;
    cin >> n;
    vector<i32> xs;
    vector<i32> ys;
    for (i32 i = 0; i < n; i++) {
        i32 x, y;
        cin >> x >> y;
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    cout << std::fixed << std::setprecision(7) << solve_axis(xs) + solve_axis(ys) << "\n";
}
