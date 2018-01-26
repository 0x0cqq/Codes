#include <cstdio> 
#include <algorithm>
#define INF 100000000
using namespace std;

int big[500][500],num[500][500],m,n;

int dp(int x,int y){
    if(x==0)
        return num[x][y];
    if(big[x][y]!=INF)
        return big[x][y];
    else{
        int res = dp(x-1,y);
        if(y!=0){
            res = max(res,dp(x-1,y-1));
        }
        if(y!=n-1){
            res = max(res,dp(x-1,y+1));
        }
        res += num[x][y];
        return big[x][y] = res;
    }
}

int main(){
    scanf("%d %d",&m,&n);
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&(num[i][j]));
            big[i][j] = INF;
        }
    }
    big[m][n/2] = INF;
    //printf("%d\n",num[m-1][n/2]);
    printf("%d\n",dp(m,n/2));
    return 0;
}