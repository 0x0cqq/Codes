#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

const int MAXN = 3100;
int M = 65536;

int minn[1000000];

void update(int x,int d){
    x+=M;
    minn[x] = min(minn[x],d);
    while(x>>=1)
        minn[x] = min(minn[x<<1],minn[(x<<1)|1]);
}

map<int,int> S;

int query(int l,int r){
    int ans = 0x3f3f3f3f;
    for(l = l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1){
        if(~l&1) ans = min(ans,minn[l^1]);
        if(r&1) ans = min(ans,minn[r^1]);
    }
    return ans;
}

int n,siz[MAXN],c[MAXN];

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&siz[i]);
        S[siz[i]] = 0;
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&c[i]);
    }
    int nowcnt = 0;
    memset(minn,0x3f,sizeof(minn));
    for(auto &i:S){
        i.second = ++nowcnt;
        //printf("%d %d\n",i.first,i.second);
    }
    int ans = 0x3f3f3f3f;
    for(int i = 1;i<=n;i++){
        if(i>1) update(S[siz[i-1]],c[i-1]);
        for(int j = i+1;j<=n;j++){
            if(siz[i] < siz[j])
                ans = min(c[i] + c[j] + query(1,S[siz[i]]-1),ans);
        }
    }
    if(ans >= 1000000000)
        printf("-1\n");
    else
        printf("%d\n",ans);
    return 0;
}