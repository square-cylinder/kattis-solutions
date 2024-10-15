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
using u128 = __uint128_t;
string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    do {
        cout << solve() << "\n";
    } while(getline(cin, line));
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

u128 adj_mat[128];

i32 num_maximal;
void bron_kerbosch(u128 r, u128 p, u128 x) {
    if (num_maximal > 1005) {
        return;
    }
    if (p == 0 && x == 0) {
        num_maximal++;
        return;
    }
    if (!p) return;
    i32 u = 0;
    u128 pivoted;
    u128 pUx = p | x;
    for (u128 i = 0; i < 128; i++) {
        if (pUx & (((u128)1) << i)) {
            pivoted = p & ~adj_mat[i];
        }
    }
    for (u128 i = 0; i < 128; i++) {
        u128 v = ((u128)1) << i;
        if (!(v & pivoted)) continue;
        bron_kerbosch(r | v, p & adj_mat[i], x & adj_mat[i]);
        p = p & ~v;
        x = x | v;
    }
}

string solve() {
    memset(adj_mat, 0, sizeof(adj_mat));
    num_maximal = 0;
    i32 n, m;
    cin >> n >> m;
    while (m--) {
        i32 a, b;
        cin >> a >> b;
        a--; b--;
        adj_mat[a] |= (((u128)1) << (u128)b);
        adj_mat[b] |= (((u128)1) << (u128)a);
    }
    cin.ignore();
    u128 all_nodes = 0;
    while (n--) {
        all_nodes <<= ((u128)1);
        all_nodes |= ((u128)1);
    }
    bron_kerbosch(0, all_nodes, 0);
    if (num_maximal > 1000) {
        return "Too many maximal sets of friends.";
    }
    return to_string(num_maximal);
}
