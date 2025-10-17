#include<iostream>

int main(){
    int n;
    int k;
    std::cin >> n >> k;
    while(k--){
        if (n % 10 != 0) n--;
        else {n /= 10;}
    }
    std::cout << n;
}
