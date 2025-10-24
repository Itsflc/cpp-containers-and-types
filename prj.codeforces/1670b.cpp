#include<iostream>
#include<string>
#include<vector>

void solve(){
    int n;
    std::cin >> n;
    
    std::string pass;
    pass.resize(n);
    std::cin >> pass;
    
    int m;
    std::cin >> m;

    std::vector<char>spec(m);
    std::vector<bool>is_special(26, false);

    for(int i = 0; i < m; i++){
        char temp;
        std::cin >> temp;
        spec[i] = temp;
        is_special[temp - 'a'] = true;
    }
    int last_pos = 0;
    int max_dist = 0;
    for (int j = 0; j < n; j++){
        char cur = pass[j];
        if (is_special[cur - 'a']){
            int dist = j - last_pos;
            last_pos = j;
            if(dist>max_dist){max_dist=dist;}
        }
    }
    std::cout << max_dist << std::endl;
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
