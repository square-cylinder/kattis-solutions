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

string solve();

i32 main(i32 argc, char** argv) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << solve();
    return 0;
}

/////////BEGINNING OF SOLUTION//////////

constexpr i64 MOD = 1000000007;

class Node {
public:
    Node() = default;

    static Node with_op(char op) { Node r; r.op = op; return r; }
    static Node leaf(i64 val) { Node r; r.op = 'c'; r.value = val; r.left = val; r.right = val; r.mult_terms = false; return r; }

    char get_op() const { return op; }

    i64 eval() const { return value; }

    void calculate(const Node& lchild, const Node& rchild) {
        if (op == 'c')
            return;
        
        // [lch.value             ] + [rch.value             ]
        // [a_left + ... + a_right] + [b_left + ... + b_right]
        //  ^left                                     ^right
        if (op == '+') { // a_left + ... + a_right + b_left + ... + b_right
            value = (lchild.value + rchild.value) % MOD;
            left = lchild.left;
            right = rchild.right;
            mult_terms = true;
            return;
        }
        assert(op == '*');
        // [lch.value - lch.right] + [lch.right * rch.left] + [rch.value - rch.left]
        // [a_left + ...         ] + [a_right   * b_left  ] + [... + b_right       ]
        //  ^left (=lch.left)                                        ^right (=rch.right)
        if (lchild.mult_terms && rchild.mult_terms) {
            left = lchild.left;
            right = rchild.right;
            value = ( lchild.value - lchild.right
                    + lchild.right * rchild.left
                    + rchild.value - rchild.left ) % MOD;
            mult_terms = true;
            return;
        }
        // [lch.value - lch.right] + [lch.right * rch.value]
        // [a_left + ...         ] + [a_right   *   b_value]
        //  ^left (=lch.left)         ^          right    ^
        if (lchild.mult_terms) {
            left = lchild.left;
            right = (lchild.right * rchild.value) % MOD;
            value = (lchild.value - lchild.right + lchild.right * rchild.value) % MOD;
            mult_terms = true;
            return;
        }
        // [lch.value * rch.left] + [rch.value - rch.left]
        // [a         * b_left  ] + [    ... + b_right   ]
        //  ^left              ^               ^right (=rch.right)
        if (rchild.mult_terms) {
            left = (lchild.value * rchild.left) % MOD;
            right = rchild.right;
            value = (lchild.value * rchild.left + rchild.value - rchild.left) % MOD;
            mult_terms = true;
            return;
        }
        // a * b
        value = (lchild.value * rchild.value) % MOD;
        left = value;
        right = value;
        mult_terms = false;
    }
private:
    Node(char op, bool has_more_than_one_term, i64 left, i64 right, i64 value) : op(op), mult_terms(has_more_than_one_term), left(left), right(right), value(value) {}

    char op;
    bool mult_terms;
    i64 left, right, value;
};

class Expr {
public:
    Expr(i32 num_ints, const string& expr) {
        i32 size = 1;
        while (size < num_ints)
            size *= 2;
        nodes.resize(2*size);
        op_indexes.resize(size);
        vector<tuple<bool, i32, i32, i32>> stack;
        stack.emplace_back(false, 0, 0, size-1);
        while (!stack.empty()) {
            auto [evaluate, index, lo, hi] = stack.back();
            if (evaluate) {
                nodes[index].calculate(nodes[2*index+1], nodes[2*index+2]);
                stack.pop_back();
                continue;
            }
            stack.back() = {true, index, lo, hi};
            if (lo == hi) {
                if (lo * 2 >= expr.size())
                    nodes[index] = Node::leaf(1);
                else
                    nodes[index] = Node::leaf(expr[lo*2] - '0');
            } else {
                i32 mid = (lo + hi) / 2;
                op_indexes[mid] = index;
                if (mid*2+1 >= expr.size())
                    nodes[index] = Node::with_op('*');
                else
                    nodes[index] = Node::with_op(expr[mid*2+1]);
                stack.emplace_back(false, 2*index+1, lo, mid);
                stack.emplace_back(false, 2*index+2, mid+1, hi);
            }
        }
    }

    i64 eval() const {
        return nodes[0].eval();
    }

    void swap(i32 i, i32 j) {
        i32 first = nodes.size() / 2 - 1;
        i32 ind1 = first + i;
        i32 ind2 = first + j;
        i32 c1 = nodes[ind1].eval();
        i32 c2 = nodes[ind2].eval();
        change_constant(ind1, c2);
        change_constant(ind2, c1);
    }

    void flip(i32 i) {
        i32 ind = op_indexes[i];
        char op = nodes[ind].get_op();
        if (op == '+')
            change_operator(ind, '*');
        else if (op == '*')
            change_operator(ind, '+');
        else { assert(false); }
    }

private:

    void propagate_change(i32 index) {
        if (index == 0)
            return;
        i32 parent = (index - 1) / 2;
        nodes[parent].calculate(nodes[2*parent+1], nodes[2*parent+2]);
        propagate_change(parent);
    }

    void change_constant(i32 index, i32 value) {
        nodes[index] = Node::leaf(value);
        propagate_change(index);
    }

    void change_operator(i32 index, char op) {
        nodes[index] = Node::with_op(op);
        nodes[index].calculate(nodes[2*index+1], nodes[2*index+2]);
        propagate_change(index);
    }

    vector<i32> op_indexes;
    vector<Node> nodes;
};

string solve() {
    i32 num_ints, num_queries;
    cin >> num_ints >> num_queries;

    string expr_str;
    cin >> expr_str;
    stringstream flipped_str;
    for (i32 i = 0; i < expr_str.size(); i++) {
        if (expr_str[i] == '+')
            flipped_str << '*';
        else if (expr_str[i] == '*')
            flipped_str << '+';
        else
            flipped_str << expr_str[i];
    }
    Expr e1(num_ints, expr_str);
    Expr e2(num_ints, flipped_str.str());

    Expr& cur = e1;
    Expr& flipped = e2;

    stringstream output;
    output << cur.eval() << "\n";

    while (num_queries--) {
        char q;
        cin >> q;
        if (q == 's') {
            i32 i, j;
            cin >> i >> j;
            i--; j--;
            cur.swap(i, j);
            flipped.swap(i, j);
        } else if (q == 'f') {
            i32 i;
            cin >> i;
            i--;
            cur.flip(i);
            flipped.flip(i);
        } else if (q == 'a') {
            std::swap(cur, flipped);
        } else {
            assert(false);
        }
        output << cur.eval() << "\n";
    }

    return output.str();
}