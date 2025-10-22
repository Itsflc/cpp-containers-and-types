#include<iostream>
#include<cmath>

void solve(){
    int k, x;
    std::cin >> k >> x;
    long long result = x * std::pow(2, k);
    std::cout << result << std::endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}

