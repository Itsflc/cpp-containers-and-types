#include<iostream>
#include<cmath>
 
void solve(){
    int a, b, c;
    std::cin >> a >> b >> c;
    int raz = std::abs(a - b);
    int cnt = 0;
    while (raz > 0){
        raz -= c * 2;
        cnt++;
        }
    std::cout << cnt << std::endl;}
    
int main(){
    int n;
    std::cin >> n;
    while (n--){
        solve();}
}
