#include <cstdio>
#include <algorithm>
#include <set>
#include <cctype>
using namespace std;

const int MAXN = 1100000;

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

int n,m,ans = 0;
int num[MAXN],re[MAXN];
set<int> S[MAXN];

void update(int last,int now){
    bool flag = 0;
    //printf("%d %d %d\n",last,now,int(flag));
    //for(int i = 1;i<=n;i++){
    //    printf("%d ",num[i]);
    //}
    //printf("\n");
    for(set<int>::iterator it = S[last].begin();it!=S[last].end();it++){
        //printf("    :%d\n",*it);
        if(num[(*it)-1] == (now)) 
            ans--;
        if(num[(*it)+1] == (now))
            ans--;
        S[now].insert(*it);
    }
    for(set<int>::iterator it = S[last].begin();it!=S[last].end();it++)
        num[*it] = now;
    S[last].clear();
}

void init(){
    read(n),read(m);
    for(int i = 1;i<=n;i++){
        read(num[i]);
        if(num[i]!=num[i-1]) ans++;
        S[num[i]].insert(i);
        re[num[i]] = num[i];
    }
}

void solve(){
    int op,a,b;
    for(int i = 1;i<=m;i++){
        read(op);
        if(op == 1){
            read(a),read(b);
            if(a == b) continue;
            if(S[re[a]].size() > S[re[b]].size()) swap(re[a],re[b]);
            update(re[a],re[b]);
        }
        else if(op == 2){
            print(ans),print('\n');
        }
    }
}

int main(){
    init();
    solve();
    flush();
    return 0;
}