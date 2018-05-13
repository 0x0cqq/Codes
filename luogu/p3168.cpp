#include <cstdio>
#include <algorithm>
#include <map>
#include <cctype>
#include <vector>
#define ll long long
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
}using namespace fast_io;

const int MAXN = 200000;

map<int,int> S;int last[MAXN];

namespace prSegTree{
    int val[MAXN*50],ls[MAXN*50],rs[MAXN*50];
    ll sum[MAXN*50];int cnt = 0;
    #define mid ((l+r)>>1)
    void maintain(int nown,int l,int r){
        val[nown] = val[ls[nown]] + val[rs[nown]];
        sum[nown] = sum[ls[nown]] + sum[rs[nown]];
    }
    void insert(int &nown,int pre,int l,int r,int pos,int d){
        nown = ++cnt;ls[nown] = ls[pre],rs[nown] = rs[pre];
        val[nown]=val[pre]+d,sum[nown]=sum[pre]+1ll * d * last[pos];
        if(l == r) return;
        else{
            if(pos <= mid) insert(ls[nown],ls[pre],l,mid,pos,d);
            if(mid+1 <= pos) insert(rs[nown],rs[pre],mid+1,r,pos,d);
        }
    }
    ll query(int nown,int l,int r,int k){
        if(l == r){
            if(k>=val[nown]) return sum[nown];
            else return k * last[l];
        }
        else{
            int sumn = val[ls[nown]];
            if(k <= sumn)
                return query(ls[nown],l,mid,k);   
            else if(sumn + 1 <= k)
                return sum[ls[nown]] + query(rs[nown],mid+1,r,k-sumn);
        }
    }
}


int n,m,totn,maxt,rt[MAXN];
vector<int> qq[MAXN];

void init(){
    read(n),read(m);
    int a,b,c;
    maxt = n;
    for(int i = 1;i<=n;i++){
        read(a),read(b),read(c);
        qq[a].push_back(c);
        qq[b+1].push_back(-c);
        maxt = max(maxt,b+1);
        S[c] = 0;
    }
    for(auto it = S.begin();it!=S.end();it++){
        it->second = ++totn;
        last[totn] = it->first;
    }
    for(int i = 1;i<=maxt;i++){
        rt[i] = rt[i-1];
        for(int j = 0;j<qq[i].size();j++){
            prSegTree::insert(rt[i],rt[i],1,totn,(S[abs(qq[i][j])]),qq[i][j] > 0? 1 : -1);
        }
    }
}

void solve(){
    ll last = 1,ans;
    int x,k,a,b,c;
    for(int i = 1;i<=m;i++){
        read(x),read(a),read(b),read(c);
        k = 1+(a*last+b)%c;
        ans = prSegTree::query(rt[x],1,totn,k);
        printf("%lld\n",ans);
        last = ans;
    }
}

int main(){
    init();
    solve();
    return 0;
}