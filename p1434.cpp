#include <cstdio>
#include <algorithm>
using namespace std;

int r,c,m[110][110],b[110][110],res = 0;

int dfs(int x,int y){
    int ans = 0;
    if(x==0||y==0||x>r||y>c)
        return 0;
    if(b[x][y]!=0)
        return b[x][y];
    if(m[x-1][y]<m[x][y])
        ans = max(ans,dfs(x-1,y));
    if(m[x+1][y]<m[x][y])
        ans = max(ans,dfs(x+1,y));
    if(m[x][y+1]<m[x][y])
        ans = max(ans,dfs(x,y+1));
    if(m[x][y-1]<m[x][y])
        ans = max(ans,dfs(x,y-1));
    ans++;
    return b[x][y] = ans;
}

int main(){
    scanf("%d %d",&r,&c);
    for(int i = 1;i<=r;i++){
        for(int j = 1;j<=c;j++){
            scanf("%d",&(m[i][j]));
        }
    }
    for(int i = 1;i<=r;i++){
        for(int j = 1;j<=c;j++){
            res = max(res,dfs(i,j));
        }
    }
    printf("%d\n",res);
    return 0;
}