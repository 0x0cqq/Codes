#include <cstdio>
#include <algorithm>
#include <vector>
#include <cctype>
#define pp pair<int,int>
#define pos first
#define col second
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

const int MAXM = 100;

int n,k;

int cnt[MAXM],sum = 0,ans = 0x3f3f3f3f;

vector<pp> T;

int main(){
    scanf("%d %d",&n,&k);
    for(int i = 1;i<=k;i++){
        int t,w;
        read(t);
        for(int j = 1;j<=t;j++){
            read(w);
            T.push_back(make_pair(w,i));
        }
    }
    sort(T.begin(),T.end());
    int l = 0,r = 0;
    while(r < T.size()){
        if(cnt[T[r++].col]++ == 0) sum++;
        while(true){
            if(cnt[T[l].col]-1 != 0)
                cnt[T[l++].col]--;
            else
                break;
        }
        if(sum == k) ans = min(ans,T[r-1].pos - T[l].pos);
    }
    printf("%d\n",ans);
    return 0;
}