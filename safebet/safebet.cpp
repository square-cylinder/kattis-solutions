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

struct Grid {
    i32 num_rows, num_cols;
    umap<i32, set<i32>> rows;
    umap<i32, set<i32>> cols;
    map<pair<i32, i32>, bool> is_rightslant;
};
 
string solve(const Grid& g);

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    i32 r, c, m, n, i;
    i = 1;
    while (cin >> r >> c >> m >> n) {
        Grid g;
        g.num_rows = r;
        g.num_cols = c;
        for (i32 i = 0; i < m; i++) {
            i32 row, col;
            cin >> row >> col;
            g.rows[row].insert(col);
            g.cols[col].insert(row);
            g.is_rightslant[{row, col}] = true;
        }
        for (i32 i = 0; i < n; i++) {
            i32 row, col;
            cin >> row >> col;
            g.rows[row].insert(col);
            g.cols[col].insert(row);
            g.is_rightslant[{row, col}] = false;
        }
        cout << "Case " << i << ": " << solve(g) << "\n";
        i++;
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

enum class Dir {
    UP, DOWN, LEFT, RIGHT
};

struct Point {
    Point() = default;
    Point(i32 row, i32 col) : row(row), col(col) {}
    i32 row, col;
};

struct LineSeg {
    LineSeg(i32 r1, i32 r2, i32 c1, i32 c2) : r1(r1), r2(r2), c1(c1), c2(c2) { assert(is_horizontal() || is_vertical()); }
    i32 r1, r2, c1, c2;

    bool is_horizontal() const { return r1 == r2; }
    bool is_vertical() const { return c1 == c2; }

    bool contains(const Point& p) const {
        if (is_horizontal()) {
            return p.row == r1 && min(c1, c2) <= p.col && p.col <= max(c1, c2);
        } else {
            return p.col == c1 && min(r1, r2) <= p.row && p.row <= max(r1, r2);
        }
    }

    optional<Point> intersect(const LineSeg& other) const {
        if (is_horizontal() == other.is_horizontal())
            return {};
        Point p;
        if (is_horizontal()) {
            p.row = r1;
            p.col = other.c1;
        } else {
            p.row = other.r1;
            p.col = c1;
        }
        if (this->contains(p) && other.contains(p))
            return p;
        return {};
    }

    bool shares_endpoint(const LineSeg& other) const {
        return r1 == other.r1 && c1 == other.c1 || r1 == other.r2 && c1 == other.c2
            || r2 == other.r1 && c2 == other.c1 || r2 == other.r2 && c2 == other.c2;
    }
};

Point raycast(const Grid& g, i32 r, i32 c, Dir d) {
    if (d == Dir::UP) {
        if (!contains(g.cols, c))
            return Point(0, c);
        const auto& col = g.cols.at(c);
        auto it = col.lower_bound(r);
        if (it == col.begin())
            return Point(0, c);
        return Point(*--it, c);
    }
    if (d == Dir::DOWN) {
        if (!contains(g.cols, c))
            return Point(g.num_rows + 1, c);
        const auto& col = g.cols.at(c);
        auto it = col.upper_bound(r);
        if (it == col.end())
            return Point(g.num_rows + 1, c);
        return Point(*it, c);
    }
    if (d == Dir::LEFT) {
        if (!contains(g.rows, r))
            return Point(r, 0);
        const auto& row = g.rows.at(r);
        auto it = row.lower_bound(c);
        if (it == row.begin())
            return Point(r, 0);
        return Point(r, *--it);
    }
    if (d == Dir::RIGHT) {
        if (!contains(g.rows, r))
            return Point(r, g.num_cols + 1);
        const auto& row = g.rows.at(r);
        auto it = row.upper_bound(c);
        if (it == row.end())
            return Point(r, g.num_cols + 1);
        return Point(r, *it);
    }
    assert(false);
}

Dir reflect(Dir d, bool is_rightslant) {
    switch (d) {
        case Dir::UP: return is_rightslant ? Dir::RIGHT : Dir::LEFT;
        case Dir::DOWN: return is_rightslant ? Dir::LEFT : Dir::RIGHT;
        case Dir::LEFT: return is_rightslant ? Dir::DOWN : Dir::UP;
        case Dir::RIGHT: return is_rightslant ? Dir::UP : Dir::DOWN;
    }
    assert(false);
}

struct Path {
    vector<LineSeg> ver, hor;
};

Path follow_path(const Grid& g, i32 r, i32 c, Dir d) {
    Path p;
    while (true) {
        auto next = raycast(g, r, c, d);
        LineSeg seg(r, next.row, c, next.col);
        if (seg.is_horizontal()) {
            p.hor.emplace_back(seg);
        } else {
            p.ver.emplace_back(seg);
        }
        r = next.row;
        c = next.col;
        if (! (1 <= r && r <= g.num_rows && 1 <= c && c <= g.num_cols) )
            break;
        d = reflect(d, g.is_rightslant.at({r, c}));
    };
    return p;
}

class Fenwick {
public:
    Fenwick(i32 n) : tree(n+1) {}

    void add(i32 i, i64 x) {
        for (; i < tree.size(); i += i & -i)
            tree[i] += x;
    }

    i64 sum(i32 i) const {
        assert(i < (i32)tree.size());
        i64 res = 0;
        for (; i > 0; i -= i & -i)
            res += tree[i];
        return res;
    }

private:
    vector<i64> tree;
};

struct Event {
    Event(i32 a, i32 b, i32 type) : a(a), b(b), type(type) {}
    i32 a, b, type;
};

tuple<i32, i32, i64> intersections(const Grid& g, const vector<LineSeg>& hor, const vector<LineSeg>& ver) {
    i32 solrow, solcol;
    i64 solcount;
    solrow = solcol = INT_MAX;
    solcount = 0;
    map<i32, vector<Event>> events;
    for (const auto& seg : ver) {
        i32 start = min(seg.r1, seg.r2);
        i32 end = max(seg.r1, seg.r2);
        assert(start >= 0 && end <= g.num_rows + 1);
        events[start+1].emplace_back(seg.c1, -1, 1);
        events[end].emplace_back(seg.c1, -1, -1);
    }
    for (const auto& seg : hor) {
        i32 start = min(seg.c1, seg.c2);
        i32 end = max(seg.c1, seg.c2);
        assert(start >= 0 && end <= g.num_cols + 1);
        events[seg.r1].emplace_back(start, end, 0);
    }
    // Strategy, do a sweep line first to find the lexicographically smallest intersection,
    // Then do another sweep line to find the number of intersections with a fenwick tree
    set<i32> active;
    vector<pair<i32, i32>> hori;
    for (const auto& [y, evs] : events) {
        // We should get the lexigraphically smallest intersection first
        if (solrow != INT_MAX)
            break;
        for (const auto& ev : evs) {
            if (ev.type == 1) {
                active.emplace(ev.a);
            } else if (ev.type == -1) {
                active.erase(ev.a);
            } else {
                hori.emplace_back(ev.a, ev.b);
            }
        }
        while (!hori.empty()) {
            auto [c1, c2] = hori.back();
            hori.pop_back();
            auto it = active.upper_bound(c1);
            while (it != active.end() && *it < c2) {
                i32 col = *it;
                if (col < solcol) {
                    solrow = y;
                    solcol = col;
                }
                it++;
            }
        }
    }
    hori.clear();
    Fenwick f(g.num_cols + 1);
    for (const auto& [y, evs] : events) {
        for (const auto& ev : evs) {
            if (ev.type == 1) {
                f.add(ev.a, 1);
            } else if (ev.type == -1) {
                f.add(ev.a, -1);
            } else {
                hori.emplace_back(ev.a, ev.b);
            }
        }
        while (!hori.empty()) {
            auto [c1, c2] = hori.back();
            hori.pop_back();
            solcount += f.sum(c2) - f.sum(c1 - 1);
        }
    }

    return { solrow, solcol, solcount };
}

string solve(const Grid& g) {
    Path from_source = follow_path(g, 1, 0, Dir::RIGHT);
    if (from_source.hor.back().c2 == g.num_cols + 1 && from_source.hor.back().r2 == g.num_rows) {
        return "0";
    }
    Path from_dest = follow_path(g, g.num_rows, g.num_cols + 1, Dir::LEFT);

    auto [solrow, solcol, solcount] = intersections(g, from_source.hor, from_dest.ver);
    auto [bestrow, bestcol, bestcount] = intersections(g, from_dest.hor, from_source.ver);


    solcount += bestcount;
    if (bestrow < solrow || (bestrow == solrow && bestcol < solcol)) {
        solrow = bestrow;
        solcol = bestcol;
    }


    if (solcount > 0)
        return  (stringstream() << solcount << " " << solrow << " " << solcol).str();
    return "impossible";
}