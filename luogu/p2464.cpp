#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

inline int randad(){
   static int seed=447;
   return seed=int(seed*48271LL%2147483647);
}

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

const int MAXN = 500000;

namespace Treap{
    int p[MAXN],siz[MAXN];
    int son[MAXN][2];int tot;
    void init(){
        tot = 1;
        p[0] = 2147483647;
        son[0][0] = son[0][1] = 0;
        siz[0] = 0;
    }
    void maintain(int x){
        if(x == 0) return;
        siz[x] = siz[son[x][0]] + siz[son[x][1]] +1;
    }
    void rotate(int &x,int t){
        int y = son[x][t];
        son[x][t] = son[y][1-t];
        son[y][1-t] = x;
        maintain(x),maintain(y);
        x = y;
    }
    void insert(int &x,int v){
        if(x == 0){
            x = v;p[x] = randad();
            siz[x] = 1;
            son[x][0] = son[x][1] = 0;
        }
        else{
            int t = v > x;
            insert(son[x][t],v);
            if(p[son[x][t]] < p[x])
                rotate(x,t);
        }
        maintain(x);
    }
    void erase(int &x,int v){
        if(x == v){
            if(son[x][0] == 0 && son[x][1] == 0)
                x = 0;
            else{
                int t = p[son[x][0]] > p[son[x][1]];
                rotate(x,t);
                erase(x,v);
            }
        }
        else{
            int t = v > x;
            erase(son[x][t],v);
        }
        maintain(x);
    }
    int getrank(int x,int v){
        if(x == 0) return 0; 
        if(v == x)
            return siz[son[x][0]];
        else if(v < x)
            return getrank(son[x][0],v);
        else
            return getrank(son[x][1],v) + siz[son[x][0]]+1;
    } 
    void print(int x,int depth = 0){
        if(depth == 0){
            printf("----------------------\n");
        }
        if(x == 0)
            return;
        print(son[x][0],depth+1);
        printf("%d: siz:%d p:%d son:%d %d\n",x,siz[x],p[x],son[x][0],son[x][1]);
        print(son[x][1],depth+1);
        if(depth == 0){
            printf("----------------------\n\n");
        }
    }
}

int n,m;
map<int,int> s;
int num[MAXN],root[MAXN],cnt = 1;

void insert(int pos,int v){
    if(!s.count(v))
        s[v] = ++cnt;
    Treap::insert(root[s[v]],pos);
}

void erase(int pos,int v){
    Treap::erase(root[s[v]],pos);
}

void update(int pos,int v){
    erase(pos,num[pos]);
    insert(pos,v);
    num[pos] = v;
}

int query(int l,int r,int k){
    if(!s.count(k))
        return 0;
    return Treap::getrank(root[s[k]],r+1) - Treap::getrank(root[s[k]],l);
}

void init(){
    read(n),read(m);
    Treap::init();
    for(int i = 1;i<=n;i++){
        read(num[i]);
        insert(i,num[i]);
    }
}

void solve(){
    char op[10];
    int a,b,k;
    for(int i = 1;i<=m;i++){
        read(op),read(a),read(b);
        if(op[0] == 'Q'){
            read(k);
            print(query(a,b,k)),print('\n');
        }
        else if(op[0] == 'C'){
            update(a,b);
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}