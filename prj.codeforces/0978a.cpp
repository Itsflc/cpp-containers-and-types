#include<iostream>
#include<vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int>all(n);
    for (int i = 0; i < n; i++) {
        std::cin >> all[i];
    }
    std::vector<int>result(n);
    int unique = 0;

    std::vector<bool>was(1001, false);

    for (int i = n - 1; i > -1; i--) {
        int current = all[i];
        
        if (not was[current]) {
            result[unique] = current;
            unique++;
            was[current] = true;
        }
    }
    std::cout << unique << std::endl;
 
    for (int i = unique - 1; i > -1; i--) {
        std::cout << result[i] << " ";}
}
