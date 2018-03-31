// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read() {static const int IN_LEN = 1000000;static char buf[IN_LEN], *s, *t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x) {static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-') iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!= -1&&(c==' '||c =='\n'))c=read();while(c!=-1&&c!=' '&&c!='\n') *a++ = c,c = read();*a = 0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x) {static int buf[30], cnt;if (x == 0)print('0');else{if(x<0) print('-'),x=-x;for(cnt=0;x;x/=10) buf[++cnt] = x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

namespace normal_io{
    inline char read(){return getchar();}
    inline void read(int &x){scanf("%d",&x);}
    inline void print(int x){printf("%d",x);}
    inline void print(char x){putchar(x);}
    inline void flush(){return;}
}//using namespace normal_io;

const int MAXN = 101000,MAXQ = 1000;

int cnt[MAXN][MAXQ];
int n,m,Q;

struct pu{
    int col,id,belong;
}pgy[MAXN];

int bl[MAXQ],br[MAXQ],numc = 0;

int z[MAXQ][MAXQ];
int t[MAXN];

int id_to[MAXN];

bool cmp1(pu a,pu b){
    return a.col < b.col;
}

bool cmp2(pu a,pu b){
    return a.id < b.id;
}

void init(){
    read(n),read(m);Q = sqrt(n);
    for(int i = 1;i<=n;i++){
        read(pgy[i].col);
        pgy[i].id = i,pgy[i].belong = (i-1)/Q+1;

        if(!bl[pgy[i].belong]) 
            bl[pgy[i].belong] = i;
        br[pgy[i].belong] = i;
    }
    sort(pgy+1,pgy+n+1,cmp1);
    int lastc = 0;
    for(int i = 1;i<=n;i++){
        if(pgy[i].col!=lastc)
            numc++,id_to[numc] = pgy[i].col;
        lastc = pgy[i].col;
        pgy[i].col = numc;
    }
    sort(pgy+1,pgy+n+1,cmp2);
    
    for(int i = 1;i<=n;i++)
        cnt[pgy[i].col][pgy[i].belong]++;
    for(int i = 1;i<=numc;i++)
        for(int j = 1;j<=n/Q;j++)
            cnt[i][j] += cnt[i][j-1];
}

void build(){
    for(int i = 1;i<=n;i+=Q){
        memset(t,0,sizeof(t));
        int maxn = 0;
        for(int j = i;j<=n;j++){
            int nowc = pgy[j].col;
            t[nowc]++;
            if(t[nowc] > t[maxn] ||(t[nowc] == t[maxn] && nowc < maxn))
                maxn = nowc;
            if(j%Q == 0)
                z[(i-1)/Q+1][j/Q] = maxn;
        }
    }
}



int answer(int ql,int qr){
    int lb = pgy[ql].belong,rb = pgy[qr].belong,maxn = 0;
    //printf("lblock:%d rblock:%d\n",lb,rb);
    if(lb == rb || lb+1 == rb){
        for(int i = ql;i<=qr;i++)
            t[pgy[i].col] = 0;
        for(int i = ql;i<=qr;i++){
            int nowc = pgy[i].col;
            t[nowc]++;
            if(t[nowc] > t[maxn] ||(t[nowc] == t[maxn] && nowc < maxn))
                maxn = nowc;
        }
    }
    else{
        for(int i = ql;i<bl[lb+1];i++)
            t[pgy[i].col] = 0;
        for(int i = br[rb-1]+1;i<=qr;i++)
            t[pgy[i].col] = 0;
        maxn = z[lb+1][rb-1];
        t[maxn] = 0;
        for(int i = ql;i<bl[lb+1];i++){
            int nowc = pgy[i].col;
            t[nowc]++;
            int maxnum = t[maxn] + cnt[maxn][rb-1]-cnt[maxn][lb];
            int tmp = t[nowc] + cnt[nowc][rb-1]-cnt[nowc][lb];
            if(tmp > maxnum || (tmp == maxnum && nowc < maxn))
                maxn = nowc;
        }
        for(int i = br[rb-1]+1;i<=qr;i++){
            int nowc = pgy[i].col;
            t[nowc]++;
            int maxnum = t[maxn] + cnt[maxn][rb-1]-cnt[maxn][lb];
            int tmp = t[nowc] + cnt[nowc][rb-1]-cnt[nowc][lb];
            if(tmp > maxnum || (tmp == maxnum && nowc < maxn))
                maxn = nowc;
        }
    }
    return id_to[maxn];
}


void solve(){
    int a,b,lastans = 0;
    for(int i = 1;i<=m;i++){
        read(a),read(b);
        a = (a+lastans-1)%n+1,b = (b+lastans-1)%n+1;
        if(a > b) swap(a,b);
        lastans = answer(a,b);
        print(lastans),print('\n');
    }
}

int main(){
    freopen("1.txt","w",stdout);
    init();
    build();
    solve();
    flush();
    return 0;
}