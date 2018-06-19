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

const int MAXN = 110000;

int n,a_0;
int a[MAXN],r[MAXN];

void init(){
	read(n),read(a_0);
	for(int i = 1;i<=n;i++){
		read(a[i]),read(r[i]);
	}
}

void solve(){
	double sum = 0;int nowr = 0;
	a[0] = a_0;
	for(int i = 1;i<=n;i++){
		while(nowr <= r[i])
			sum += a[nowr++];
		// printf("%d %lf\n",i,sum);
		if(sum < a[i]*5){
			printf("-1\n");
			return;
		}
		else{
			sum -= a[i]*5;
		}
	}
	while(nowr <= n){
		sum += a[nowr++];
	}
	printf("%lf\n",sum/5);

}

int main(){
	init();
	solve();
	return 0;
}