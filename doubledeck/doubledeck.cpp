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

class SegTree {
    vector<i32> tree;
    i32 n;
    public:
    SegTree(i32 n) : n(n) {
        tree.resize(4 * n);
    }

    i32 get_max(i32 l, i32 r) {
        return get_max(0, 0, n - 1, l, r);
    }

    i32 get_max(i32 i, i32 l, i32 r, i32 want_l, i32 want_r) {
        if (r < want_l || want_r < l) {
            return 0;
        }
        if (want_l <= l && r <= want_r) {
            return tree[i];
        }
        i32 m = (l + r) / 2;
        return max(get_max(2 * i + 1, l, m, want_l, want_r),
                   get_max(2 * i + 2, m + 1, r, want_l, want_r));
    }

    void update(i32 i, i32 v) {
        update(0, 0, n - 1, i, v);
    }

    void update(i32 i, i32 l, i32 r, i32 pos, i32 val) {
        if (pos > r || pos < l) {
            return;
        }
        if (l == r) {
            tree[i] = max(tree[i], val);
            return;
        }
        tree[i] = max(tree[i], val);
        i32 m = (l + r) / 2;
        update(2 * i + 1, l, m, pos, val);
        update(2 * i + 2, m + 1, r, pos, val);
    }

};

string solve() {
    i32 n, k;
    cin >> n >> k;
    vector<i32> deck1, deck2;
    deck1 = input_vec<i32>(n * k);
    deck2 = input_vec<i32>(n * k);
    vector<vector<i32>> next_pos(n+1);
    for (i32 i = 0; i < n * k; i++) {
        next_pos[deck2[i]].emplace_back(i);
    }
    SegTree dp(n * k + 1);
    for (auto v : deck1) {
        vector<i32>& pos = next_pos[v];
        for (i32 i = pos.size() - 1; i >= 0; i--) {
            i32 p = pos[i];
            i32 best = dp.get_max(0, p) + 1;
            dp.update(p + 1, best);
        }
    }
    return to_string(dp.get_max(0, n * k + 1));
}