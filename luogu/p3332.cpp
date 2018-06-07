#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;
#define ll long long
#define mid ((l+r)>>1)
const int MAXN = 210000;

namespace fast_io{
    static const int SIZE=1024*1024;char obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){static char ibuf[SIZE],*s,*t;if(s==t)t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);return s==t?-1:*s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

struct ZKW{
    ll sumn[MAXN<<2],addn[MAXN<<2];
    int M;
    void init(int n){
        for(M = 1;M<=n+2;M<<=1);
    }
    void update(int l,int r,ll d){
        int i=1,L=0,R=0;
        for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            sumn[l]+=L*d,sumn[r]+=R*d;
            if(~l&1) addn[l^1]+=d,sumn[l^1]+=d*i,L+=i;
            if(r&1) addn[r^1]+=d,sumn[r^1]+=d*i,R+=i;
        }
        sumn[l]+=L*d,sumn[r]+=R*d;
        while(l>>=1) sumn[l]+=(L+R)*d;
    }
    ll query(int l,int r){
        ll ans = 0;int i=1,L=0,R=0;
        for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,i<<=1){
            ans+=addn[l]*L,ans+=addn[r]*R;
            if(~l&1) ans+=sumn[l^1],L+=i;
            if(r&1) ans+=sumn[r^1],R+=i;
        }
        ans+=addn[l]*L,ans+=addn[r]*R;
        while(l>>=1) ans+=addn[l]*(L+R);
        return ans;
    }
}tree;

struct Q{
    int o,ql,qr;
    ll k;
    // o == 0 -> update l,r,val
    // 0 -- 1 -> query l r k
    Q(){}
    Q(int a,int b,int c,ll d):o(a),ql(b),qr(c),k(d){}
}query[MAXN];

int tl[MAXN],tr[MAXN],ans[MAXN];

void solve(int *a,int n,int l,int r){
    //表示要处理的询问在q[0]->q[n-1]，二分范围为[l,r]
    if(n == 0) return;
    //printf("n:%d l:%d r:%d mid:%d\n",n,l,r,mid);
    if(l == r){
        for(int i = 0;i<n;i++) ans[a[i]] = l;
        return;
    }
    int n1 = 0,n2 = 0;ll sum;
    for(int i = 0;i<n;i++){
        Q &q = query[a[i]];
        //printf("    %d :o:%d l:%d r:%d k:%lld\n",a[i],q.o,q.ql,q.qr,q.k);
        if(q.o == 1){
            if(q.k > mid) tree.update(q.ql,q.qr,1),tr[n2++] = a[i];
            else tl[n1++] = a[i];
        }
        else if(q.o == 2){
            sum = tree.query(q.ql,q.qr);
            //printf("        sum:%lld k:%lld\n",sum,q.k);
            if(q.k <= sum) tr[n2++] = a[i];
            else q.k -= sum,tl[n1++] = a[i];
        }
    }
    /*printf("n1: ");
    for(int i = 0;i<n1;i++){
        printf("%d ",tl[i]);
    }
    printf("\n");
    printf("n2: ");
    for(int i = 0;i<n2;i++){
        printf("%d ",tr[i]);
    }
    printf("\n");*/
    for(int i = 0;i<n;i++){
        Q &q = query[a[i]];
        if(q.o == 1 && q.k > mid) tree.update(q.ql,q.qr,-1);
    }
    memcpy(a,tl,sizeof(int) * n1),memcpy(a+n1,tr,sizeof(int) * n2);
    //printf("\n");
    solve(a,n1,l,mid),solve(a+n1,n2,mid+1,r);
}

int n,m,t[MAXN];

void init(){
    read(n),read(m);
    tree.init(n);
    int op,l,r;ll c;
    for(int i = 0;i<m;i++){
        read(op),read(l),read(r),read(c);
        query[i] = Q(op,l,r,c);
        t[i] = i;
    }
}

void solve(){
    solve(t,m,-n,n);
    for(int i = 0;i<m;i++){
        if(query[i].o == 2)
            print(ans[i]),print('\n');
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}