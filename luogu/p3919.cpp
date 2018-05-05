#include <cstdio>
#include <cctype>
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

const int MAXN = 1100000;

namespace persistentSegTree{
    int val[MAXN*25],ls[MAXN*25],rs[MAXN*25],cnt = 1;
    inline void build(int &nown,int l,int r,int *num){
        nown = cnt++;
        if(l == r)
            val[nown] = num[l];
        else{
            int mid = (l+r)>>1;
            build(ls[nown],l,mid,num);
            build(rs[nown],mid+1,r,num);
        } 
    }
    inline void update(int &nown,int pre,int l,int r,int pos,int v){
        nown = cnt++;ls[nown] = ls[pre],rs[nown] = rs[pre];val[nown] = val[pre];
        if(l == r)
            val[nown] = v;
        else{
            int mid = (l+r) >> 1;
            if(pos <= mid) 
                update(ls[nown],ls[pre],l,mid,pos,v);
            else 
                update(rs[nown],rs[pre],mid+1,r,pos,v);
        }
    }
    inline int query(int nown,int l,int r,int pos){
        if(l == r)
            return val[nown];
        else{
            int mid = (l+r) >> 1;
            if(pos <= mid)
                return query(ls[nown],l,mid,pos);
            else
                return query(rs[nown],mid+1,r,pos);
        }
    }
}

int n,m,num[MAXN];
int root[MAXN];

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++)
        read(num[i]);
    persistentSegTree::build(root[0],1,n,num);
}

void solve(){
    int ver,op,pos,a;
    for(int i = 1;i<=m;i++){
        read(ver),read(op),read(pos);
        if(op == 1){
            read(a);
            persistentSegTree::update(root[i],root[ver],1,n,pos,a);
        }
        else{
            root[i] = root[ver];
            print(persistentSegTree::query(root[ver],1,n,pos)),print('\n');
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}