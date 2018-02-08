有些同学回家了，而有些同学则有以前的好朋友来探访，那么住宿就是一个问题。我们假设每个人只能睡和自己直接认识的人的床。我们已知一共有$n$个人，并且知道其中每个人是不是本校学生，也知道每个本校学生是否回家。问是否存在一个方案使得所有不回家的本校学生和来看他们的其他人都有地方住。

<!-- more -->

## 链接

[Luogu P2055 [ZJOI2009]假期的宿舍](https://www.luogu.org/problemnew/show/P2055)

## 题解

这道题其实可以转化成二分图匹配的问题。如果把所有不回家的在校生和前来探访的朋友放在二分图一侧，所有本校学生床放在二分图另一侧，再将认识的人&床连边（包括自己和自己的床），注意上面的人不包括回家的人。

然后就是一个模版的二分图匹配了。然而我只会写网络流，所以写了一个$Dinic$上去，使用了单路增广&当前弧优化。

然而开始调了一个下午也没调对。然而回家调了一个晚上也没调对。最后还算是调对了。奇怪的是我今天又敲了另一个$Dinic$，然后竟然1次AC了。缘妙不可言啊。

## 代码

{% fold %}

```cpp
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge{
    int from,to,flow,cap;
    int next;
}edge[20000];

int fir[300],dis[300],cur[300];
int n,T,home[300],local[300],s,t,tot;

bool bfs(){
    queue<int> q;
    memset(dis,0,sizeof(dis));
    memcpy(cur,fir,sizeof(fir));
    q.push(s);dis[s] = 1;
    while(!q.empty()){
        int nown = q.front();q.pop();
        for(int e = fir[nown];e!=0;e = edge[e].next){
            int v = edge[e].to;
            if(dis[v] == 0 && edge[e].cap > edge[e].flow){
                dis[v] = dis[nown]+1;
                q.push(v);
            }
        }
    }
    return dis[t];
}

int dfs(int nown,int limit = 0x3f3f3f3f){
    if(nown == t || limit == 0) return limit;
    for(int &e = cur[nown];e!=0;e = edge[e].next){
        int f,v = edge[e].to;
        if(dis[v] == dis[nown]+1&&edge[e].flow <edge[e].cap){
            int f = dfs(v,min(edge[e].cap-edge[e].flow,limit));
            if(f>0){
                edge[e].flow+=f;
                edge[e^1].flow-=f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,f;
    while(bfs()){
        while((f = dfs(s)>0))
            ans+=f;
    }
    return ans;
}

void addedge(int from,int to,int c){
    edge[tot].from = from;edge[tot].to = to;
    edge[tot].cap = c;edge[tot].flow = 0;
    edge[tot].next = fir[from];fir[from] = tot;
    tot++;
}

int main(){
    scanf("%d",&T);
    for(int i = 1;i<=T;i++){
        scanf("%d",&n);
        //清零
        memset(edge,0,sizeof(edge));
        memset(home,0,sizeof(home));
        memset(local,0,sizeof(local));
        memset(fir,0,sizeof(fir));
        tot = 2;int cnt = 0;
        s = 2*n+1,t = 2*n+2;
        //是否本校
        for(int i = 1;i<=n;i++){
            scanf("%d",&local[i]);
        }
        //是否回家
        for(int i = 1;i<=n;i++){
            scanf("%d",&home[i]);
            if(local[i] == 0) home[i] = 0;
        }
        //是否认识且符合条件
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                int tmp;scanf("%d",&tmp);
                if(i == j) tmp = 1;
                if(home[i] == 1||local[j] == 0||tmp == 0)
                    continue;
                else addedge(i,j+n,1),addedge(j+n,i,0);
            }
        }
        //超级源点&&汇点
        for(int i = 1;i<=n;i++){
            if(home[i] == 0)
                addedge(s,i,1),addedge(i,s,0),cnt++;
            if(local[i] == 1)
                addedge(i+n,t,1),addedge(t,i+n,0);
        }
        if(dinic()==cnt) printf("^_^\n");
        else printf("T_T\n");
    }
    return 0;
}
```

{% endfold %}