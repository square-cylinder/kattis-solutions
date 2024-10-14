#include <bits/stdc++.h>
#include <iomanip>

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
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

struct Cat {
    bool is_female;
    i32 dom_b, dom_o, dom_d;
    static Cat parse(const string& s) {
        Cat c;
        c.dom_b = c.dom_d = c.dom_o = 0;
        if (s.size() == 6) {
            c.is_female = true;
            if (s[5] == 'O') c.dom_o++;
        } else {
            c.is_female = false;
        }
        if (s[4] == 'O') c.dom_o++;
        if (s[0] == 'B') c.dom_b++;
        if (s[1] == 'B') c.dom_b++;
        if (s[2] == 'D') c.dom_d++;
        if (s[3] == 'D') c.dom_d++;
        return c;
    }

    string get_color() {
        if (dom_o == 0) {
            if (dom_b >= 1 && dom_d >= 1) return "Black";
            if (dom_b >= 1 && dom_d == 0) return "Blue";
            if (dom_b == 0 && dom_d >= 1) return "Chocolate";
            if (dom_b == 0 && dom_d == 0) return "Lilac";
        } else if ((dom_o == 2 && is_female) || (dom_o == 1 && !is_female)) {
            if (dom_d >= 1) return "Red";
            if (dom_d == 0) return "Cream";
        } else if (is_female && dom_o == 1){
            if (dom_b >= 1) {
                if (dom_d >= 1) return "Black-Red Tortie";
                if (dom_d == 0) return "Blue-Cream Tortie";
            }
            if (dom_b == 0) {
                if (dom_d >= 1) return "Chocolate-Red Tortie";
                if (dom_d == 0) return "Lilac-Cream Tortie";
            }
        }
        cerr << "bro... " << to_string() << "\n";
        assert(false);
    }

    string to_string() {
        stringstream out;
        for (i32 i = 0; i < 2; i++) {
            if (i < dom_b) out << 'B';
            else out << 'b';
        }
        for (i32 i = 0; i < 2; i++) {
            if (i < dom_d) out << 'D';
            else out << 'd';
        }
        if (is_female) {
            for (i32 i = 0; i < 2; i++) {
                if (i < dom_o) out << 'O';
                else out << 'o';
            }
        } else {
            out << (dom_o > 0 ? 'O' : 'o');
        }
        if (is_female) out << " (female)";
        else out << " (male)";
        return out.str();
    }

    vector<Cat> breed(const Cat& other) {
        assert(is_female != other.is_female);
        const Cat *female = this;
        const Cat *male = &other;
        if (!is_female) {
            female = &other;
            male = this;
        }
        vector<Cat> children;
        for (i32 g1f = 0; g1f < 2; g1f++) for (i32 g1m = 0; g1m < 2; g1m++) {
            for (i32 g2f = 0; g2f < 2; g2f++) for (i32 g2m = 0; g2m < 2; g2m++) {
                for (i32 g3f = 0; g3f < 2; g3f++) for (i32 gender = 0; gender < 2; gender++) {
                    Cat c;
                    c.is_female = gender == 0;
                    c.dom_b = c.dom_d = c.dom_o = 0;
                    if (g1f < female->dom_b) c.dom_b++;
                    if (g1m < male->dom_b) c.dom_b++;
                    if (g2f < female->dom_d) c.dom_d++;
                    if (g2m < male->dom_d) c.dom_d++;
                    if (g3f < female->dom_o) c.dom_o++;
                    if (c.is_female && male->dom_o > 0) c.dom_o++;
                    children.emplace_back(c);
                }
            }
        }
        return children;
    }
};

vector<string> uniform_wildcards(const string& s) {
    vector<string> v(1);
    for (u32 i = 0; i < s.size(); i++) {
        if (s[i] == '-') {
            char c;
            if (i < 2) c = 'b';
            else if (i < 4) c = 'd';
            else c = 'o';
            i32 iterations = v.size();
            for (i32 j = 0; j < iterations; j++) {
                v.emplace_back(v[j]);
                v.back() += toupper(c);
                v[j] += c;
            }
        } else {
            for (auto& x : v) {
                x += s[i];
            }
        }
    }
    return v;
}

map<string, string> genes_from_color = {
{"Black",               "B-D-oo"}, 
{"Blue",                "B-ddoo"}, 
{"Chocolate",           "bbD-oo"}, 
{"Lilac",               "bbddoo"}, 
{"Red",                 "--D-OO"}, 
{"Cream",               "--ddOO"}, 
{"Black-Red Tortie",    "B-D-Oo"}, 
{"Blue-Cream Tortie",   "B-ddOo"}, 
{"Chocolate-Red Tortie","bbD-Oo"}, 
{"Lilac-Cream Tortie",  "bbddOo"}, 
};

string solve() {
    string male_color, female_color;
    getline(cin, female_color);
    getline(cin, male_color);
    vector<Cat> males;
    vector<Cat> females;
    for (auto& s : uniform_wildcards(genes_from_color[male_color])) {
        s.pop_back();
        males.emplace_back(Cat::parse(s));
    }
    for (auto& s : uniform_wildcards(genes_from_color[female_color])) {
        females.emplace_back(Cat::parse(s));
    }
    for (auto& c : males) {
        if (c.get_color() != male_color || c.is_female) {
            cerr << "Something went wrong with males: " << c.to_string() << " - " << c.get_color() << "\n";
            exit(1);
        }
    }
    for (auto& c : females) {
        if (c.get_color() != female_color || !c.is_female) {
            cerr << "Something went wrong with females: " << c.to_string() << " - " << c.get_color() << "\n";
            exit(1);
        }
    }
    map<string, i32> counts;
    for (auto& m : males) for (auto& f : females) {
        auto children = m.breed(f);
        for (auto& c : children) {
            counts[c.get_color()]++;
        }
    }
    vector<pair<i32, string>> bruh;
    i32 total = 0;
    for (auto&[color, count] : counts) {
        bruh.emplace_back(-count, color);
        total += count;
    }
    sort(bruh.begin(), bruh.end());
    for (auto&[count, color] : bruh) {
        cout << color << " " << fixed << setprecision(9) << (double)-count / (double)total << "\n";
    }

    stringstream out;
    return out.str();
}
