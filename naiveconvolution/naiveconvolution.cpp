#include <bits/stdc++.h>

using namespace std;

using ll = __int128;

int main() {
    int n, m;
    cin >> n >> m;
    vector<ll> p1(n), p2(m), p3(n + m);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        p1[i] = x;
    }
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        p2[i] = x;
    }
    for (int s = 0; s < n + m; s++) {
        for (int i = 0; i < n; i++) {
            int j = s - i;
            if (j < 0 || j >= m) continue;
            p3[s] += p1[i] * p2[j];
        }
    }
    while (p3.size() > 1 && p3.back() == 0) p3.pop_back();
    for (int i = 0; i < p3.size(); i++) {
        string s;
        bool is_negative = p3[i] < 0;
        if (is_negative) p3[i] *= -1;
        for (; p3[i]; p3[i] /= 10) {
            s.push_back('0' + (p3[i] % 10));
        }
        if (s.size() == 0) s = "0";
        if (is_negative) s.push_back('-');
        std::reverse(s.begin(), s.end());
        cout << s;
        if (i != p3.size() - 1) cout << " ";
    }
    
    cout << "\n";
}
