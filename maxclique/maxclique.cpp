#include <bits/stdc++.h>

//#define MULTIPLE_CASES

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

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef MULTIPLE_CASES
i32 n;
cin >> n;
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

u64 adj_mat[64];

u32 bron_kerbosch(u64 r, u64 p, u64 x) {
    if (p == 0 && x == 0) {
        return __builtin_popcountll(r);
    }
    if (!p) return 0;
    i32 u = 0;
    u64 pivoted;
    u64 pUx = p | x;
    for (u64 i = 0; i < 64; i++) {
        if (pUx & (((u64)1) << i)) {
            pivoted = p & ~adj_mat[i];
        }
    }
    u32 best = 0;
    for (u64 i = 0; i < 64; i++) {
        u64 v = ((u64)1) << i;
        if (!(v & pivoted)) continue;
        best = max(best, bron_kerbosch(r | v, p & adj_mat[i], x & adj_mat[i]));
        p = p & ~v;
        x = x | v;
    }
    return best;
}

string solve() {
    memset(adj_mat, 0, sizeof(adj_mat));
    i32 n, m;
    cin >> n >> m;
    while (m--) {
        i32 a, b;
        cin >> a >> b;
        adj_mat[a] |= (((u64)1) << (u64)b);
        adj_mat[b] |= (((u64)1) << (u64)a);
    }
    cin.ignore();
    u64 all_nodes = 0;
    while (n--) {
        all_nodes <<= ((u64)1);
        all_nodes |= ((u64)1);
    }
    return to_string(bron_kerbosch(0, all_nodes, 0));
}
