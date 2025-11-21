#include <iostream>
 
int main() {
    long long n, k;
    std::cin >> n >> k;
    
    long long tran = (n + 1) / 2;
    
    if (k <= tran) {
        std::cout << 2 * k - 1;
    } else {std::cout << 2 * (k - tran);}
}
