#include <bits/stdc++.h>

/*
 * Took me a while to figure out what you have to do here so I
 * will briefly go through what I have done (with some help 
 * from other peoples solutions on github).
 * 
 * Basically we have a 2d grid of booleans to keep track of which
 * states are reachable given the current numbers we have been given.
 * A state here is referring to what the first cd could be and second
 * cd could be. Initially, we can only reach state 0, 0 therefore 
 * reachable[0][0] is set to true in the beginning.
 *
 * The way we update it with a new number is that we go through the
 * grid and if we find a reachable state we will mark the other
 * positions we can reach by adding this new number to sum1 or sum2 as true.
 * 
 * We have to be careful not to update from a reachable state that we just marked as
 * reachable for this iteration as this will result in the wrong answer. To
 * deal with this we can go through the grid "backwards" as we will not update
 * any states in that direction.
 *
 * Finally, because sum1 + sum2 = sum2 + sum1, we only have to keep track of
 * the states where sum1 >= sum2 which will effectively cut the amount of 
 * computation in half.
 * 
 * In the end we just iterate through all possible sums we could have gotten
 * and if they are reachable, we consider it for an answer.
*/

using namespace std;

using vbool2d = vector<vector<bool>>;

void update_reachable(vbool2d& reachable, int item, int limit) {
    for (int sum1 = limit; sum1 >= 0; sum1--) {
        for (int sum2 = sum1; sum2 >= 0; sum2--) {
            if (!reachable[sum1][sum2])
                continue;

            if (sum1 + item <= limit) {
                reachable[sum1+item][sum2] = true;
            }
            if (sum2 + item <= limit) {
                int greater = sum1;
                int lesser = sum2 + item;
                if (lesser > greater) {
                    greater = lesser;
                    lesser = sum1;
                }
                reachable[greater][lesser] = true;
            }
        }
    }
}

int main(int argc, char **argv) {
    int cdlimit, amt_music;
    cin >> cdlimit >> amt_music;

    vbool2d reachable;
    reachable.resize(cdlimit+1);
    for (vector<bool>& row : reachable) {
        row.resize(cdlimit + 1, false);
    }

    reachable[0][0] = true;
    for (int i = 0; i < amt_music; i++) {
        int item;
        cin >> item;
        update_reachable(reachable, item, cdlimit);
    }

    int best1 = 0;
    int best2 = 0;
    for (int sum1 = 0; sum1 < cdlimit + 1; sum1++) {
        for (int sum2 = 0; sum2 <= sum1; sum2++) {
            if (!reachable[sum1][sum2])
                continue;
            const int cursum = best1 + best2;
            const int thissum = sum1 + sum2;
            const int curdiff = best1 - best2;
            const int thisdiff = sum1 - sum2;
            if (thissum > cursum || (thissum == cursum && thisdiff < curdiff)) {
                best1 = sum1;
                best2 = sum2;
            }
        }
    }

    cout << best1 << " " << best2 << "\n";

    return 0;
}