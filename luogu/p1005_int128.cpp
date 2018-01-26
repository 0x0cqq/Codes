#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#define MAXN 100
#p
using namespace std;

int n,m,num[200][200];

__int128 n_2[1000][1000],dd[1000][1000];

inline __int128 n2(int t,int k){
    if(n_2[t][k]!=0)
        return n_2[t][k];
    else{
        return n_2[t][k] = n_2[t][1]*k;
    }
}

inline void print(__int128 k){
    if (k==0) return;
    if (k) print(k/10);
    putchar(k%10+'0');
}

__int128 dp(int row,int l,int r,int t){
    __int128 res = 0;
    memset(dd,0,sizeof(dd));
    if(l>r)
        return res;
    else if(l == r)
        res = n2(t,num[row][l]);
    else if(dd[l][r]!=0)
        res = dd[l][r];
    else{
        __int128 x,y;
        x = n2(t,num[row][l])+dp(row,l+1,r,t+1);
        y = n2(t,num[row][r])+dp(row,l,r-1,t+1);
        if(x>y)
            res = x;
        else
            res = y;
    }
    printf("t:%d l:%d r:%d res:",t,l,r);
    print(res); 
    return dd[l][r] = res;
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            int tmp;
            scanf("%d",&tmp);
            num[i][j] = tmp;
        }
    }
    /*for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            num[i][j].print(0);
            putchar(' ');
        }
        putchar('\n');
    }*/
    __int128 a;
    a = 1;
    for(int i = 1;i<=m;i++){
        a = a*2;
        n_2[i][1] = a;
    }
    __int128 ans;ans = 0;
    for(int i = 0;i<n;i++){
        printf("i:%d\n",i);
        ans = dp(i,0,m-1,1)+ans;
    }
    print(ans);
    return 0;
}