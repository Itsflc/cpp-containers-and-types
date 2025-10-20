#include<iostream>
#include<string>

void solve(){
    int a, b;
    std::cin >> a >> b;
    std::string s;
    s.resize(a + b);
    std::cin >> s;
    int size = s.size();
    bool is_palindrome = true;
    
    for (int i = 0; i < (size + 1) / 2; i++){
        if (s[i] == s[size - 1 - i]){continue;}
        else if (s[i]=='?' && s[size - 1 - i]=='0'){s[i] = '0';}
        else if (s[i]=='0' && s[size - 1 - i]=='?'){s[size - 1 - i] = '0';}
        else if (s[i]=='?' && s[size - 1 - i]=='1'){s[i] = '1';}
        else if (s[i]=='1' && s[size - 1 - i]=='?'){s[size - 1 - i] = '1';}
        else {is_palindrome = false;}
    }
    int ones = 0, zero = 0, quest = 0;
    for (int j = 0; j < size; j++){
        if (s[j] == '1'){ones++;}
        else if (s[j] == '0'){zero++;}
        else {quest++;}
    }
    if (zero > a || ones > b){is_palindrome = false;}
    a -= zero;
    b -= ones;
    if(is_palindrome){
        for(int k = 0; k < size / 2; k++){
            if (s[k] == '?'){
                if (a >= 2){
                    s[k] = '0';
                    s[size - 1 - k] = '0';
                    a -= 2;}
                else if (b >= 2){
                    s[k] = '1';
                    s[size - 1 - k] = '1';
                    b -= 2;}
            }
        }
        if (size % 2 == 1 && s[size / 2] == '?'){
            if (a == 1){s[size / 2] = '0'; a--;}
            else if (b == 1){s[size / 2] = '1'; b--;}
        }
    }
    if (is_palindrome && a == 0 && b == 0){
        std::cout << s << std::endl;
    } else {std::cout << -1 << std::endl;}
    
}

int main(){
    int t;
    std::cin >> t;
    while(t--){
        solve();
    }
}
