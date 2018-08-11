#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 510000,logn = 20;

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
    for(int i = 0;i<n;i++) rk[int(str[i])] = 1;//=1!
    for(int j = 0;j<m;j++) rk[j+1] += rk[j]; 
    for(int i = 0;i<n;i++) s[i] = rk[int(str[i])]-1;
    return rk[m];
}
void getHeight(int n){
    for(int i = 0;i<n;i++)rk[sa[i]] = i;
    for(int i = 0,h = ht[0] = 0;i<n;i++){
        int j = sa[rk[i]-1];
        while(i+h<n && j+h<n && s[i+h] == s[j+h]) h++;
        if(ht[rk[i]] = h) --h;
    }
}
// str[n] yange zidianxu zuixiao
template <typename T>
void build(int n,const T *str){
    int m = mapChartoInt(++n,str);
    sais(n,m,s,t,p);
    getHeight(n);
}
}

namespace ST{
int minn[MAXN][logn];
void build(int n,int *num){
    int l = log2(n);
    for(int i = 0;i<=n;i++)
        minn[i][0] = num[i];
    for(int j = 1;j<=l;j++){
        for(int i = 0;i+(1<<(j-1))<=n;i++){
            minn[i][j] = min(minn[i+(1<<(j-1))][j-1],minn[i][j-1]); 
        }
    }
}
int query(int l,int r){
    int t = log2(r-l+1);
    return min(minn[l][t],minn[r-(1<<t)+1][t]);
}
}

int n,q;

int lcp(int a,int b){
    if(a == b) return n-a+1;
    a = SA::rk[a],b = SA::rk[b];
    if(a > b) swap(a,b);
    // printf("a:%d b:%d\n",a,b);
    return ST::query(a+1,b);
}



char s[MAXN];

int r[MAXN];

void init(){
    scanf("%s",s);
    n = strlen(s);
    reverse(s,s+n);
    s[n] = 'a' - 1;
    SA::build(n,s);
    ST::build(n+1,SA::ht);
}

void build(){
    //[0,i),[i,2*i),[2*i+i-1)
    for(int i = 1;2*i<n;i++){
        if(lcp(0,i) < i) continue;
        else{
            // printf("i:%d\n",i);
            int t = lcp(0,2*i);
            // printf("    t:%d\n",t);
            if(t == 0) continue;
            r[2*i]++,r[min(2*i+t,2*i+i-1)]--;
        }
    }
    for(int i = 1;i<n;i++){
        r[i] += r[i-1];
    }
}

void solve(){
    int q,t;
    // for(int i = 0;i<n;i++)
    //     printf("%d:%d\n",i,r[i]);
    
    scanf("%d",&q);

    for(int i = 1;i<=q;i++){
        scanf("%d",&t);
        t = n-t;
        if(r[t]){
            printf("niconiconi\n");
        }
        else{
            printf("no\n");
        }
    }
}

int main(){
    init();
    build();
    solve();
    return 0;
}