#include <cstdio>
#include <cstring>
#include <cctype>
#include <ctime>
#include <queue>
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

const int MAXN = 200010;

struct Edge{
    int to,len,nex;
}edge[MAXN];

int fir[MAXN],n,m,t,cc,cnt;

void addedge(int f,int t,int l){
    edge[cnt] = (Edge){t,l,fir[f]};
    fir[f] = cnt++;
}

int dis[MAXN],instack[MAXN],times[MAXN];

queue<int> q;

void init(){
    memset(fir,0,sizeof(fir));
    memset(dis,0x3f,sizeof(dis));
    memset(instack,0,sizeof(instack));
    memset(times,0,sizeof(times));
    while(!q.empty()) q.pop();
    cnt = 1;
}

bool spfa(int s){
    //st = clock();
    dis[s] = 0;q.push(s);
    while(!q.empty()){
        int nown = q.front();q.pop();
        instack[nown] = 0;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to,l = edge[nowe].len;
            if(dis[v] > dis[nown] + l){
                dis[v] = dis[nown] + l; 
                if(++times[v] >= n)
                    return true;
                if(instack[v] == 0){
                    instack[v] = 1;
                    q.push(v);
                }
           }
        }
    }
    return false;
}

int main(){
    read(t);
    for(int i = 1;i<=t;i++){
        init();
        read(n),read(m);cc = n;
        for(int i = 1;i<=m;i++){
            int a,b,c;
            read(a),read(b),read(c);
            addedge(a,b,c);
            if(c>=0) addedge(b,a,c);
        }
        if(spfa(1))
            print('Y'),print('E'),print('5');
        else
            print('N'),print('0');
        print('\n');
    }
    flush();
    return 0;
}