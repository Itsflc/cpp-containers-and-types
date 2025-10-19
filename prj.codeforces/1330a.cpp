#include<iostream>

void solve(){
    int n, x;
    std::cin >> n >> x;
    int max = 0;
    int places[n];
    
    for (int i = 0; i < n; i++){
        int temp;
        std::cin >> temp;
        places[i] = temp;
        if (temp > max) max = temp;}
        
    bool was[max + 1]{};
    for (int j = 0; j < n; j++){
        was[places[j]] = true;}
        
    int howfar = 1;
    while (x > -1){
        if (howfar > max && x != 0){
            x--;  howfar++;}
        else if (howfar > max && x == 0){x--;}
        
        else if (was[howfar]){howfar++;}
        
        else if (x == 0 && !was[howfar]){x--;}
        else if (x != 0 && !was[howfar]){
            x--;  howfar++;}
        }
        std::cout << howfar - 1 << std::endl;
    }
    
int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
