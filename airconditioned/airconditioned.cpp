#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** arv) {
    int num_minions;
    cin >> num_minions;
    // stored as {end, start} because I want to sort on the end
    vector<pair<int, int>> intervals;
    for (int i = 0; i < num_minions; i++) {
        int l, h;
        cin >> l >> h;
        intervals.emplace_back(h, l);
    }
    sort(intervals.begin(), intervals.end());
    int prev_selected = -1;
    int num_rooms = 0;
    for (int i = 0; i < intervals.size(); i++) {
        if (intervals[i].second > prev_selected) {
            prev_selected = intervals[i].first;
            num_rooms++;
        }
    }
    cout << num_rooms << "\n";
    return 0;
}