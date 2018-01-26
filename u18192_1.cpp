#include<cstdio>
#include<algorithm>
#include<cmath>
#define ll long long 
using namespace std;

ll point[2010][3], dis[2010][2010],d[2010],res[2010];
int cnt = 0;
int p,n;
bool vis[2010];

inline ll dd(int i,int j){
    ll res = 0;
    res += (point[i][0]-point[j][0])*(point[i][0]-point[j][0]);
    res += (point[i][1]-point[j][1])*(point[i][1]-point[j][1]);
    res += (point[i][2]-point[j][2])*(point[i][2]-point[j][2]);
    return res;
}

bool cmp(ll a,ll b){
    return a>b;
}

int main(){
    freopen("rtfz10.in","r",stdin);
    scanf("%d %d",&n,&p);
    if(p == 0) p = 1;
    for(int i=1;i<=n;i++){
        d[i]=0x3f3f3f3f;
        scanf("%lld %lld %lld",&point[i][0],&point[i][1],&point[i][2]);
        for(int j = 0;j<i;j++)
            dis[i][j] = dis[j][i] = dd(i,j);
    }
    d[1]=0;
    for(int i=1;i<=n;i++){
        ll minval=0x3f3f3f3f3f3f;int nown;
        for(int j=1;j<=n;j++)
            if(minval>d[j]&&vis[j]==false)
                minval=d[nown=j];
        vis[nown]=true; res[++cnt]=minval;
        for(int j=1;j<=n;j++)
            if(vis[j]==false)
                d[j]=min(d[j],dis[nown][j]);
    }
    sort(res+1,res+n+1,cmp);
    printf("%.2lf\n",sqrt(res[p]));
    return 0;
}