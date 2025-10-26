#include<iostream>
#include<vector>
 
int main(){
    int cnt = 0;
    int len;
    std::cin >> len;
    std::vector<char>line(len);
    char line[len];
    for (int i = 0; i < len; i++){
        std::cin >> line[i];
    }
    for (int j = 2; j < len; j++){
        if (line[j-2] == 'x'  && line[j-1] == 'x' && line[j] == 'x'){cnt++;}}
        
    std::cout << cnt;
}
