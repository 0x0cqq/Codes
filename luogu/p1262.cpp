#include <cstdio>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 4000;

int n,p,m,dfn[MAXN],low[MAXN],instack[MAXN],cnt = 1;
int col[MAXN],siz[MAXN],vis[MAXN],colnum = 0;

int num1[MAXN],num2[MAXN];
int in[MAXN];
vector<int> edge1[MAXN],edge2[MAXN];
stack<int> s;

void addedge(int a,int b,int w){
    if(w == 1) edge1[a].push_back(b);
    if(w == 2) edge2[a].push_back(b);
}

void dfs(int nown){
    dfn[nown] = low[nown] = cnt++;
    instack[nown] = 1;s.push(nown);
    for(int i = 0;i<edge1[nown].size();i++){
        int to = edge1[nown][i];
        if(dfn[to] == 0)
            dfs(to),low[nown] = min(low[nown],low[to]);
        else if(instack[to])
            low[nown] = min(low[nown],dfn[to]);
    }
    if(dfn[nown] == low[nown]){
        int j = -1,minn = 0x3f3f3f3f3f,ss = 0;
        colnum++;
        //printf("%d:\n",colnum);
        do{
            j = s.top();s.pop();
            //printf("    %d\n",j);
            instack[j] = 0;
            ss++;
            col[j] = colnum;
            minn = min(minn,num1[j]);
        }while(j!=nown);
        num2[colnum] = minn;
        siz[colnum] = ss;
    }
}

void tarjan(){
    while(!s.empty()) s.pop();
    for(int i = 1;i<=n;i++){
        if(dfn[i] == 0)
            dfs(i);
    }

}

void rebuild(){
    /*
    for(int i = 1;i<=n;i++){
        printf("%d ",col[i]);
    }
    printf("\n");
    */
    for(int i = 1;i<=n;i++){
        for(int j = 0;j<edge1[i].size();j++){
            int to = edge1[i][j];
            //printf("%d %d %d %d\n",i,to,col[i],col[to]);
            if(col[i] == col[to]) continue;
            addedge(col[i],col[to],2);
            in[col[to]]++;
        }
    }
    /*
    for(int i = 1;i<=colnum;i++){
        printf("%d num:%d:\n",i,num2[i]);
        for(int j = 0;j<edge2[i].size();j++){
            printf("    %d\n",edge2[i][j]);
        }
    }
    */
}

void solve(){
    int tot = 0,ans = 0;
    while(!s.empty()) s.pop();
    for(int i = 1;i<=colnum;i++)
        if(in[i] == 0) s.push(i);
    while(!s.empty()){
        int nown = s.top();s.pop();
        if(vis[nown] || num2[nown] < 100000)
            tot+=siz[nown],ans += num2[nown] * (1-vis[nown]),vis[nown]=1;
        for(int i = 0;i<edge2[nown].size();i++){
            int to = edge2[nown][i];
            if(--in[to] == 0)
                s.push(to);
            vis[to] = vis[to] || vis[nown];
        }
    }
    if(tot == n){
        printf("YES\n%d\n",ans);
    }
    else{
        for(int i = 1;i<=n;i++){
            if(vis[col[i]] == 0){
                printf("NO\n%d\n",i);
                break;
            }
        }
    }
}

void init(){
    memset(num1,0x3f,sizeof(num1));
    scanf("%d %d",&n,&p);
    int a,b;
    for(int i = 1;i<=p;i++){
        scanf("%d %d",&a,&b);
        num1[a] = b;
    }
    scanf("%d",&m);
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&a,&b);
        addedge(a,b,1);
    }
}

int main(){
    init();
    tarjan();
    rebuild();
    solve();
    return 0;
}