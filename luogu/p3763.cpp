#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>
using namespace std;

namespace fast_io{
    inline char read(){static const int SIZE=1024*1024;static char ibuf[SIZE],*s,*t;if(s==t)t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);return s==t?-1:*s++;}
    template<typename T>inline void read(T&x){static char c;static bool iosig;for(iosig=0,c=read();!isdigit(c);c=read()){if(c==-1)return;iosig|=(c=='-');}for(x=0;isdigit(c);c=read())x=(((x<<2)+x)<<1)+(c^48);if(iosig)x=-x;return;}
    inline void read(char*a){static char c=read();while(c!=-1&&(c==' '||c!='\r'||c=='\n'))c=read();while(c!=-1&&c!=' '&&c!='\r'&&c!='\n')*a++=c,c=read();*a=0;}
}using namespace fast_io;


const int MAXN = 210000;

namespace SA{
int sa[MAXN],rk[MAXN],ht[MAXN],s[MAXN<<1],t[MAXN<<1];
int p[MAXN],b[MAXN],cur[MAXN];
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v)\
    fill_n(b,m,0),fill_n(sa,n,-1);\
    for(int i=0;i<n;i++) b[s[i]]++;\
    for(int j=1;j<m;j++) b[j]+=b[j-1];\
    for(int j=0;j<m;j++) cur[j] = b[j]-1;\
    for(int i=n1-1;~i;--i) pushS(v[i]);\
    for(int j=1;j<m;j++) cur[j] = b[j-1];\
    for(int i=0;i<n;i++) if(sa[i]>0 && t[sa[i]-1]) pushL(sa[i]-1);\
    for(int j=0;j<m;j++) cur[j] = b[j]-1;\
    for(int i=n-1;~i;--i) if(sa[i]>0 && !t[sa[i]-1]) pushS(sa[i]-1);
void sais(int n,int m,int *s,int *t,int *p){
    int n1 = t[n-1] = 0,ch = rk[0] = -1,*s1 = s+n;
    for(int i=n-2;~i;--i) t[i] = s[i]==s[i+1]?t[i+1]:s[i]>s[i+1];
    for(int i=1;i<n;i++) rk[i] = (t[i-1]&&!t[i])?(p[n1] = i,n1++):-1;
    inducedSort(p);
    for(int i=0,x,y;i<n;i++)if(~(x=rk[sa[i]])){
        if(ch<1||p[x+1]-p[x]!=p[y+1]-p[y]) ch++;
        else for(int j=p[x],k=p[y];j<=p[x+1];j++,k++)
            if((s[j]<<1|t[j]) != (s[k]<<1|t[k])){ch++;break;}
        s1[y=x] = ch;
    }
    if(ch+1 < n1) sais(n1,ch+1,s1,t+n,p+n1);
    else for(int i = 0;i<n1;i++) sa[s1[i]] = i;
    for(int i = 0;i<n1;i++) s1[i] = p[sa[i]];
    inducedSort(s1);
}
template <typename T>
int mapChartoInt(int n,const T *str){
    int m = *max_element(str,str+n);
    fill_n(rk,m+1,0);//+1!!!
    for(int i = 0;i<n;i++) rk[str[i]] = 1;//=1!
    for(int j = 0;j<m;j++) rk[j+1] += rk[j]; 
    for(int i = 0;i<n;i++) s[i] = rk[str[i]]-1;
    return rk[m];
}
// str[n] yange zidianxu zuixiao
template <typename T>
void suffixArray(int n,const T *str){
    int m = mapChartoInt(++n,str);
    sais(n,m,s,t,p);
}
void getHeight(int n){
    // 这里的循环一定要到a！
    for(int i = 0;i<=n;i++) rk[sa[i]] = i;
    for(int i = 0,h = ht[0] = 0;i<=n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n && j+h<n && s[i+h] == s[j+h]) h++;
        if(ht[rk[i]] = h) --h;
    }
}
}

int n,x,y;
char s[MAXN];

namespace ST{
    int st[20][MAXN];
    void build(int n,int *num){
        for(int i = 1;i<=n;i++) st[0][i] = num[i];
        for(int j = 1,t = 2;t<=n;j++,t<<=1){
            for(int i = 1;i+(t>>1)<=n;i++){
                st[j][i] = min(st[j-1][i],st[j-1][i+(t>>1)]);
                // printf("i:%d j:%d val:%d\n",i,j,st[j][i]);
            }
            // printf("\n");
        }
    }
    int query(int l,int r){
        int t = log2(r-l+1);
        //printf("%d\n", t);
        return min(st[t][l],st[t][r-(1<<t)+1]);
    }
}

void init(){
    read(s);
    x = strlen(s);
    read(s+x);
    n = strlen(s);
    y = n-x;
    s[n] = 'A'-1;
    SA::suffixArray(n,s);
    SA::getHeight(n);
    ST::build(n,SA::ht);
    // for(int i = 1;i<=n;i++)
    //     printf("%d ",SA::sa[i]+1);
    // printf("\n");
    // for(int i = 1;i<=n;i++)
    //     printf("%d ",SA::ht[i]);
    // printf("\n");
}

int lcp(int a,int b){
    if(a == b) return n - a + 1;
    a = SA::rk[a],b = SA::rk[b];
    if(a > b) swap(a,b);
    return ST::query(a+1,b);
}

bool judge(int p){
    int cnt = 0,len = 0;
    while(len < y){
        // printf("cnt:%d len:%d lcp:%d\n",cnt,len,lcp(p+len,x+len));
        len += lcp(p+len,x+len);
        if(cnt >= 3 && len < y) return false;
        len++,cnt++;
    }
    return true;
}

void solve(){
    int ans = 0;
    for(int i = 0;i<=x-y;i++){
        if(judge(i))
            ans++;
        // printf("%d:%d\n",i,ans);
    }
    printf("%d\n",ans);
}

int main(){
    int T;
    read(T);
    for(int i = 1;i<=T;i++){
        init();
        solve();
    }
    return 0;
}