#include<iostream>
int main(){
    int coord = 0;
    int cnt = 0;
    std::cin>>coord;
    cnt = coord/5;
    if (coord%5 != 0){
        cnt = cnt + 1;
     }
   std::cout<<cnt;
}
