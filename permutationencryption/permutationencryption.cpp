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

string solve(i32 n);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    i32 n;
    while (cin >> n && n) {
        cout << solve(n) << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve(i32 n) {
    vector<i32> perm(n);
    for (i32 i = 0; i < n; i++) {
        cin >> perm[i];
        perm[i]--;
    }
    cin.ignore();
    string input;
    getline(cin, input);
    i32 m_len = input.size();
    if (m_len % n != 0) m_len += n - m_len % n;
    input.resize(m_len, ' ');
    i32 n_blocks = m_len / n;
    stringstream out;
    out << "'";
    for (i32 i = 0; i < n_blocks; i++) {
        for (i32 j = 0; j < n; j++) {
            out << input[i * n + perm[j]];
        }
    }
    out << "'";
    return out.str();
}
