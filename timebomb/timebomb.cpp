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
string digits[] = {
    "***   * *** *** * * *** *** *** *** ***",
    "* *   *   *   * * * *   *     * * * * *",
    "* *   * *** *** *** *** ***   * *** ***",
    "* *   * *     *   *   * * *   * * *   *",
    "***   * *** ***   * *** ***   * *** ***"
};

i32 check_digit(const vector<string>& rs, i32 d) {
    for (i32 i = 0; i < 10; i++) {
        bool match = true;
        for (i32 j = 0; j < 5; j++) {
            for (i32 k = 0; k < 3; k++) {
                if (digits[j][i * 4 + k] != rs[j][d * 4 + k]) {
                    match = false;
                    break;
                }
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

string solve() {
    vector<string> rs;
    for (i32 i = 0; i < 5; i++) {
        string s;
        getline(cin, s);
        rs.emplace_back(s);
    }
    i32 num_digits = (rs[0].size() + 1) / 4;
    i32 num = 0;
    for (i32 i = 0; i < num_digits; i++) {
        num *= 10;
        i32 d = check_digit(rs, i);
        if (d == -1) {
            return "BOOM!!";
        }
        num += d;
    }
    if (num % 6 == 0) {
        return "BEER!!";
    }
    return "BOOM!!";
}
