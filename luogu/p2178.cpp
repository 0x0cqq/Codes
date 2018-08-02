#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define ll long long

const int MAXN = 310000;

namespace fast_io{
    static const int SIZE=1024*1024;char ibuf[SIZE],*_s,*_t,obuf[SIZE],*oh=obuf;inline void flush(){fwrite(obuf,1,oh-obuf,stdout);}
    inline char read(){if(_s==_t)_t=(_s=ibuf)+fread(ibuf,1,SIZE,stdin);return _s==_t?-1:*_s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c=='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
    inline void print(char c){if(oh==obuf+SIZE)fwrite(obuf,1,SIZE,stdout),oh=obuf;*oh++=c;}
    template<typename T>inline void print(T x){static int buf[21],cnt;if(!x)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while(cnt)print((char)buf[cnt--]);}}
    inline void print(char*a){while(*a)print(*a++);}
}using namespace fast_io;


namespace SA{
int s[MAXN],sa[MAXN],ht[MAXN],rk[MAXN],x[MAXN],y[MAXN],cnt[MAXN];
void get_sa(int n,int m){
    for(int i = 0;i<m;i++) cnt[i] = 0;
    for(int i = 0;i<n;i++) cnt[s[i]]++;
    for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
    for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
    m = rk[sa[0]] = 0;
    for(int i = 1;i<n;i++) rk[sa[i]] = s[sa[i]] != s[sa[i-1]]?++m:m;
    for(int j = 1;;j<<=1){
        if(++m == n) break;
        for(int i = 0;i<j;i++) y[i] = n-j+i;
        for(int i = 0,k=j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i]-j;
        for(int i = 0;i<n;i++) x[i] = rk[y[i]];
        for(int i = 0;i<m;i++) cnt[i] = 0;
        for(int i = 0;i<n;i++) cnt[x[i]]++;
        for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
        for(int i = n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
        m = rk[sa[0]] = 0;
        for(int i = 1;i<n;i++) rk[sa[i]] =(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+j]!=y[sa[i-1]+j])?++m:m;
    }
}
template<typename T>
int mapCharToInt(int n,const T *str){
    int m = *max_element(str,str+n);
    for(int i = 0;i<=m;i++) rk[i] = 0;
    for(int i = 0;i<n;i++) rk[(int)(str[i])] = 1;
    for(int i = 1;i<=m;i++) rk[i] += rk[i-1];
    for(int i = 0;i<n;i++) s[i] = rk[(int)(str[i])]-1;
    return rk[m]; 
}
void getheight(int n){
    for(int i = 0,h = ht[0] = 0;i<n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) h++;
        if(ht[rk[i]] = h) h--;
    }
}
void build(int n,char *str){
    int m = mapCharToInt(++n,str);
    get_sa(n,m);
    getheight(n);
}
}


namespace BCJ{
    int f[MAXN],siz[MAXN];
    ll maxn[MAXN],minn[MAXN];
    void init(int n,ll * val){
        for(int i = 0;i<=n;i++){
            f[i] = i,siz[i] = 1;
            maxn[i] = minn[i] = val[i];
        }
    }
    int find(int x){
        return f[x] == x?x:f[x] = find(f[x]);
    }
    bool same(int x,int y){
        return find(x) == find(y);
    }
    ll unite(int x,int y,ll &ans){
        int fx = find(x),fy = find(y);
        if(fx == fy) return 0;
        ans = max(ans,maxn[fx]*maxn[fy]);
        ans = max(ans,minn[fx]*minn[fy]);
        f[fy] = fx;
        minn[fx] = min(minn[fx],minn[fy]);
        maxn[fx] = max(maxn[fx],maxn[fy]);
        ll res = 1LL*siz[fx] * siz[fy];
        siz[fx] += siz[fy];
        return res;
    }
}

bool cmp(int a,int b){
    return SA::ht[a] > SA::ht[b];
}

char str[MAXN];
int n,m;
ll a[MAXN],ans[MAXN],cnt[MAXN];

void init(){
    static ll min1 = inf,min2 = inf,max1 = -inf,max2 = -inf;
    read(n);
    read(str);
    str[n] = 'a'-1;
    for(int i = 1;i<=n;i++){
        read(a[i]);
        if(a[i] < min1) min1=a[i];
        else if(a[i] < min2) min2=a[i];
        if(a[i] > max1) max1=a[i];
        else if(a[i] > max2) max2=a[i];
        ans[i] = -1LL*inf*inf;      
    }
    ans[0] = max(max1*max2,min1*min2);
}

void solve(){
    static int h[MAXN];
    SA::build(n,str);
    BCJ::init(n,a);
    for(int i = 1;i<=n;i++) h[i] = i;
    sort(h+1,h+n+1,cmp);
    for(int i = 1;i<=n;i++){
        int x = h[i],ht = SA::ht[x];//merge(h[i],h[i]-1) -> SA::ht[h[i]]
        // printf("x:%d ht:%d\n",x,ht);
        // printf("merge:%d %d\n",SA::sa[x]+1,SA::sa[x-1]+1);
        if(x!=1)
            cnt[ht] += BCJ::unite(SA::sa[x]+1,SA::sa[x-1]+1,ans[ht]);
        // printf("cnt:%lld\n",cnt[ht]);
    }  
    for(int i = n-2;i>=0;i--){
        cnt[i] += cnt[i+1];
        ans[i] = max(ans[i],ans[i+1]);
    }
    cnt[0] = 1LL*n*(n-1)/2;
    for(int i = 0;i<n;i++){
        if(!cnt[i]) ans[i] = 0;
        print(cnt[i]),print(' '),print(ans[i]),print('\n');
    }
}

signed main(){
    init();
    solve();
    flush();
    return 0;
}