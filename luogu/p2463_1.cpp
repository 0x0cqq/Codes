// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int INF=2e9;
int n;
int che[105];
struct rp{
    int num[105];
}m[1005];
inline bool operator < (rp a,rp b){
    return a.num[0]<b.num[0];
}
inline bool check3(int len,int x){
    for(register int i=1;i<=m[x].num[0]-len+1;++i){
        int ck=che[1]-m[x].num[i];
        bool fl=0;
        for(register int j=2;j<=len;++j){
            if(che[j]-m[x].num[i+j-1]!=ck){
                fl=1;
                break;
            }
        }
        if(!fl) return 1;
    }
    return 0;
}
inline bool check2(int len){
    for(register int i=2;i<=n;++i){
        if(!check3(len,i)) 
          return 0;
    }
    return 1;
}
inline bool check(int len){
    for(register int i=1;i<=m[1].num[0]-len+1;++i){
        for(register int j=1;j<=len;++j){
            che[j]=m[1].num[i+j-1];
        }
        if(check2(len)) return 1;
    }
    return 0;
}
char ss[1<<17],*A=ss,*B=ss;
inline char gc()
{if(A==B){B=(A=ss)+fread(ss,1,1<<17,stdin);if(A==B)return EOF;}return*A++;}
template<class T>inline void read(T&x){
    char c;int y=1;while(c=gc(),c<48||57<c)if(c=='-')y=-1;x=c^48;
    while(c=gc(),47<c&&c<58)x=(x<<1)+(x<<3)+(c^48);x*=y;
}
inline void print(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int main(){
    read(n);
    m[0].num[0]=INF;
    for(register int i=1;i<=n;++i){
        read(m[i].num[0]);
        for(register int j=1;j<=m[i].num[0];++j){
            read(m[i].num[j]);
        }
    }
    sort(m+1,m+n+1);
    m[0].num[0]=m[1].num[0];
    int l=1,r=m[0].num[0];
    while(l<r){
        int mid=(l+r+1)>>1;
        if(check(mid)) l=mid;
        else r=mid-1;
    }
    printf("%d\n",l);
    return 0;
}