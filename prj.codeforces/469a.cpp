#include<iostream>
#include<vector>

int main(){
    int levels;
    int fir;
    std::cin >> levels >> fir;

    std::vector<int>first(fir);

    for (int i = 0; i < fir; i++){
        std::cin >> first[i];
    }
    int sec;
    std::cin >> sec;
    std::vector<int>second(sec);

    for (int j = 0; j < sec; j++){
        std::cin >> second[j];
    }
    
    bool success = true;
    
    for (int k = 1; k < levels + 1; k++){
        
        bool cancomplete = false;
        
        for (int p = 0; p < fir; p++){
            if (first[p] == k){cancomplete = true;}
        }
        
        for (int l = 0; l<sec; l++){
            if (second[l] == k){cancomplete = true;}
            
        }
        if (!cancomplete){success = false; break;}
    }
        
    if (success){std::cout << "I become the guy.";} else{
        std::cout << "Oh, my keyboard!";}
