#include<cstdio>
#include<algorithm>
#include<cstring>
#define rint register int
using namespace std;
const int N=6e5+5;
int f[N],key[N],root[N],c[N][2],id[N];
int n,m,s[N],w[N],NodeCnt;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0' || ch>'9'){if (ch=='-')f=-1;ch=getchar();}
    while ('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
inline int find(int x){
    return f[x]==x?x:f[x]=find(f[x]);
}
inline void rotate(int &t,int p){
    rint k=c[t][!p];
    c[t][!p]=c[k][p];
    c[k][p]=t;
    s[k]=s[t];
    s[t]=s[c[t][0]]+s[c[t][1]]+1;
    t=k;
}
inline void maintain(int &t,int p){
    if (s[c[c[t][p]][p]]>s[c[t][!p]])
        rotate(t,!p);else
    if (s[c[c[t][p]][!p]]>s[c[t][!p]])
        rotate(c[t][p],p),rotate(t,!p);
    else return;
    maintain(c[t][0],0);
    maintain(c[t][1],1);
    maintain(t,0);
    maintain(t,1);
}
inline void insert(int &t,int u,int idx){
    if (!t){
        key[t=++NodeCnt]=u;id[t]=idx,s[t]=1;
        return;
    }
    ++s[t];
    if (u<key[t])insert(c[t][0],u,idx);
        else insert(c[t][1],u,idx);
    maintain(t,u>=key[t]);
}
inline int select(int &t,int k){
    rint lc=c[t][0];
    if (s[lc]+1==k)return id[t];
    if (s[lc]+1<k)return select(c[t][1],k-s[lc]-1);
        else return select(c[t][0],k);
}    
inline void dfs(int &p,int &q){
    if (!p)return;
    f[id[p]]=id[q];
    insert(q,key[p],id[p]);
    dfs(c[p][0],q);
    dfs(c[p][1],q);
}
inline void merge(int &p,int &q){
    if (s[p]>s[q])swap(p,q);
    dfs(p,q);
    p=q;
}
int main(){
    n=read(),m=read();
    for (rint i=1;i<=n;++i)
        w[i]=read();
    for (rint i=1;i<=n;++i)
        f[i]=i;
    for (rint i=1;i<=m;++i){
        rint u=read(),v=read();
        rint p=find(u),q=find(v);
        f[q]=p;
    }
    for (rint i=1;i<=n;++i)
        insert(root[f[i]=find(i)],w[i],i);
    rint T=read();
    char op[5];
    for (rint i=1;i<=T;++i){
        scanf("%s",op);
        if (op[0]=='Q'){
            rint u=read(),k=read();
            rint p=root[find(u)];
            printf("%d\n",s[p]>=k?select(p,k):-1);
        }else{
            rint u=read(),v=read();
            rint &p=root[find(u)],&q=root[find(v)];
            if (p!=q) merge(p,q);
        }
    }
    return 0;
}