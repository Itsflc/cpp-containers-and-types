#include <iostream>
#include<cmath>
 
int main() {
    char ch;
    int w = 0;
    while (true) {
        std::cin >> ch;
        if (ch == '1') break;
        if (ch == '0') w++;
    }
    int i = w % 5 + 1;
    int j = w/5 + 1;
    std::cout << std::abs(i - 3) + std::abs(j-3);
}
