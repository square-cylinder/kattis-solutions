#include <bits/stdc++.h>

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

string solve(const string& goal);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string line;
    getline(cin, line);
    while (line[0] != '*') {
        //line.pop_back();
        cout << solve(line) << "\n";
        getline(cin, line);
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

char keyboard[4][10][2] = {
    { {'q','Q'}, {'w','W'}, {'e','E'}, {'r','R'}, {'t','T'}, {'y','Y'}, {'u','U'}, {'i','I'}, {'o','O'}, {'p','P'} },
    { {'a','A'}, {'s','S'}, {'d','D'}, {'f','F'}, {'g','G'}, {'h','H'}, {'j','J'}, {'k','K'}, {'l','L'}, {';',':'} },
    { {'z','Z'}, {'x','X'}, {'c','C'}, {'v','V'}, {'b','B'}, {'n','N'}, {'m','M'}, {',','<'}, {'.','>'}, {'/','?'} },
    { {'$','$'}, {'$','$'}, {' ',' '}, {' ',' '}, {' ',' '}, {' ',' '}, {' ',' '}, {' ',' '}, {'$','$'}, {'$','$'} }
};

u32 encode(i32 index, i8 r1, i8 c1, i8 r2, i8 c2) {
    if (r1 > r2 || (r1 == r2 && c1 > c2)) {
        std::swap(r1, r2);
        std::swap(c1, c2);
    }
    u32 val = index;
    val <<= 2;
    val |= r1;
    val <<= 2;
    val |= r2;
    val <<= 7;
    u32 combined = c1 * 10 + c2; // < 128
    val |= combined;
    // 2 + 2 + 7 + 7 = 18 bits (7 for index)
    return val;
}

void decode(u32 val, i32& index, i8& r1, i8& c1, i8& r2, i8& c2) {
    c2 = (val & 0b1111111) % 10;
    c1 = (val & 0b1111111) / 10;
    val >>= 7;
    r2 = val & 0b11;
    val >>= 2;
    r1 = val & 0b11;
    val >>= 2;
    index = val;
}

i32 dr[8] = { -1, -1, 1, 1, -2, -2, 2, 2 };
i32 dc[8] = { -2, 2, -2, 2, -1, 1, -1, 1 };

string solve(const string& goal) {
    vector<bool> visited(1 << 18, false);
    vector<u32> dfs;
    dfs.emplace_back(encode(0, 3, 0, 3, 9));
    while (!dfs.empty()) {
        u32 val = dfs.back();
        dfs.pop_back();
        if (visited[val]) continue;
        visited[val] = true;
        i32 index;
        i8 r[2], c[2];
        decode(val, index, r[0], c[0], r[1], c[1]);
        if (index == goal.size()) {
            return "1";
        }
        for (i32 i = 0; i < 2; i++) {
            for (i32 j = 0; j < 8; j++) {
                i8 nr = r[i] + dr[j];
                i8 nc = c[i] + dc[j];
                i32 other = 1 ^ i;
                bool is_shift = keyboard[r[other]][c[other]][0] == '$';
                if (nr == r[other] && nc == c[other]) continue;
                if (0 <= nr && nr < 4 && 0 <= nc && nc < 10) {
                    if (keyboard[nr][nc][is_shift] == goal[index]) {
                        u32 next = encode(index+1,nr,nc,r[other],c[other]);
                        if (!visited[next])
                            dfs.emplace_back(next);
                    } else if (keyboard[nr][nc][is_shift] == '$') {
                        u32 next = encode(index,nr,nc,r[other],c[other]);
                        if (!visited[next])
                            dfs.emplace_back(next);
                    }
                } 
            }
        }
    }
    return "0";
}