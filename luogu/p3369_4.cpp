#include <bits/stdc++.h>
#define maxint 2147483647
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

const int MAXN = 200000;

struct treap{
    int val[MAXN],p[MAXN],son[MAXN][2];
    int siz[MAXN],cnt[MAXN];
    int root,treapcnt;
    int newnode(int v){
        int x = ++treapcnt;
        son[x][0] = son[x][1] = 0;
        val[x] = v;cnt[x] = 1;p[x] = rand();
        return x;
    }
    void update(int x){
        siz[x] = cnt[x]+siz[son[x][1]]+siz[son[x][0]];
    }
    void rotate(int &x,int t){
        int y = son[x][t];
        son[x][t] = son[y][1-t];
        son[y][1-t] = x;
        update(x),update(y);
        x = y;
    }
    treap(){
        srand(19260817);
        treapcnt = root = 0;
        p[0] = maxint;
    }
    void __insert(int &x,int v){
        if(x){
            if(val[x] == v)
                cnt[x]++;
            else{
                int t = v > val[x];
                __insert(son[x][t],v);
                if(p[son[x][t]] < p[x])
                    rotate(x,t);
            }
        }
        else{
            x = newnode(v);
        }
        update(x);
    }
    void __erase(int &x,int v){
        if(val[x] == v){
            if(cnt[x]){
                cnt[x]--;
            }
            else{
                if(son[x][0] == 0 && son[x][1] == 0){
                    x = 0;return;
                }
                int t = p[son[x][0]] > p[son[x][1]];
                rotate(x,t);
                __erase(x,v);
            }
        }
        else{
            int t = val[x] < v;
            __erase(son[x][t],v);
        }
        update(x);
    }
    int get_kth(int k){
        int x = root;
        while(true){
            if(k<=siz[son[x][0]])
                x = son[x][0];
            else{
                k -= siz[son[x][0]] + cnt[x];
                if(k<=0)
                    return val[x];
                else
                    x = son[x][1];
            }
        }
    }
    int get_rank(int v){
        int x = root,ans = 0;
        while(x){
            if(v < val[x])
                x = son[x][0];
            else if(v > val[x])
                ans+=siz[son[x][0]]+cnt[x],x = son[x][1];
            else
                ans+=siz[son[x][0]],x = 0;
        }
        return ans;
    }
    void __print(int x,int dep){
        if(dep == 0)
            printf("-------------------\n");
        if(x == 0) return;
        __print(son[x][0],dep+1);
        for(int i = 0;i<dep;i++) putchar(' ');
        printf("v:%d p:%d siz:%d cnt:%d son:%d %d\n",val[x],p[x],siz[x],cnt[x],son[x][0],son[x][1]);
        __print(son[x][1],dep+1);
        if(dep == 0)
            printf("---------------------\n");
    }
    void insert(int v){
        __insert(root,v);
    }
    void erase(int v){
        __erase(root,v);
    }
    int upper(int v){
        return get_kth(get_rank(v+1)+1);
    }
    int lower(int v){
        return get_kth(get_rank(v));
    }
    void print(){
        __print(root,0);
    }
};

treap a;

int n,op,v;


int main(){
    read(n);
    for(int i = 1;i<=n;i++){
        read(op),read(v);
        if(op == 1)
            a.insert(v);
        if(op == 2)
            a.erase(v);
        if(op == 3)
            print(a.get_rank(v)+1),print('\n');
        if(op == 4)
            print(a.get_kth(v)),print('\n');
        if(op == 5)
            print(a.lower(v)),print('\n');
        if(op == 6)
            print(a.upper(v)),print('\n');
        if(op == 0)
            a.print(),--i;
    }
    flush();
    return 0;
}