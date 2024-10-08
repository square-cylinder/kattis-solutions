#include <bits/stdc++.h>
#include <queue>

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
    while (cin >> n) {
        cout << solve(n) << "\n";
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

string solve(i32 n) {
    vector<i32> s;
    queue<i32> q;
    priority_queue<i32> pq;
    i32 sb = 1, qb = 1, pqb = 1;
    while (n--) {
        i32 cmd, x;
        cin >> cmd >> x;
        if (cmd == 1) {
            s.emplace_back(x);
            q.emplace(x);
            pq.emplace(x);
        } else if (cmd == 2) {
            i32 res;
            if (s.empty()) {
                sb = 0;
                qb = 0;
                pqb = 0;
                continue;
            }
            res = s.back();
            s.pop_back();
            if (res != x) {
                sb = 0;
            }
            res = q.front();
            q.pop();
            if (res != x) {
                qb = 0;
            }
            res = pq.top();
            pq.pop();
            if (res != x) {
                pqb = 0;
            }
        }
    }
    if (sb + qb + pqb > 1) {
        return "not sure";
    }
    if (!sb && !qb && !pqb) {
        return "impossible";
    }
    if (sb) {
        return "stack";
    }
    if (qb) {
        return "queue";
    }
    return "priority queue";
}  