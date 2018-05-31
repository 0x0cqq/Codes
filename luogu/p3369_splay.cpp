#include <cstdio>
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

const int MAXN = 510000;

struct Splay{
    int val[MAXN],siz[MAXN],cnt[MAXN];
    int c[MAXN][2],f[MAXN];
    int tot,root;
    int newnode(int v = 0){
        val[++tot] = v;
        return tot;
    }
    void maintain(int x){
        if(!x) return;
        siz[x] = siz[c[x][0]] + siz[c[x][1]] + cnt[x];
    }
    void rotate(int x){
        int y = f[x],z = f[y],t =(c[y][1]==x),w = c[x][1-t];
        if(z) c[z][c[z][1]==y] = x;
        c[x][1-t] = y,c[y][t] = w;
        if(w) f[w] = y;
        f[y] = x;f[x] = z;
        maintain(y),maintain(x);
        if(!f[x]) root = x;
    }
    void splay(int x,int target = 0){
        if(!x) return;
        while(f[x]!=target){
            int y = f[x],z = f[y];
            if(z!=target){
                (c[y][1]==x)^(c[z][1]==y)?rotate(x):rotate(y);
            }rotate(x);
        }
    }
    int find(int v){
        int x = root;
        while(x && val[x]!=v)
            x = c[x][val[x] < v];
        splay(x);
        return x;
    } 
    int __qrank(int r){//寻找排名为r的数的编号
        int x = root;
        while(x){
            if(r <= siz[c[x][0]])
                x = c[x][0];
            else if(r <= siz[c[x][0]] + cnt[x])
                break;
            else
                r-=(siz[c[x][0]] + cnt[x]),x = c[x][1];
        }
        splay(x);
        return x;
    }
    int getrank(int v){//寻找数v的排名
        int x = root,ans = 0;
        while(x && val[x] != v){
            if(v < val[x])
                x = c[x][0];
            else
                ans += siz[c[x][0]]+cnt[x],x = c[x][1];
        }
        ans += siz[c[x][0]]+1;splay(x);
        return ans;
    }
    int loworup(int v,int t){
        int last = 0,x = root;//last表示上一个没有当前寻找方向的节点
        while(x && val[x] != v){
            last = (val[x]<v)^t?x:last;
            x = c[x][val[x] < v];
        }
        if(c[x][t]){
            last = c[x][t];
            while(c[last][1-t]) last = c[last][1-t];
        }
        return last;
    }
    void insert(int v){
        int x = root,y = 0;
        while(x && val[x]!=v)
            siz[x]++,y = x,x = c[x][val[x] < v];
        if(x)  cnt[x]++,siz[x]++;
        else{
            x = newnode(v);
            if(y) c[y][val[y] < v] = x;
            f[x] = y;siz[x] = cnt[x] = 1;
            if(!f[x]) root = x;
        }
        splay(x);
    }
    void erase(int v){
        int x = find(v);
        splay(x);
        if(cnt[x] > 1) cnt[x]--,siz[x]--;
        else{
            int l = loworup(v,0),r = loworup(v,1);
            splay(l),splay(r,l);
            c[r][0] = 0;
            maintain(r),maintain(l);
        }
    }
    void print(){
        __print(root,0);
    }
    void __print(int x,int depth){
        if(depth == 0) printf("-----------------\n");
        if(!x) return;
        __print(c[x][0],depth+1);
        for(int i = 0;i<depth;i++) putchar(' ');
        printf("%d: val:%d siz:%d(cnt:%d) c:%d %d f:%d\n",x,val[x],siz[x],cnt[x],c[x][0],c[x][1],f[x]);
        __print(c[x][1],depth+1);
        if(depth == 0) printf("-----------------\n");
    }
    int lower(int v){
        return val[loworup(v,0)];
    }
    int upper(int v){
        return val[loworup(v,1)];
    }
    int qrank(int r){
        return val[__qrank(r)];
    }
}T;

int n,op,a;


void solve(){
    read(n);
    T.insert(-0x3f3f3f3f),T.insert(0x3f3f3f3f);
    for(int i = 1;i<=n;i++){
        read(op),read(a);
        //printf("operation %d\n",i);
        if(op == 1)
            T.insert(a);
        else if(op == 2)
            T.erase(a);
        else if(op == 3)
            print(T.getrank(a)-1),print('\n');
        else if(op == 4)
            print(T.qrank(a+1)),print('\n');
        else if(op == 5)
            print(T.lower(a)),print('\n');
        else if(op == 6)
            print(T.upper(a)),print('\n');
        else if(op == 0)
            T.print(),--i;
    }
}

int main(){
    solve();
    flush();
    return 0;
}