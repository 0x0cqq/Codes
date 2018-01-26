#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int n;
double minn = 1000000000;
double di[100][100];
bool vis[20];
struct p{
    double x,y;
}c[100];

inline double dis(int a,int b){
    if(di[a][b])
        return di[a][b];
    double ans = sqrt((c[a].x-c[b].x)*(c[a].x-c[b].x)+(c[a].y-c[b].y)*(c[a].y-c[b].y));
    return di[a][b] = ans;
}

void dfs(int now,int v,double di){
    if(di > minn)
        return;
    if(v == n){
        if(minn>di)
            minn = di;
        return;
    }
    for(int i = 1;i<=n;i++)
        if(vis[i]==0){
            vis[i] = 1;
            dfs(i,v+1,di+dis(now,i));
            vis[i] = 0;
        }
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        scanf("%lf %lf",&(c[i].x),&(c[i].y));
    dfs(0,0,0);
    printf("%.2lf\n",minn);
    return 0;
}