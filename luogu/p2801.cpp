#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100000,MAXQ = 50000;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*s,*t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(s==t)t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);return s==t?-1:*s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;

int n,m,num[MAXN];

namespace fenkuai{
    int q,lb[MAXQ],rb[MAXQ],b[MAXN];//[lb,rb]
    int num[MAXN];
    void init(){
        q = sqrt(n);
        for(int i = 1,j=1;i+q-1<=n;i+=q,j++){
            lb[j] = i,rb[j] = i+q-1;
            for(int w = lb[j];w<=rb[j];w++) b[w] = j;
        }
    }
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(num[i]);
    }
}

void solve(){
    char op[10],l,r,c;
    for(int i = 1;i<=m;i++){
        read(op);

    }
}

int main(){
    return 0;
}