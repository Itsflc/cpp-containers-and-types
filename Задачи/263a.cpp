#include <iostream>
 
int main() {
    char ch;
    int w = 1;
    while (std::cin.get(ch)) {
        if (ch == '1') break;
        if (ch == '0') w++;
    }
    if (w == 13){std::cout << 0;}
    else if (w==1 || w==5 || w==21 || w==25){std::cout << 4;}
    else if (w==8 || w==12 || w==14 || w==18){std::cout << 1;}
    else if (w==3 || w==7 || w==9 || w==11 || w==15 || w==17 || w==19 || w==23){
        std::cout << 2;} else{std::cout << 3;}
}
