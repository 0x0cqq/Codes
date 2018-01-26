#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n,m,b,cost[10100],dis[10100],v[10100];

vector<pair<int,int> > r[10100];

int spfa(int maxn){
    queue<int> s;
    memset(dis,0x3f,sizeof(dis));
    memset(v,0,sizeof(v));
    if(cost[1]>maxn||cost[n]>maxn)
        return 0x3f3f3f3f;
    dis[1] = 0;
    v[1] = 1;
    s.push(1);
    while(!s.empty()){
        int nown = s.front();
        v[nown] = 0;
        s.pop();
        for(auto i:r[nown]){
            if(cost[i.first]>maxn)
                continue;
            if(dis[nown]+i.second<dis[i.first]){
                dis[i.first] = dis[nown]+i.second;
                if(v[i.first] == 0){
                    s.push(i.first);
                    v[i.first] = 0;
                }
            }
        }
    }
    return dis[n];
}

int main(){
    //freopen("1.in","r",stdin);
    scanf("%d %d %d",&n,&m,&b);
    for(int i = 1;i<=n;i++){
        scanf("%d",&cost[i]);
    }
    for(int i = 1;i<=m;i++){
        int a,b,l;
        scanf("%d %d %d",&a,&b,&l);
        r[a].push_back(make_pair(b,l));
        r[b].push_back(make_pair(a,l));
    }
    int l = 1,r = 0x3f3f3f3f;//闭区间
    while(l!=r){
        int mid = (l+r)/2;
        int t = spfa(mid);
        //printf("%d:%d\n",mid,t);
        if(t<b)
            r = mid;
        else
            l = mid+1;
    }
    if(l>1000000000)
        printf("AFK\n");
    else
        printf("%d\n",l);
    return 0;
}
