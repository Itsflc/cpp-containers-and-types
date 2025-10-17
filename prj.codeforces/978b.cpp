#include<iostream>
 
int main(){
    int cnt = 0;
    int len;
    std::cin >> len;
    char line[len];
    for (int i = 0; i < len; i++){
        char current;
        std::cin >> current;
        line[i] = current;
    }
    for (int j = 2; j < len; j++){
        if (line[j-2] == 'x'  && line[j-1] == 'x' && line[j] == 'x'){cnt++;}}
        
    std::cout << cnt;
}
