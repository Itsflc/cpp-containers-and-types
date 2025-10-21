#include<iostream>
#include<string>

void solve(){
    bool is_possible = true;
    int n,k;
    std::cin >> n >> k;
    
    std::string s;
    s.resize(n);
    std::cin >> s;
    
    int size = s.size();
    
    for (int i = 0; i < k; i++){
        int cnt = size / k;
        if(i < size % k){cnt++;}
        
        bool was_one = false;
        bool was_zero = false;
        
        for (int j = 0; j < cnt; j++){
            if (s[i + k * j] == '0'){was_zero = true;}
            else if (s[i + k * j] == '1'){was_one = true;}
        }
        if (was_one && was_zero){is_possible = false;}
        else if (was_zero){
            for (int p = 0; p < cnt; p++){
            if (s[i + k * p] == '?'){
                s[i + k * p] = '0';}
            }
        }
        else if (was_one){
            for (int u = 0; u < cnt; u++){
            if (s[i + k * u] == '?'){
                s[i + k * u] = '1';}
            }
        }
    }
    if (is_possible){
        int zeros = 0, ones = 0;
        for (int m = 0; m < k; m++){
            if (s[m] == '0')zeros++;
            else if (s[m] == '1')ones++;
        }
        if (zeros > k/2 || ones > k / 2){
            is_possible = false;
        }
    }
    if(is_possible){
        std::cout << "YES" << std::endl;
    } else {std::cout << "NO" << std::endl;}
}


int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
