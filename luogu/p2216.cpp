#include <cstdio>
#include <queue>
#include <cctype>
#include <algorithm>
#define pp pair<int,int>
using namespace std;

const int MAXN = 1100;

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

int n,m,k;
int num[MAXN][MAXN];

deque<pp> max1[MAXN],min1[MAXN];
deque<pp> max2,min2;

void init(){
    read(n),read(m),read(k);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            read(num[i][j]);
        }
    }
}


void solve(){
    int ans = 0x3f3f3f3f;
    static int minn[MAXN],maxn[MAXN];
    int tmin,tmax;
    for(int i = 1;i<=n;i++){
        //printf("i %d:\n",i);
        for(int j = 1;j<=m;j++){
            //max
            while(!max1[j].empty()&&max1[j].begin()->second < num[i][j])
                max1[j].pop_front();
            max1[j].emplace_front(i,num[i][j]);
            while(!max1[j].empty()&&max1[j].rbegin()->first <= i-k)
                max1[j].pop_back();
            tmax = max1[j].rbegin()->second;
            maxn[j] = tmax;
            //printf("a\n");
            //min
            while(!min1[j].empty()&&min1[j].begin()->second > num[i][j])
                min1[j].pop_front();
            min1[j].emplace_front(i,num[i][j]);
            while(!min1[j].empty()&&min1[j].rbegin()->first <= i-k)
                min1[j].pop_back();
            tmin = min1[j].rbegin()->second;
            minn[j] = tmin;
            //printf("b\n");
            //printf("    j:%d max:%d min:%d\n",j,tmax,tmin);
        }
        max2.clear(),min2.clear();
        for(int j = 1;j<=m;j++){
            //max
            while(!max2.empty()&&max2.begin()->second < maxn[j])
                max2.pop_front();
            max2.emplace_front(j,maxn[j]);
            while(!max2.empty()&&max2.rbegin()->first <= j-k)
                max2.pop_back();
            tmax = max2.rbegin()->second;
            //printf("a\n");
            //min
            while(!min2.empty()&&min2.begin()->second > minn[j])
                min2.pop_front();
            min2.emplace_front(j,minn[j]);
            while(!min2.empty()&&min2.rbegin()->first <= j-k)
                min2.pop_back();
            tmin = min2.rbegin()->second;
            //printf("b\n");
            //printf("    j:%d max:%d min:%d\n",j,tmax,tmin);
            if(i>=k && j>=k)
                ans = min(tmax-tmin,ans);
        }
    }
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}