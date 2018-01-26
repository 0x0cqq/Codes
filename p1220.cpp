#include <cstdio>
#include <algorithm>
using namespace std;

int n,c,dd[100][100][2];
int dis[100],w[100];

int dp(int i,int j,int side){//0left,1right
    if(dd[i][j][side])
        return dd[i][j][side];
    if(i == 0&&j == n+1)
        return 0;
    int sum = w[i]-w[0]+w[n+1]-w[j-1],res = 0x3f3f3f3f;
    if(i>=1){
        if(side == 0){
            res = min(res,dp(i-1,j,0)+(dis[i+1]-dis[i])*sum);
        }
        else{
            res = min(res,dp(i-1,j,0)+(dis[j-1]-dis[i])*sum);
        }
    }
    if(j<=n){
        if(side == 0){
            res = min(res,dp(i,j+1,1)+(dis[j]-dis[i+1])*sum);
        }
        else{
            res = min(res,dp(i,j+1,1)+(dis[j]-dis[j-1])*sum);
        }
    }
    return dd[i][j][side] = res;
}


int main(){
    scanf("%d %d",&n,&c);
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&(dis[i]),&(w[i]));
        w[i] += w[i-1];
    }
    w[0] = 0;w[n+1] = w[n];
    /*for(int i = 0;i<=n+1;i++){
        printf("%d ",w[i]);
    }
    putchar('\n');*/
    printf("%d\n",dp(c-1,c+1,0));
    return 0;
}