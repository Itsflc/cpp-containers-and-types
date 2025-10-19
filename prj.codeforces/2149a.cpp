#include<iostream>

void solve(){
    int zero = 0, neg = 0;
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        if (temp == 0){zero++;}
        else if (temp == -1){neg++;}}
    std::cout << zero + 2 * (neg % 2) << std::endl;
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
