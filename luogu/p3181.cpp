#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 233333;

template<size_t siz>
struct SA{
int s[siz<<1],p[siz],t[siz<<1];
int sa[siz],rk[siz],ht[siz];
int b[siz],cur[siz];
#define pushL(x) sa[cur[s[x]]++] = x
#define pushS(x) sa[cur[s[x]]--] = x
#define inducedSort(v)\
    fill_n(b,m,0),fill_n(sa,n,-1);\
    for(int i = 0;i<n;i++) b[s[i]]++;\
    for(int i = 1;i<m;i++) b[i] += b[i-1];\
    for(int i = 0;i<m;i++) cur[i] = b[i]-1;\
    for(int i=n1-1;~i;--i) pushS(v[i]);\
    for(int i = 1;i<m;i++) cur[i] = b[i-1];\
    for(int i = 0;i<n;i++) if(sa[i]>0&&t[sa[i]-1]) pushL(sa[i]-1);\
    for(int i = 0;i<m;i++) cur[i] = b[i]-1;\
    for(int i =n-1;~i;--i) if(sa[i]>0&&!t[sa[i]-1]) pushS(sa[i]-1);
void sais(int n,int m,int *s,int *t,int *p){
    int ch = rk[0] = -1,n1 = t[n-1] = 0,*s1 = s+n;
    for(int i = n-2;~i;--i) t[i] = s[i]==s[i+1]?t[i+1]:s[i]>s[i+1];
    for(int i = 1;i<n;i++) rk[i] = (!t[i]&&t[i-1])?(p[n1]=i,n1++):-1;
    inducedSort(p);
    for(int i = 0,x,y;i<n;i++)if(~(x=rk[sa[i]])){
        if(ch<1||p[x+1]-p[x] != p[y+1]-p[y]) ch++;
        else for(int j=p[x],k=p[y];j<=p[x+1];j++,k++)
            if((s[j]<<1|t[j])!=(s[k]<<1|t[k])){ch++;break;}
        s1[y=x] = ch;
    }
    if(ch+1 < n1) sais(n1,ch+1,s1,t+n,p+n1);
    else for(int i = 0;i<n1;i++) sa[s1[i]] = i;
    for(int i = 0;i<n1;i++) s1[i] = p[sa[i]];
    inducedSort(s1);
}
template<typename T>
int mapp(const T *str,int n){
    int m = *max_element(str,str+n);
    fill_n(rk,m+1,0);
    for(int i = 0;i<n;i++) rk[str[i]] = 1;
    for(int i = 0;i<m;i++) rk[i+1] += rk[i];
    for(int i = 0;i<n;i++) s[i] = rk[str[i]]-1;
    return rk[m];
}
// 这个时候传正确的字符串大小，++n对str[n]做处理
template<typename T>
void SuffixArray(const T *str,int n){
    int m = mapp(str,++n);
    sais(n,m,s,t,p);
}
void getheight(int n){
    for(int i = 0;i<=n;i++) rk[sa[i]] = i;
    for(int i = 0,h=ht[0]=0;i<=n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h]) ++h;
        if(ht[rk[i]] = h) --h;
    } 
}
template<typename T>
void build(const T *str,int n){
    SuffixArray(str,n);
    getheight(n);
}
};

char s1[MAXN],s2[MAXN],s3[MAXN<<1];

void init(){
    scanf("%s",s1);
    scanf("%s",s2);
}

ll cal(char *a){
    #define pp pair<int,int>
    int n = strlen(a);
    a[n] = 'A'-1;
    static SA<401000> T;
    T.build(a,n);

    ll ans = 0,tmp = 0;
    stack<pp> S;
    for(int i = 1;i<=n;i++){
        ll cnt = 1,tot = 0;
        while(!S.empty() && S.top().first >= T.ht[i]){
            cnt += S.top().second,tot += 1LL * S.top().first * S.top().second;
            S.pop();
        }
        S.push(make_pair(T.ht[i],int(cnt)));
        
        tmp += T.ht[i]*cnt - tot;
        ans += tmp;
    }
    return ans;
}

void solve(){
    int n = strlen(s1),m = strlen(s2);
    memcpy(s3,s1,n),memcpy(s3+n+1,s2,m);s3[n] = 'A';
    printf("%lld\n",cal(s3)-cal(s1)-cal(s2));
}

signed main(){
    init();
    solve();
    return 0;
}