#include <bits/stdc++.h>

using namespace std;

array<int, 2000> a;
int lis[2000], lds[2000];
int n;

int main() {
    cin >> n;
    assert(n <= 2000);
    for (int i = 0; i < n; i++) cin >> a[i];
    reverse(a.begin(), a.begin() + n);
    if (n == 0) {
        cout << 0 << "\n";
        return 0;
    }

    memset(lis, 0, sizeof(lis));
    memset(lds, 0, sizeof(lds));
    int best = 1;
    lds[0] = lis[0] = 1;
    for (int i = 1; i < n; i++) {
        int h, l, v;
        lds[i] = lis[i] = 1;
        v = a[i];
        h = l = i;
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] < v && lis[j] >= lis[i]) lis[i] = lis[j] + 1;
            if (a[j] > v && lds[j] >= lds[i]) lds[i] = lds[j] + 1;
        }
        best = max(best, lis[i] + lds[i] - 1);
    }

    
    cout << best << "\n";
}
