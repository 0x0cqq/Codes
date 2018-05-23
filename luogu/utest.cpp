#include <cstdio>
using namespace std;


int main(){
    int n = 100000;
    int ans = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            ans++;
        }
    }
    return 0;
}