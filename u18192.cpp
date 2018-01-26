#include <cstdio>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

ll s,p,dis[2100][2100],point[2100][3],color[2100];
ll maxn = -1;

inline ll dd(int i,int j){
    ll res = 0;
    res += (point[i][0]-point[j][0])*(point[i][0]-point[j][0]);
    res += (point[i][1]-point[j][1])*(point[i][1]-point[j][1]);
    res += (point[i][2]-point[j][2])*(point[i][2]-point[j][2]);
    return res;
}

void dfs(int nown,int c,int nowd){
    color[nown] = c;
    for(int i = 0;i<s;i++)
        if(color[i]==0 && dis[nown][i]<=nowd)
            dfs(i,c,nowd);
}

int colored(int nowd){
    memset(color,0,sizeof(color));
    int nowc = 0;
    for(int i = 0;i<s;i++){
        if(color[i]!=0)
            continue;
        else
            dfs(i,++nowc,nowd);
    }
    return nowc;
}

int main(){
    scanf("%lld %lld",&s,&p);
    if(p == 0) p = 1;//特判,防止二分出错
    for(int i = 0;i<s;i++){
        scanf("%lld %lld %lld",&point[i][0],&point[i][1],&point[i][2]);
        for(int j = 0;j<i;j++)
            if((dis[i][j] = dis[j][i] = dd(i,j))>=maxn) 
                maxn = dis[i][j];//检测最大值
    }
    double b = 0,e = maxn;
    while(e-b>=1e-2){//二分查找
        double mid = (b+e)/2;
        if(colored(mid)>p) b = mid;
        else e = mid;
    }
    printf("%.2lf\n",sqrt(b));
    return 0;
}