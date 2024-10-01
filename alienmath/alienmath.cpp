#include <bits/stdc++.h>
#include <string>

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
    i32 unique_digits;
    cin >> unique_digits;
    vector<string> digits = input_vec<string>(unique_digits);
    string number;
    cin >> number;
    i32 outnumber = 0;
    i32 mag = 1;
    for (i32 i = number.size() - 1; i >= 0; ) {
        for (i32 digit_index = 0; digit_index < unique_digits; digit_index++) {
            string& digit = digits[digit_index];
            bool match = true;
            for (i32 j = digit.size() - 1; j >= 0; j--) {
                if (number[i] != digit[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                i -= digit.size();
                outnumber += digit_index * mag;
                mag *= unique_digits;
                break;
            }
        }
    }
    return to_string(outnumber);
}