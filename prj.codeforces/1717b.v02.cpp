#include<iostream>

void solve(){
    int n, k, r, c;
    std::cin >> n >> k >> r >> c;
    r--;
    c--;
    int important_thing = (r + c) % k;
    char setka[n][n];
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((i + j) % k  == important_thing){
                std::cout << 'X';
            } else {std::cout << '.';}
        }
        std::cout << std::endl;
    }
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
