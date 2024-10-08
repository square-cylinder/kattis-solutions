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
#ifdef MULTIPLE_CASES
i32 n;
cin >> n;
while(n--)
#endif
    cout << solve() << "\n";
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

i32 num_stars(i32 rank) {
    if (rank >= 21) {
        return 2;
    }
    if (rank >= 16) {
        return 3;
    }
    if (rank >= 11) {
        return 4;
    }
    if (rank >= 1) {
        return 5;
    }
    return 999;
}

string solve() {
    string history;
    cin >> history;
    i32 stars = 0;
    i32 rank = 25;
    i32 consecutive = 0;
    for (auto m : history) {
        i32 star_gain = 0;
        if (m == 'W') {
            star_gain += 1;
            consecutive += 1;
            if (rank >= 6 && consecutive >= 3) {
                star_gain += 1;
            }
        } else {
            consecutive = 0;
            if (1 <= rank && rank <= 20) {
                star_gain -= 1;
            }
        }
        stars += star_gain;
        if (stars < 0 && rank == 20) {
            stars = 0;
        } if (stars < 0) {
            rank += 1;
            stars = num_stars(rank) - 1;
        } else if (stars > num_stars(rank)) {
            stars -= num_stars(rank);
            rank -= 1;
            assert(stars == 1 || stars == 2);
        }
        if (rank == 0) {
            return "Legend";
        }
    }
    return to_string(rank);
}
