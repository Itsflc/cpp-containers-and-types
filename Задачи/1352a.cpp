#include <iostream>

void solve() {
    int numb;
    std::cin >> numb;
    int res[5];
    int cnt = 0;
    int mult = 1;

    while (numb > 0) {
        int digit = numb % 10;
        if (digit != 0) {
            res[cnt] = digit * mult;
            cnt++;}
        numb /= 10;
        mult *= 10;
    }
    std::cout << cnt << "\n";
    for (int i = 0; i < cnt; ++i) {
        std::cout << res[i];
        if (i < cnt - 1) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}

int main() {
    int tr = 0;
    std::cin >> tr;
    while (tr--) {
        solve();
    }
}

