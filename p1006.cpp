#include <cstdio>
#include <algorithm>
#define INF 1000000000
using namespace std;

int a[100][100],n,m,dd[100][100][150];

int dp(int x1,int x2,int he){
    //printf("!%d %d %d\n",x1,x2,he);
    int y1 = he - x1,y2 = he - x2;
    if((x1==x2&&(he!=0&&he!=m+n-2))||x1>=m||x2>=m||y1>=n||y2>=n)
        return -INF;
    if(x1 == m-1&&x2 == m-1 &&he==m+n-2)
        return 0;
    if(dd[x1][x2][he])
        return dd[x1][x2][he];
    int res,res_1,res_2;
    res_1 = max(dp(x1,x2+1,he+1),dp(x1+1,x2,he+1));
    res_2 = max(dp(x1,x2,he+1),dp(x1+1,x2+1,he+1));
    res = max(res_1,res_2);
    res += (a[x1][y1]+a[x2][y2]);
    //printf("::%d\n",res);
    return dd[x1][x2][he] = res;
}


int main(){
    scanf("%d %d",&m,&n);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&(a[i][j]));
        }
    }
    printf("%d\n",dp(0,0,0));
    return 0;
}