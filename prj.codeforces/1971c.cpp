#include <iostream>

void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    bool c_betw = (c > a && c < b);
    bool d_betw = (d > a && d < b);

    if (c_betw != d_betw) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
