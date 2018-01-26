#include <cstdio>
#include <algorithm>
#define INF 1000000000
using namespace std;

int a[100][100],n,dd[100][100][150];

int dp(int x1,int x2,int he){
    //printf("!%d %d %d\n",x1,x2,he);
    int y1 = he - x1,y2 = he - x2;
    if(x1>=n||x2>=n||y1>=n||y2>=n)
        return -INF;
    if(x1 == n-1&&x2 == n-1&&he==2*n-2)
        return a[n-1][n-1];
    if(dd[x1][x2][he])
        return dd[x1][x2][he];
    int res,res_1,res_2;
    res_1 = max(dp(x1,x2+1,he+1),dp(x1+1,x2,he+1));
    res_2 = max(dp(x1,x2,he+1),dp(x1+1,x2+1,he+1));
    res = max(res_1,res_2);
    res += (a[x1][y1]+a[x2][y2]);
    if(x1 == x2)
        res -= a[x1][y1];
    //printf("::%d\n",res);
    return dd[x1][x2][he] = res;
}


int main(){
    scanf("%d",&n);
    while(true){
        int x,y,w;
        scanf("%d %d %d",&x,&y,&w);
        if(x == 0&&y == 0&& w == 0)
            break;
        a[x-1][y-1] = w;
    }
    printf("%d\n",dp(0,0,0));
    return 0;
}