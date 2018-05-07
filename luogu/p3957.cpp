#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define pp pair<int,int>
#define int long long
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
}using namespace fast_io;

inline int max(const int a,const int b){return (a>b)?(a):(b);}
inline int min(const int a,const int b){return (a<b)?(a):(b);}
const int MAXN = 1000000;


namespace dan{
    pp q[MAXN<<2];
    int head,tail;
    //[head,tail)
    void clear(){
        head = tail = 0;
    }
    void insert(pp a){
        int i;
        for(i = tail;i>head;i--){
            if(a.second < q[i-1].second)
                break;
        }
        tail = i+1;
        q[i] = a;
    }
    int query(){
        if(head == tail) 
            return -0x3f3f3f3f3f;
        return q[head].second;
    }
    void update(int mindis){
        int i;
        for(i = head;i<tail;i++){
            if(q[i].first >= mindis)
                break;
        }
        head = i;
    }
}

int n,d,k;
int dis[MAXN],num[MAXN];

void init(){
    read(n),read(d),read(k);
    for(int i = 1;i<=n;i++)
        read(dis[i]),read(num[i]);
}

bool check(int g)
{
    static int dp[MAXN];
    memset(dp,0,sizeof(dp));
    dan::clear();
    int nowp = 0;
    for(int i = 1;i<=n;i++){
        while(dis[nowp] <= dis[i]-max(d-g,1))
            dan::insert(make_pair(dis[nowp],dp[nowp])),nowp++;
        dan::update(max(0,dis[i] - (d+g)));
        dp[i] = dan::query() + num[i];
    }
    int maxn = 0;
    for(int i = 0;i<=n;i++)
        maxn = max(maxn,dp[i]);
    return maxn>=k;
}

void solve(){
    int b = 0,e = 2333333;
    while(b!=e){
        int mid = (b+e)>>1;
        if(check(mid))
            e = mid;
        else
            b = mid+1;
    }
    if(b >= 1000000)
        printf("-1\n");
    else
        printf("%lld\n",b);
}

signed main(){
    init();
    solve();
    return 0;
}