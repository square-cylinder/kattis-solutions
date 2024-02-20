#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
    int num_ch, num_ch_dep;
    cin >> num_ch >> num_ch_dep;
    // number of pages, dependency
    vector<pair<int,int>> chapters;
    chapters.reserve(num_ch + 1);
    chapters.emplace_back(0, -1);
    for (int i = 0; i < num_ch; i++) {
        int num_pages;
        cin >> num_pages;
        chapters.emplace_back(num_pages, 0);
    }
    vector<bool> has_dep;
    has_dep.resize(num_ch + 1, false);
    has_dep[0] = true;
    // back edges 
    vector<vector<int>> depending;
    depending.resize(num_ch + 1);
    for (int i = 0; i < num_ch_dep; i++) {
        int pre, post;
        cin >> pre >> post;
        chapters[post].second = pre;
        has_dep[pre] = true;
        depending[pre].emplace_back(post);
    }
    vector<int> culcon;
    for (int i = 1; i < num_ch + 1; i++) {
        if (!has_dep[i]) {
            culcon.emplace_back(i);
        }
        if (chapters[i].second == 0) {
            depending[0].emplace_back(i);
        }
    }
    int smallesttotal = INT_MAX;
    for (int first : culcon) {
        vector<bool> read_stuff;
        read_stuff.resize(num_ch+1);
        read_stuff[first] = true;
        int subtotalpages = 0;
        int cur_ch = first;
        int smallstuff = INT_MAX;
        while (true) {
            auto [num_pages, dep] = chapters[cur_ch];
            if (dep == -1)
                break;
            subtotalpages += num_pages;
            read_stuff[dep] = true;
            cur_ch = dep;
            vector<pair<int, int>> dfs;
            dfs.emplace_back(0, cur_ch);
            while (!dfs.empty()) {
                auto [pages, search_ch] = dfs.back();
                dfs.pop_back();
                if (depending[search_ch].empty()) {
                    if (pages < smallstuff) {
                        smallstuff = pages;
                    }
                    continue;
                }
                for (int next_ch : depending[search_ch]) {
                    if (read_stuff[next_ch])
                        continue;
                    dfs.emplace_back(pages + chapters[next_ch].first, next_ch);
                }
            }
        }
        if (subtotalpages + smallstuff < smallesttotal) {
            smallesttotal = subtotalpages + smallstuff;
        }
    }
    cout << smallesttotal << "\n";
    return 0;
}