#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define pp pair<int,int>
using namespace std;

struct Edge{
    int b,e,len;
}edge[200000];

vector<Edge> r[10000];

vector<Edge> rr[10000];

int n,m,ans = 0;
bool v[10000];
int d[10000];

priority_queue<pp,vector<pp>,greater<pp> > p;

void dij(){
    memset(v,0,sizeof(v));
    memset(d,0x3f,sizeof(d));
    p.push(make_pair(0,1));
    d[1] = 0;
    while(!p.empty()){
        pp nown = p.top();
        p.pop();
        //printf("%d %d\n",nown.first,nown.second);
        if(v[nown.second]) continue;
        v[nown.second] = 1;
        for(Edge i:r[nown.second]){
            if(d[i.e]>nown.first+i.len){
                d[i.e] = nown.first+i.len;
                p.push(make_pair(d[i.e],i.e));
            }
        }
    }
    for(int i = 1;i<=n;i++)
        ans+=d[i];
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        scanf("%d %d %d",&edge[i].b,&edge[i].e,&edge[i].len);
        r[edge[i].b].push_back(edge[i]);
    }
    dij();
    for(int i = 1;i<=n;i++)
        r[i] = rr[i];
    for(int i = 0;i<m;i++){
        swap(edge[i].b,edge[i].e);
        r[edge[i].b].push_back(edge[i]);
    }  
    dij();
    printf("%d\n",ans);  
    return 0;
}