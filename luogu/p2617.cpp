#include <cstdio>
#include <algorithm>
#include <cctype>
#include <map>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 50000;

int n,m,totn = 0;
int rt[MAXN],num[MAXN];

int lowbit(int x){return x & (-x);}

namespace prSegTree{
    int val[MAXN*50],ls[MAXN*50],rs[MAXN*50];
    int cnt = 0;int ll[MAXN],rr[MAXN],totx,toty;
    #define mid ((l+r) >> 1)
    void insert(int &nown,int pre,int l,int r,int pos,int d){
        nown = ++cnt;val[nown] = val[pre];
        ls[nown] = ls[pre],rs[nown] = rs[pre];
        if(l == r){
            val[nown] += d;
        }
        else{
            val[nown] += d;
            if(pos <= mid)
                insert(ls[nown],ls[pre],l,mid,pos,d);
            else if(pos >= mid+1)
                insert(rs[nown],rs[pre],mid+1,r,pos,d);
        }
    }
    void update(int pos,int v,int d){
        for(int i = pos;i<=totn;i += lowbit(i))
            insert(rt[i],rt[i],1,totn,v,d);
    }
    void add(int l,int r){
        totx = toty = 0;
        for(int i = l-1;i;i-=lowbit(i))
            ll[++totx] = rt[i];
        for(int i = r;i;i-=lowbit(i))
            rr[++toty] = rt[i];
    }
    int find_kth(int l,int r,int k){
        int sum = 0;
        if(l == r){
            return l;
        }
        else{
            for(int i = 1;i<=totx;i++) sum -= val[ls[ll[i]]];
            for(int i = 1;i<=toty;i++) sum += val[ls[rr[i]]];   
            if(k <= sum){
                for(int i = 1;i<=totx;i++)  ll[i] = ls[ll[i]];
                for(int i = 1;i<=toty;i++)  rr[i] = ls[rr[i]];
                return find_kth(l,mid,k);
            }
            else{
                for(int i = 1;i<=totx;i++)  ll[i] = rs[ll[i]];
                for(int i = 1;i<=toty;i++)  rr[i] = rs[rr[i]];
                return find_kth(mid+1,r,k-sum);
            } 
        }  
    }
    int query(int l,int r,int k){
        add(l,r);
        return find_kth(1,totn,k);
    }
}
 
map<int,int> S;int last[MAXN];

int op[MAXN],ql[MAXN],qr[MAXN],v[MAXN];

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(num[i]),S[num[i]] = 0;
    char t[23];
    for(int i = 1;i<=m;i++){
        read(t);read(ql[i]),read(qr[i]);
        if(t[0] == 'Q') op[i] = 1,read(v[i]);
        else S[qr[i]] = 0;
    }
    for(auto it = S.begin();it != S.end();it++)
        it->second = ++totn,last[totn] = it->first;
    for(int i = 1;i<=n;i++)
        prSegTree::update(i,S[num[i]],1);
}

void solve(){
    for(int i = 1;i<=m;i++){
        if(op[i] == 0)
            prSegTree::update(ql[i],S[num[ql[i]]],-1),
            prSegTree::update(ql[i],S[qr[i]],1),num[ql[i]] = qr[i]; 
        else
            print(last[prSegTree::query(ql[i],qr[i],v[i])]),print('\n');
    }
}


int main(){
    init();
    solve();
    flush();
    return 0;
}