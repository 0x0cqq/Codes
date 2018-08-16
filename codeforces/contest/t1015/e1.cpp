#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1100;

int n,m;
char s[MAXN][MAXN];
int maxn[MAXN][MAXN][4];
int minn[MAXN][MAXN];
int vis1[MAXN][MAXN];
int vis2[MAXN][MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%s",s[i]+1);
    }
    int now = 0;
    for(int i = 1;i<=n;i++){
        now = 0;
        for(int j = 1;j<=m;j++){
            if(s[i][j] == '*') now++;
            else now = 0;
            maxn[i][j][0] = now-1;
        }
        now = 0;
        for(int j = m;j>=1;j--){
            if(s[i][j] == '*') now++;
            else now = 0;
            maxn[i][j][1] = now-1;
        }
    }
    for(int j = 1;j<=m;j++){
        now = 0;
        for(int i = 1;i<=n;i++){
            if(s[i][j] == '*') now++;
            else now = 0;
            maxn[i][j][2] = now-1;
        }
        now = 0;
        for(int i = n;i>=1;i--){
            if(s[i][j] == '*') now++;
            else now = 0;
            maxn[i][j][3] = now-1;
        }
    }
    // for(int i = 1;i<=n;i++){
    //     for(int j = 1;j<=m;j++){
    //         printf("%d %d:%d %d %d %d\n",i,j,maxn[i][j][0],maxn[i][j][1],maxn[i][j][2],maxn[i][j][3]);
    //     }
    // }
    int cnt = 0;

    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            int t = min(min(maxn[i][j][0],maxn[i][j][1]),min(maxn[i][j][2],maxn[i][j][3]));
            minn[i][j] = t;
            if(t > 0)
                vis1[i][j-t]++,vis2[i-t][j]++,vis1[i][j+t+1]--,vis2[i+t+1][j]--;
            if(t > 0) cnt++;
        }
    }
    for(int i = 1;i<=n;i++){
        int nown = 0;
        for(int j = 1;j<=m;j++){
            nown += vis1[i][j];
            vis1[i][j] = nown;
        }
    }
    for(int j = 1;j<=m;j++){
        int nown = 0;
        for(int i = 1;i<=n;i++){
            nown += vis2[i][j];
            vis2[i][j] = nown;
        }
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(s[i][j] == '*' && (vis1[i][j] == 0 && vis2[i][j] == 0)){
                printf("%d\n",-1);
                return 0;
            }
        }
    }
    printf("%d\n",cnt);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(minn[i][j] > 0){
                printf("%d %d %d\n",i,j,minn[i][j]);
            }
        }
    }
    return 0;
}