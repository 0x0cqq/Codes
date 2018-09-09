#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#define ll long long
using namespace std;


int main(){
    srand(time(NULL));
    int T = 5;
    int n = 20,m = 20,L = 0?100:101,MAXN = 5;
    printf("%d %d %d\n",n,m,L);
    for(int i = 1;i<=n;i++){
        int len = L<=100?rand()%4+2:rand()%2+1;
        for(int i = 0;i<len;i++){
            putchar(rand()%MAXN+'a');
        }
        putchar('\n');        
    }
    for(int i = 1;i<=m;i++){
        int len = rand()%3+3;
        for(int i = 0;i<len;i++){
            putchar(rand()%MAXN+'a');
        }
        putchar('\n');
    }
    return 0;
}