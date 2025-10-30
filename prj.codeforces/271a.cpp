#include<iostream>
int main(){
    int year = 0;
    std::cin>>year;
    bool flag = false;
    while(flag == false){
        year+=1;
        int d = year%10;
        int c = (year/10)%10;
        int b = (year/100)%10;
        int a = year/1000;
        if (a!=b && a!=c && a!=d && b!=c && b!=d && c!=d){flag = true;}
    }
    std::cout<<year;}
