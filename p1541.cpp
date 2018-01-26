#include <cstdio>
#include <algorithm>
using namespace std;

inline int cal(int a,int b,int c,int d){
    return a+2*b+3*c+4*d+1;
}

int w[40][40][40][40],n,p,num[5],board[1000];

int dfs(int a,int b,int c,int d){
    if(w[a][b][c][d])
        return w[a][b][c][d];
    if(a > num[1]||b > num[2]||c> num[3]||d>num[4])
        return 0;
    if(a == num[1]&&b == num[2]&&c== num[3]&&d==num[4]){
        return board[cal(a,b,c,d)];
    }
    int res = -1;
    res = max(dfs(a+1,b,c,d),dfs(a,b+1,c,d));
    res = max(res,dfs(a,b,c+1,d));
    res = max(res,dfs(a,b,c,d+1));
    return w[a][b][c][d] = res+board[cal(a,b,c,d)];
}

int main(){
    scanf("%d %d",&n,&p);
    for(int i = 1;i<=n;i++){
        scanf("%d",&board[i]);
    }
    for(int i = 1;i<=p;i++){
        int t;
        scanf("%d",&t);
        num[t]++;
    }
    printf("%d\n",dfs(0,0,0,0));

    return 0;
}