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

const int MAXN = 200000,logn = 20;

namespace BCJ{
    int f[MAXN][logn];
    void init(int n){
        for(int i = 1;i<=n;i++)
            for(int j = 0;j<logn;j++)
                f[i][j] = i;
    }
    int find(int x,int k){
        return f[x][k] == x?x:f[x][k] = find(f[x][k],k);
    }
    void merge(int a,int b,int k){
        //printf("    :%d %d %d\n",a,b,k);
        int fa = find(a,k),fb = find(b,k);
        if(fa!=fb)
            f[fb][k] = fa;
    }
}using namespace BCJ;

int n,m;

void init(){
    read(n),read(m);
    int l1,r1,l2,r2,len;
    init(n);
    for(int i = 1;i<=m;i++){
        read(l1),read(r1),read(l2),read(r2);
        len = 0;
        while((1<<(len+1)) <= (r1-l1+1))len++;
        //printf("%d:%d\n",i,len);
        merge(l1,l2,len);
        merge(r1-(1<<len)+1,r2-(1<<len)+1,len);
    }
}

void solve(){
    for(int j = logn-1;j>=0;--j){
        /*for(int i = 1;i<=n;i++){
            printf("%d ",f[i][j]);
        }
        putchar('\n');*/
        if(j == 0) continue;
        for(int i = 1;i <= n;i++){
            int fa = find(i,j);
            if(fa != i){
                merge(i,fa,j-1);
                merge(i + (1<<(j-1)),fa + (1<<(j-1)),j-1);
            }
        }
    }
    int ans = 0;
    for(int i = 1;i<=n;i++){
        if(find(i,0) == i)
            ans++;
    }
    long long sum = 9;
    for(int i = 1;i<ans;i++){
        sum *= 10;
        sum %= 1000000007;
    }
    printf("%lld\n",sum);
}

int main(){
    init();
    solve();
    return 0;
}