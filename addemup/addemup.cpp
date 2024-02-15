#include <bits/stdc++.h>

using namespace std;

optional<uint64_t> flip_card(uint64_t card) {
    char flipped_digits[] = {0, 1, 2, -1, -1, 5, 9, -1, 8, 6};
    uint64_t out = 0;
    while (card > 0) {
        const uint64_t digit = card % 10;
        if (flipped_digits[digit] == -1) {
            return {};
        }
        out *= 10;
        out += flipped_digits[digit];
        card /= 10;
    }
    return out;
}

int main(int argc, char** argv) {
    uint64_t num_cards, target_sum;
    cin >> num_cards >> target_sum;

    vector<pair<uint64_t, int>> cards;
    cards.reserve(num_cards * 2);
    for (int i = 0; i < num_cards; i++) {
        uint64_t card;
        cin >> card;
        cards.emplace_back(card, i);
        optional<uint64_t> flipped;
        flipped = flip_card(card);
        if (flipped.has_value()) {
            cards.emplace_back(flipped.value(), i);
        }
    }
    sort(cards.begin(), cards.end());

    bool possible = false;
    int lo = 0, hi = cards.size() - 1;
    while (lo < hi) {
        uint64_t sum = cards[lo].first + cards[hi].first;
        if (sum < target_sum) {
            lo++;
        } else if (sum > target_sum) {
            hi--;
        } else if (cards[lo].second != cards[hi].second) {
            possible = true;
            break;
        } else {
            lo++;
        }
    }
    if (possible) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}