#include <bits/stdc++.h>

/*
You had to do a lot of math in order to solve this problem. Basically, you had to
figure out that the expected value of the sum of the boxes squared follows the
formula E[A] = 1 + (2/s) * sum(g_i from a to b) + P, where s is the size of the range, g_i
is the sum of the probabilities thus far in box i, and P is the previous value of E[A].
This means you have to keep track of the sum of the probabilities in each box, and
doing this efficiently requires that you can do range updates and range queries which
means you need a segment tree with lazy propagation. You also need to store the probabilities
as integers mod 1000000007, because if you keep track of the probabilities 
as fractions the integers will get very large and overflow. This works because the
addition and multiplication form a homomorphism from rationals to integers mod 1000000007,
for h(a/b) = (a * modinv(b)) % 1000000007, which basically means that you get the same
result if you do the operations on the integers mod 1000000007 as you would if you did
the operations on the rationals and then took the result mod 1000000007.
*/

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

using std::max;
using std::min;
using std::to_string;
using std::sqrt;
using std::hypot;

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

class UnionFind {
private:
    mutable vector<i32> parents;
    vector<i32> sizes;
public:
    UnionFind(i32 n) : parents(n, -1), sizes(n, 1) {}

    i32 find(i32 x) const {
        if (parents[x] < 0) return x;
        vector<i32> path;
        while (parents[x] >= 0) {
            path.push_back(x);
            x = parents[x];
        }
        const i32 parent = x;
        for (i32 node : path) {
            parents[node] = parent;
        }
        return parent;
    }

    void join(i32 x, i32 y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (sizes[x] < sizes[y]) {
            parents[x] = y;
            sizes[y] = sizes[x];
        } else {
            parents[y] = x;
            sizes[x] += sizes[y];
        }
    }
};

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

constexpr i32 MOD = 1000000007;

i32 modinv(i32 a, i32 m) {
    i32 m0 = m;
    i32 y = 0, x = 1;

    if (m == 1) return 0;

    while (a > 1) {
        i32 q = a / m;
        i32 t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }
    
    if (x < 0)
        x += m0;

    return x;
}

i64 add(i64 a, i64 b) {
    if (a + b >= MOD) return (a + b) - MOD;
    return a + b;
}

i64 add3(i64 a, i64 b, i64 c) {
    return add(a, add(b, c));
}

i64 sub(i64 a, i64 b) {
    return (a - b + MOD) % MOD;
}

i64 mul(i64 a, i64 b) {
    return (a * b) % MOD;
}

i64 recip(i64 a) {
    return modinv(a, MOD);
}


class SegmentTree {
public:
    SegmentTree(i32 n) : n(n) {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    void propagate_lazy(i32 x, i32 l, i32 r) {
        if (lazy[x] == 0) return;
        i32 mid = (l+r) / 2;
        lazy[x*2] = add(lazy[x*2], lazy[x]);
        lazy[x*2+1] = add(lazy[x*2+1], lazy[x]);
        tree[x*2] = add(tree[x*2], 
                        mul(mid - l + 1, lazy[x]));
        tree[x*2+1] = add(tree[x*2+1], 
                        mul(r-mid, lazy[x]));
        lazy[x] = 0;
    }

    void update(i32 l, i32 r, i64 delta) {
        _update(1, 0, n-1, l, r, delta);
    }

    i64 query(i32 l, i32 r) {
        return _query(1, 0, n-1, l, r);
    }

private:

    void _update(i32 x, i32 l, i32 r, i32 ql, i32 qr, i64 delta) {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            lazy[x] = add(lazy[x], delta);
            tree[x] = add(tree[x], mul(r - l + 1, delta));
            return;
        }
        propagate_lazy(x, l, r);
        
        i32 mid = (l+r) / 2;

        _update(x*2, l, mid, ql, qr, delta);
        _update(x*2+1, mid+1, r, ql, qr, delta);
        tree[x] = add(tree[x*2], tree[x*2+1]);
    }

    i64 _query(i32 x, i32 l, i32 r, i32 ql, i32 qr) {
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[x];
        propagate_lazy(x, l, r);
        i32 mid = (l+r) / 2;
        return add(
                _query(x*2, l, mid, ql, qr), 
                _query(x*2+1, mid+1, r, ql, qr));
    }

    vector<i64> tree;
    vector<i64> lazy;
    i32 n;
};

#ifndef NOSEG
#define SEG_IMPL
#endif

class RangeSum {
public:
    #ifdef SEG_IMPL
    RangeSum(i32 n) : data(n) {}
    #else
    RangeSum(i32 n) : data(n, 0) {}
    #endif

    void update(i32 l, i32 r, i64 delta) {
        #ifdef SEG_IMPL
        data.update(l, r, delta);
        #else
        for (i32 i = l; i <= r; i++) {
            data[i] = add(data[i], delta);
        }
        #endif
    }

    i64 query(i32 l, i32 r) {
        #ifdef SEG_IMPL
        return data.query(l, r);
        #else
        i64 s = 0;
        for (i32 i = l; i <= r; i++) {
            s = add(s, data[i]);
        }
        return s;
        #endif
    }

private:
    #ifdef SEG_IMPL
    SegmentTree data;
    #else
    vector<i64> data;
    #endif

};

string solve() {
    stringstream ss;
    i32 n, q;
    cin >> n >> q;
    RangeSum boxes(n);
    i64 total_expected = 0;
    for (i32 q_i = 0; q_i < q; q_i++) {
        i32 query;
        cin >> query;
        if (query == 1) {
            i32 u, v;
            cin >> u >> v;
            i64 s = v - u + 1;
            i64 prob = recip(s);
            u--; v--;
            i64 G_sum = boxes.query(u, v);
            boxes.update(u, v, prob);
            total_expected = add3(total_expected, mul(mul(2, prob), G_sum), 1);
        } else {
            ss << total_expected << "\n";
        }
    }
    return ss.str();
}