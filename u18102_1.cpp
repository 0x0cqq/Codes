#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define cw cc[1].num,cc[2].num,cc[3].num,cc[4].num
using namespace std;

int n,m,k;
struct card{
    int num,ai,bi;
}cc[5];

inline int c1(int a,int b,int c,int d){
    return cc[1].ai*a+cc[2].ai*b+cc[3].ai*c+cc[4].ai*d+1;
}

inline int c2(int a,int b,int c,int d){
    return cc[1].bi*a+cc[2].bi*b+cc[3].bi*c+cc[4].bi*d+1;
}

double board[1600][1600];
double dd[200][200][200][200];

double dfs(int a,int b,int c,int d){
    if(a>cc[1].num||b>cc[2].num||c>cc[3].num||d>cc[4].num)
        return -20000000000;
    if(dd[a][b][c][d]!=0)
        return dd[a][b][c][d];
    if(a+b+c+d == k){
        return board[n][m];
    }
    double res = max(dfs(a,b,c+1,d),dfs(a,b,c,d+1));
    double t1 = max(dfs(a+1,b,c,d),dfs(a,b+1,c,d));
    return dd[a][b][c][d] = max(res,t1)+board[c1(a,b,c,d)][c2(a,b,c,d)];
}

int main(){
    freopen("1.txt","r",stdin);
    scanf("%d %d %d",&n,&m,&k);
    //printf(":%d %d %d\n",n,m,k);
    for(int i = 1;i<=4;i++)
        scanf("%d %d %d",&cc[i].ai,&cc[i].bi,&cc[i].num);
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=m;j++)
            scanf("%lf",&board[i][j]);
    double ans = dfs(0,0,0,0);
    printf("%.4lf\n",ans);
    return 0;
}