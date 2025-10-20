#include<iostream>

void solve(){
    int n, k, r, c;
    std::cin >> n >> k >> r >> c;
    char setka[3*n][3*n];
    r--;
    c--;
    while(r >= 0){r -= k;}
    r += k;
    while(c >= 0){c -= k;}
    c += k;
    
    for (int i = 0; i < 3*n; i++){
        for (int j = 0; j < 3*n; j++){
            
            if (j % k == c && i % k == r){
                setka[i][j] = 'X';
                for (int v = 0; v < 3 * n; v++){
                    if (i - v >= 0 && j + v < 3 * n){setka[i - v][j + v] = 'X';}}
                for (int vi = 0; vi < 3 * n; vi++){
                    if (i + vi < 3 * n && j - vi >= 0){setka[i + vi][j - vi] = 'X';}}}
            else {setka[i][j] = '.';}
        }
    }
    
    for (int l = n; l < 2 * n; l++){
        for (int p = n; p < 2 * n; p++){
            std::cout << setka[l][p];}
            
        std::cout << std::endl;
    }
}

int main(){
    int tem;
    std::cin >> tem;
    while(tem--){
        solve();
    }
}
