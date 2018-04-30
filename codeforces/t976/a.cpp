#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 10000;

int n,m,s,p,t,k,w,num[MAXN];

char www[MAXN];

int main(){
    scanf("%d",&n);
    scanf("%s",www);
    if(n == 1){
        printf("%s",www);
    }
    else{
        putchar('1');
        for(int i = 1;i<n;i++){
            if(www[i] == '0'){
                putchar('0');
            }
        }
        putchar('\n');
    }
    return 0;
}