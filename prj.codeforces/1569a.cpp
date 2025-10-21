#include<iostream>
#include<string>

void solve(){
    int n;
    std::cin >> n;
    
    std::string s;
    s.resize(n);
    std::cin >> s;
    
    int l = -1, r = -1;
    for(int i = 0; i < n - 1; i++){
        if(s[i] == 'a' && s[i + 1] == 'b' || s[i] == 'b' && s[i + 1] == 'a'){
            l = i + 1; r = i + 2; break;
        }
    }
    std::cout << l << ' ' << r << std::endl;
}

int main(){
    int t;
    std::cin >> t;
    
    while(t--){
        solve();
    }
}
