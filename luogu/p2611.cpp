#include <cstdio>
#include <algorithm>
#include <cctype>
#define ll long long
typedef int T;
using namespace std;
#define calc(x) (((ll)(x)*((x)+1))/2)

namespace fast_io{
    inline char read(){static const int SIZE=1024*1024;static char ibuf[SIZE],*_s,*_t;if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
}using namespace fast_io;

const int MAXN = 110000;

namespace Treap{
    //小根堆
    #define ls c[x][0]
    #define rs c[x][1]
    ll ans[MAXN],addn[MAXN];
    int ht[MAXN],siz[MAXN];
    int c[MAXN][2],cnt = 0;
    int root;
    void maintain(int x){//确保合法才能maintain
        siz[x] = siz[ls] + siz[rs] + 1;
        ans[x] = ans[ls] + ans[rs];
        ans[x] += (ll)(ht[ls] - ht[x])*calc(siz[ls]);
        ans[x] += (ll)(ht[rs] - ht[x])*calc(siz[rs]); 
    }
    int __build(int l,int r){
        if(l > r) return 0;
        int x = ++cnt,mid = (l+r)>>1;
        siz[x] = 1;
        ls = __build(l,mid-1),rs = __build(mid+1,r);
        maintain(x);
        return x;
    }
    void add(int x,int v){
        addn[x] += v,ht[x] += v;
    }
    void push_down(int x){
        if(addn[x]){
            add(ls,addn[x]),add(rs,addn[x]);
            addn[x] = 0;
        }
    }
    void rotate(int &x,int t){
        int y = c[x][t];
        c[x][t] = c[y][1-t];
        c[y][1-t] = x;
        maintain(x),maintain(y);
        x = y;        
    }
    void modify(int &x,int r){
        push_down(x);int t = siz[ls] + 1;
        if(r == t){
            ht[x] = 0;maintain(x);return;
        }
        else{
            if(r < t){
                modify(ls,r);
                if(ht[ls]<ht[x]) rotate(x,0);
                else             maintain(x);
            }
            else{
                modify(rs,r-t);
                if(ht[rs]<ht[x]) rotate(x,1);
                else             maintain(x);
            }
        }
    }
    void add(){add(root,1);}
    void modify(int r){modify(root,r);}
    ll query(){return ans[root];}
    int getheight(){return ht[root];}
    void build(int n){root = __build(1,n);}
}

int n,m,k;

struct Point{
    int x,y;
    bool operator < (const Point & _a)const{
        if(x != _a.x) return x < _a.x;  
        else return y < _a.y;
    }
}p[MAXN];

void init(){
    read(n),read(m),read(k);
    for(int i = 1;i<=k;i++){
        read(p[i].x),read(p[i].y);
    }
}

void build(){
    sort(p+1,p+k+1);
    Treap::build(m);
}

void solve(){
    static ll ans = calc(n)*calc(m);
    for(int i = 1,j = 1;i<=n;i++){
        Treap::add();
        //printf("%d %d\n",p[j].x,p[j].y);
        while(j <= k && p[j].x == i){
            Treap::modify(p[j].y);j++;
        }
        ans -= Treap::query() + calc(Treap::siz[Treap::root]) * Treap::getheight(); 
    }
    printf("%lld\n",ans);
}

int main(){
    init();
    build();
    solve();
    return 0;
}