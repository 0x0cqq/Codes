#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 200;
typedef long long ll;

#define mod 45989

int n,m,t,A,B;
struct Edge{
    int to,nex;
}edge[MAXN];
int fir[MAXN],ecnt = 2;

inline void addedge(int u,int v){
    edge[ecnt] = (Edge){v,fir[u]};
    fir[u] = ecnt++;
}

struct Matrix{
    ll a[MAXN][MAXN];
    Matrix(){
        memset(a,0,sizeof(a));
    }
};

inline Matrix mul(const Matrix &_a,const Matrix &_b){
    Matrix tmp;
    for(int i = 1;i<=2*m;i++){
        for(int j = 1;j<=2*m;j++){
            for(int k = 1;k<=2*m;k++){
                tmp.a[i][j] += _a.a[i][k] * _b.a[k][j]; 
            }
            if(tmp.a[i][j] >= mod) tmp.a[i][j] %= mod;
        }
    }
    return tmp;
}

inline Matrix pow(Matrix x,int k){
    Matrix ans;
    for(int i = 1;i<=2*m;i++) ans.a[i][i] = 1;
    for(int i = k;i;i>>=1,x = mul(x,x)){
        if(i&1) ans = mul(ans,x);
    }
    return ans;
}

inline void init(){
    scanf("%d %d %d %d %d",&n,&m,&t,&A,&B);
    A++,B++; 
    int u,v;
    for(int i = 1;i<=m;i++){
        scanf("%d %d",&u,&v);
        u++,v++;
        addedge(u,v);
        addedge(v,u);
    }
    m++;
    edge[2*m] = (Edge){A,fir[0]};
    fir[0] = 1;
}

void solve(){
    Matrix M,I;
    for(int e = 2;e<=2*m;e++){
        int x = edge[e].to;
        if(x == B) I.a[e][1] = 1;
        for(int nowe = fir[x];nowe;nowe = edge[nowe].nex){
            if((e^1)==nowe) continue;
            M.a[e][nowe] = 1;
        }
    }
    M = pow(M,t);
    static ll ans[MAXN];
    for(int i = 1;i<=2*m;i++){
        for(int j = 1;j<=2*m;j++){
            ans[i] += M.a[i][j] * I.a[j][1];
        }
    }
    
    // for(int i = 2;i<=2*m;i++){
    //     printf("%d:%d\n",i,ans[i]);
    // }
    printf("%lld\n",ans[2*m] % mod);
}

int main(){
    init();
    solve();
    return 0;
}