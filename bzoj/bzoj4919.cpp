#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <cctype>
#define iter multiset<int>::iterator
using namespace std;

inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}

const int MAXN = 210000;

int n,w[MAXN],r;
vector<int> edge[MAXN];
multiset<int> S[MAXN];

void init(){
    read(n);
    int f;
    for(int i = 1;i<=n;i++){
        read(w[i]),read(f);
        if(f == 0) r = i;
        edge[f].push_back(i);
    }
}

void dfs(int x){
    for(int i = 0;i<edge[x].size();i++){
        int v = edge[x][i];
        dfs(v);
        if(S[v].size() > S[x].size()) swap(S[v],S[x]);
        for(iter it = S[v].begin();it != S[v].end();it++)
            S[x].insert(*it);
        //S[v].clear();
    }
    if(!S[x].empty() && S[x].lower_bound(w[x])!=S[x].end()) S[x].erase(S[x].lower_bound(w[x]));
    S[x].insert(w[x]);
}

void solve(){
    dfs(r);
    printf("%d\n",int(S[1].size()));
}

int main(){
    init();
    solve();
    return 0;
}