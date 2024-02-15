#include <bits/stdc++.h>

using std::cin;
using std::string;
using std::cout;

constexpr uint64_t modulus = 1000000009;

uint64_t num_zeroes_with_length(uint64_t n) {
    // 2 ^ (n-1) * n
    return (1 << (n-1)) * n;
}

int main(int argc, char** argv) {
    string s;
    cin >> s;
    uint64_t questionmarks, toadd, thusfar, dimensions;
    questionmarks = 0;
    toadd = 0;
    thusfar = 0;
    dimensions = 1;

    for (auto c : s) {
        if (c == '?') dimensions = (dimensions * 2) % modulus;
    }
    for (auto c : s) {
        if (c == '?' || c == '0') {
            thusfar = (thusfar + toadd) % modulus;
        }
        if (c == '?') {
            questionmarks++;
            toadd = (toadd + num_zeroes_with_length(questionmarks)) % modulus;
        } else if (c == '1') {
            toadd = (toadd + dimensions) % modulus;
        }
    }
    cout << thusfar << "\n";
    return 0;
}