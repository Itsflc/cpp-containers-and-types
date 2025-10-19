#include<iostream>

void solve(){
    int n, m, sm, sn, d;
    std::cin >> n >> m >> sn >> sm >> d;
    bool impossible = false;
    
    if (sm - d < 2 && sn - d < 2) impossible = true;
    else if (sm + d >= m && sn + d >= n) impossible = true;
    else if (sm - d < 2 && sm + d >= m) impossible = true;
    else if (sn - d < 2 && sn + d >= n) impossible = true;
    
    if (!impossible){
        std::cout << n + m - 2 << std::endl;}
    else{std::cout << -1 << std::endl;}
}

int main(){
    int t; 
    std::cin >> t;
    while(t--){
        solve();
    }
}
