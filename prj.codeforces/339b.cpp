#include<iostream>
#include<vector>
 
int main(){
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    long long n, m;
    std::cin >> n >> m;
    std::vector<int>dela(m + 1);
    dela[0] = 1;
    long long timer = 0;
    
    for (long long i = 1; i <= m; i++){
        std::cin >> dela[i];
    }
    for (long long j = 0; j < m; j++){
        if (dela[j + 1] >= dela[j]){
            timer += dela[j + 1] - dela[j];
        } else {timer += n - dela[j] + dela[j + 1];}
    }
    std::cout << timer;
}
