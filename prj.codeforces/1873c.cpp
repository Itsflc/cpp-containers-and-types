#include<iostream>

int point(int i, int j){
    if (j == 0 || i == 0 || i == 9 || j == 9) return 1;
    else if (j == 1 || i == 1 || j == 8 || i == 8) return 2;
    else if (j == 2 || i == 2 || j == 7 || i == 7) return 3;
    else if (j == 3 || i == 3 || j == 6 || i == 6) return 4;
    else {return 5;}
}

void solve(){
    int cnt = 0;
    
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            char s;
            std::cin >> s;
            if (s == 'X'){
                cnt += point(i,j);
            }
        }
    }
    std::cout << cnt << std::endl;
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
