#include <cstdio>
#include <vector>
#include <cstring> 
using namespace std;

const int MAXN = 500;

int n,color[MAXN],cnum = 1,cnt = 1,dfn[MAXN],low[MAXN],in[MAXN],out[MAXN];
bool instack[MAXN];

struct stack{
    int s[MAXN],tt = 0;
    void push(int x){
        s[tt++] = x;
    }
    void pop(){
        --tt;
    }
    int top(){
        return s[tt-1];
    }
}a;

vector<int> edge1[MAXN],edge2[MAXN];

void init(){
    scanf("%d",&n);
    int t;
    for(int i = 1;i<=n;i++){
        scanf("%d",&t);
        while(t){
            edge1[i].push_back(t);
            scanf("%d",&t);
        }
    }
}

void dfs(int nown){
    dfn[nown] = low[nown] = ++cnt;
    a.push(nown),instack[nown] = true;
    for(int to:edge1[nown]){
        if(dfn[to] == 0)
            dfs(to),low[nown] = min(low[nown],low[to]);
        if(instack[to])
            low[nown] = min(low[nown],dfn[to]);
    }
    if(dfn[nown] == low[nown]){
        int j = -1;
        do{
            j = a.top();a.pop();
            instack[j] = 0;
            color[j] = cnum;
        }while(j!=nown);
        cnum++;
    }
}

void tarjan(){
    for(int i = 1;i<=n;i++){
        if(dfn[i] == 0)
            dfs(i);
    }
}

void solve(){
    for(int i = 1;i<=n;i++){
        for(int to:edge1[i]){
            if(color[i]!=color[to]){
                edge2[color[i]].push_back(color[to]);
                out[color[i]]++;
                in[color[to]]++;
            }
        }
    }
    int ans1 = 0,ans2 = 0;
    for(int i = 1;i<cnum;i++){
        if(in[i] == 0)
            ans1++;
        if(out[i] == 0)
            ans2++;
    }
    printf("%d\n%d\n",ans1,max(cnum == 2?0:ans1,cnum == 2?0:ans2));
}


int main(){
    init();
    tarjan();
    solve();
    return 0;
}