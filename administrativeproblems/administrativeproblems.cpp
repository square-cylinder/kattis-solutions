#include <bits/stdc++.h>
#include <iostream>
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
    i32 num_cases;
    cin >> num_cases;
    for (i32 i = 0; i < num_cases; i++) {
        cout << solve();
    }
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

struct CarType {
    i32 catalouge_price, pickupcost, cost_per_km;
};

struct Spy {
    i32 bill;
    i32 current_car;
};

string solve() {
    i32 num_cartypes, num_events;
    cin >> num_cartypes >> num_events;
    umap<string, i32> car_type_to_index;
    vector<CarType> car_types;
    car_types.reserve(num_cartypes);
    for (i32 i = 0; i < num_cartypes; i++) {
        string name;
        CarType car;
        cin >> name >> car.catalouge_price >> car.pickupcost >> car.cost_per_km;
        car_types.emplace_back(car);
        car_type_to_index[name] = i;
    }
    i32 prevtime = 0;
    map<string, Spy> spies;
    for (i32 i = 0; i < num_events; i++) {
        string spy; 
        char event;
        i32 time;
        cin >> time >> spy >> event;
        if (time < prevtime) {
            assert(false && "Events are not in order");
        }
        prevtime = time;
        if (!contains(spies, spy)) {
            spies[spy] = {0, -1};
        }
        Spy& s = spies[spy];
        if (s.bill == -1) {
            cin.ignore(1000, '\n');
            continue;
        }

        if (event == 'p') {
            string cartype;
            cin >> cartype;
            i32 car_index = car_type_to_index[cartype];
            if (s.current_car != -1) {
                s.bill = -1;
            } else {
                s.current_car = car_index;
                s.bill += car_types[car_index].pickupcost;
            }
        } else if (event == 'r') {
            i32 distance;
            cin >> distance;
            if (s.current_car == -1) {
                s.bill = -1;
            } else {
                s.bill += distance * car_types[s.current_car].cost_per_km;
                s.current_car = -1;
            }
        } else if (event == 'a') {
            i32 percentage;
            cin >> percentage;
            if (s.current_car == -1) {
                s.bill = -1;
            } else {
                s.bill += (car_types[s.current_car].catalouge_price * percentage + 99) / 100;
            }
        }
    }
    stringstream ss;
    for (const auto& [name, spy] : spies) {
        ss << name << " ";
        if (spy.bill == -1 || spy.current_car != -1) {
            ss << "INCONSISTENT\n";
        } else {
            ss << spy.bill << "\n";
        }
    }
    return ss.str();
}