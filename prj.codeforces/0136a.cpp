#include<iostream>
#include<vector>

int main(){
    int n;
    std::cin >> n;
    std::vector<int>friends(n);
    std::vector<int>result(n);
    
    for (int i = 0; i < n; i++){
        std::cin >> friends[i];
    }
    for (int j = 0; j < n; j++){
       result[friends[j] - 1] = j + 1;
    }
    for (int k = 0; k < n; k++){
        std::cout << result[k] << ' ';
    }
}
