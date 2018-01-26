#include <cstdio>
#include <cmath>
#define m(x) ((x%w+w)%w) 
using namespace std;


int dd[805][805][32][2],num[900][900];
int n,m,w;
long long ans = 0;

int main(){
    scanf("%d %d %d",&n,&m,&w);
    w++;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            scanf("%d",&num[i][j]);
            num[i][j] = m(num[i][j]);
            dd[i][j][num[i][j]][0]=1;
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            for(int s = 0;s<=w;s++){
                dd[i][j][s][0]+=dd[i-1][j][m(s-num[i][j])][1]+dd[i][j-1][m(s-num[i][j])][1];
                dd[i][j][s][1]+=dd[i-1][j][m(s+num[i][j])][0]+dd[i][j-1][m(s+num[i][j])][0];
            }
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            ans+=dd[i][j][0][1];
        ans%=1000000007;
    }
    printf("%lld\n",ans);
    return 0;
}