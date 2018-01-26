#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

struct point{
    int p,l;
    bool operator<(const point a)const{
        return l>a.l;
    }
};

int n;
int d[300][300];
int dis[300];
bool vis[300];


void djs(){
    memset(dis,0x3f,sizeof(dis));
    priority_queue<point> a;
    point start;
    start.l = 0;start.p = 1;
    a.push(start);
    while(!a.empty()){
        point nown = a.top();
        a.pop();
        if(vis[nown.p])
            continue;
        vis[nown.p] = 1;
        dis[nown.p] = nown.l;
        for(int i = nown.p+1;i<=n;i++){
            point newn;
            newn.p = i;
            newn.l = nown.l+d[nown.p][i];
            a.push(newn);
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<n;i++){
        for(int j = i+1;j<=n;j++){
            scanf("%d",&d[i][j]);
        }
    }
    djs();
    printf("%d\n",dis[n]);
    return 0;
}