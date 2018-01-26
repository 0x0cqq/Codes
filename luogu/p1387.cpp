#include <cstdio>
#include <cmath>
using namespace std;

int b[300][300],n,m;

int cal(int x,int y,int l){
    int ans;
    ans = b[x][y]-b[x-l][y]-b[x][y-l]+b[x-l][y-l];
    return ans;
}

void print(){
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            scanf("%d",&(b[i][j]));
            b[i][j] += b[i-1][j]+b[i][j-1]-b[i-1][j-1];
        }
    }
    for(int l = int(sqrt(b[n][m]));l>=0;l--){
        for(int i = n;i>=l;i--){
            for(int j = m;j>=l;j--){
                if(cal(i,j,l)==l*l){
                    printf("%d\n",l);
                    return 0;
                }
            }
        }
    }
    return 0;
}