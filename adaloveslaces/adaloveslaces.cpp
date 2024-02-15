#include <bits/stdc++.h>
#include <filesystem>

using namespace std;

struct SearchNode {
    int cur;
    bool first_visit;
    double length;
};

double calc_dist(int from, int to, double s, double d) {
    double dist = static_cast<double>(abs(from - to)) * d;
    return sqrt(s * s + dist * dist);
}

vector<double> get_paths(int N, int d, int s, int t) {
    double s_d, t_d, d_d;
    s_d = static_cast<double>(s);
    t_d = static_cast<double>(t);
    d_d = static_cast<double>(d);
    vector<double> paths;
    // levels that have already been visited
    vector<bool> forbidden;
    forbidden.resize(N, false);
    vector<SearchNode> to_search;
    // At first we have the half s because we needed to tie the two upmost holes
    to_search.emplace_back(SearchNode{0, true, s_d / 2.0});
    while (!to_search.empty()) {
        const SearchNode n = to_search.back();
        // We have reached the final hole(s), we are done with this branch
        if (n.cur == N - 1) {
            paths.emplace_back((n.length + t_d) * 2);
            to_search.pop_back();
            continue;
        }
        // We have explored everything after this node, move on
        if (!n.first_visit) {
            forbidden[n.cur] = false;
            to_search.pop_back();
            continue;
        }
        // We want to explore everything after this node, which will become
        // forbidden, because of symmetry + every hole has one lace (at most)
        forbidden[n.cur] = true;
        to_search.back().first_visit = false;
        // Visit every availible spot on the other side
        for (int i = 0; i < N; i++) {
            if (forbidden[i])
                continue;
            // distance thus far plus hole penalty and geometrical distance
            const double distance =
                t_d + n.length + calc_dist(n.cur, i, s_d, d_d);
            to_search.emplace_back(SearchNode{i, true, distance});
        }
        assert(n.cur < N - 1);
        // Try visiting hole directly under
        if (!forbidden[n.cur + 1]) {
            to_search.emplace_back(
                SearchNode{n.cur + 1, true, n.length + t_d + d_d});
        }
        // Try visiting the hole directly above :(((((((((((((((((((((((
        // I spent over 8 hours trying to figure out why it didn't work
        if (n.cur > 0 && !forbidden[n.cur - 1]) {
            to_search.emplace_back(
                SearchNode{n.cur - 1, true, n.length + t_d + d_d});
        }
    }

    // Will want paths lengths in order
    // sort(paths.begin(), paths.end());
    return paths;
}

int number_options(const vector<double>& distances, double length,
                   double low_bound, double high_bound) {
    int count = 0;
    for (auto distance : distances) {
        const double remaining_distance = (length - distance) / 2.0;
        if (low_bound < remaining_distance && remaining_distance < high_bound) {
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    int N, d, s, t, f_min, f_max;
    vector<int> laces;
    cin >> N >> d >> s >> t >> f_min >> f_max;
    int lace;
    double f_min_d = static_cast<double>(f_min);
    double f_max_d = static_cast<double>(f_max);
    while (cin >> lace) {
        laces.emplace_back(lace);
    }
    // sorted list of all possible threadings
    vector<double> paths = get_paths(N, d, s, t);

    for (auto lace : laces) {
        int options =
            number_options(paths, static_cast<double>(lace), f_min_d, f_max_d);
        cout << options << "\n";
    }

    return 0;
}