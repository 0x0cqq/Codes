#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;


namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void read(char *x){scanf("%s",x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}using namespace normal_io;

const int MAXN = 1100;

int n,m,k;
int cost[MAXN*MAXN];
int num[MAXN][MAXN];
int vis[MAXN*MAXN];
int x[MAXN],y[MAXN];

set<int> S;

int main(){
    read(n),read(m),read(k);
    for(int i = 1;i<=(n*m-1)/2;i++){
        read(cost[i]);
    }
    for(int i = 1;i<=k;i++)
        read(x[i]),read(y[i]);
    int xx,yy;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            read(num[i][j]);
            if(num[i][j] == 0)
                xx = i,yy = j;
        }
    }
    int sum = 0;
    for(int i = 1;i<=k;i++){
        if(((x[i] + y[i]) & 1) == 0)
            vis[num[x[i]][y[i]]] += 1,sum+=1;
    }
    long long ans = 0;
    if(vis[0] == 1){
        printf("GG\n");
        return 0;
    }
    else{
        if(vis[num[xx-1][yy]] + vis[num[xx+1][yy]] + vis[num[xx][yy-1]] + vis[num[xx][yy-1]] < sum)
            ans = 1ll * cost[num[xx-1][yy]] + cost[num[xx+1][yy]] + cost[num[xx][yy-1]] + cost[num[xx][yy+1]];
        else{
            if(vis[num[xx-1][yy]])
                ans += cost[num[xx-1][yy]];
            if(vis[num[xx+1][yy]])
                ans+= cost[num[xx+1][yy]];
            if(vis[num[xx][yy-1]])
                ans+= cost[num[xx][yy-1]];
            if(vis[num[xx][yy+1]])
                ans+= cost[num[xx][yy+1]];
        }
    }
    long long ans1 = 0;
    for(int i = 1;i<=k;i++){
        if(((x[i]+y[i])&1) == 0 && !S.count(num[x[i]][y[i]]))
            ans1 += cost[num[x[i]][y[i]]],S.insert(num[x[i]][y[i]]);
    }
    printf("%lld\n",min(ans,ans1));
    return 0;
}