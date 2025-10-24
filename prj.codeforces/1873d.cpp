#include<iostream>
#include<vector>

void solve(){
    int n, k;
    std::cin >> n >> k;
    
    int cnt = 0;
    std::vector<char>list(n);
    for (int i = 0; i < n; i++){
        std::cin >> list[i];
    }
    for (int j = 0; j < n; j++){
        if (list[j] == 'B'){
            cnt++;
            j = j + k - 1;
        }
    }
    std::cout << cnt << std::endl;
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
