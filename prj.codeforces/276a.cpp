#include<iostream>

int main(){
    int choice = -10000000000000000;
    int numb = 0;
    int maxtime = 0;
    std::cin >> numb >> maxtime;
    while(numb--){
        int stars = 0;
        int enjoy = 0;
        int time = 0;
        std::cin >> enjoy >> time;
        if (time > maxtime){
            stars = enjoy - time + maxtime;
        } else {stars = enjoy;}
        if (stars > choice) choice = stars;
    }
    std::cout << choice;
}
