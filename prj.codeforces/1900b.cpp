#include<iostream>

void solve(){
    int a, b, c;
    std::cin >> a >> b >> c;
    
    int res[3]{};
    
    if ((b + c) % 2 == 0){
        res[0] = 1;
    }
    if ((a + c) % 2 == 0){
        res[1] = 1;
    }
    if ((a + b) % 2 == 0){
        res[2] = 1;
    }
    std::cout << res[0] << ' ' << res[1] << ' ' << res[2] << std::endl;
}


int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
