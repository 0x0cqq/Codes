#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 55;

int n,s1,s2;char edge[MAXN+10];
int dmin[MAXN][MAXN],dmax[MAXN][MAXN];
//最小值求最长路，最大值求最短路

void init(){
    scanf("%d %d %d",&n,&s1,&s2);
    for(int i = 1;i<=n;i++){
        scanf("%s",edge+1);
        for(int j = 1;j<=n;j++){
            if(i == j || edge[j] == '=')
                dmin[i][j] = 0,dmax[i][j] = 0;
            else if(edge[j] == '-')
                dmin[i][j] = -2,dmax[i][j] = -1;
            else if(edge[j] == '+')
                dmin[i][j] = 1,dmax[i][j] = 2;
            else
                dmin[i][j] = -2,dmax[i][j] = 2;
        }
    }
}

void floyd(){
    for(int k = 1;k<=n;k++){
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                dmin[i][j] = max(dmin[i][j],dmin[i][k]+dmin[k][j]);
                dmax[i][j] = min(dmax[i][j],dmax[i][k]+dmax[k][j]);
            }
        }
    }
}

void solve(){
    int c1 = 0,c2 = 0,c3 = 0;
    for(int i = 1;i<=n;i++){
        if(i == s1||i == s2) continue;
        for(int j = 1;j<=n;j++){
            if(j == s1||j == s2||i == j) continue;
            if(dmin[s1][i] > dmax[j][s2] || dmin[s1][j] > dmax[i][s2]){
                c1++;
            }
            else if(
            (dmin[s1][i]==dmax[s1][i]&&dmin[j][s2]==dmax[j][s2]&&dmin[s1][i]==dmin[j][s2]) ||
            (dmin[s1][j]==dmax[s1][j]&&dmin[i][s2]==dmax[i][s2]&&dmin[s1][j]==dmin[i][s2])){
                c2++;
            }
            else if(dmax[s1][i] < dmin[j][s2] || dmax[s1][j] < dmin[i][s2]){
                c3++;
            }
        }
    }
    printf("%d %d %d\n",c1/2,c2/2,c3/2);
}

int main(){
    init();
    floyd();
    solve();
    return 0;
}