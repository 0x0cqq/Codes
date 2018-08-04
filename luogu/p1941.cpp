#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 10100,MAXM = 1100;

inline int min(int a,int b){
    return a < b ? a : b;
}

int n,m,k;
int x[MAXN],y[MAXN];
bool vis[MAXN][MAXM];
struct tune{
    int p,l,h;
    bool operator <(const tune &a)const{return p < a.p;}
}t[MAXN];

void init(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i = 1;i<=n;i++)
        scanf("%d %d",&x[i],&y[i]);
    for(int i = 1;i<=k;i++)
        scanf("%d %d %d",&t[i].p,&t[i].l,&t[i].h);
}

void prepare(){
    sort(t+1,t+k+1);
    for(int i = 1;i<=k;i++){
        for(int j = 0;j<=t[i].l;j++)
            vis[t[i].p][j] = 1;
        for(int j = t[i].h;j <= m;j++)
            vis[t[i].p][j] = 1;
    }
}


void solve(){
    static int minn[MAXM],tmp[MAXM];
    int nowp = 0;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++)
            tmp[j] = 0x3f3f3f3f;
        for(int pos = 1;pos<=m;pos++){
            if(pos-x[i] > 0)
                tmp[pos] = min(tmp[pos],1 + min(tmp[pos-x[i]],minn[pos-x[i]]));
            tmp[m] = min(tmp[m],(m-pos)/x[i] + 1 + minn[pos]);
        }
        for(int pos = 1;pos<=m;pos++)
            if(pos+y[i] <= m) 
                tmp[pos] = min(tmp[pos],minn[pos+y[i]]);
        int cnt = 0;
        for(int j = m;j>=1;j--){
            if(vis[i][j]) tmp[j] = 0x3f3f3f3f;
            minn[j] = tmp[j];
            if(minn[j] != 0x3f3f3f3f) cnt = 1;
        }
        if(cnt == 0) break;
        if(nowp < k && i >= t[nowp+1].p) nowp++;
    }
    if(nowp == k){
        int minx = 0x3f3f3f3f;
        for(int i = 1;i<=m;i++)
            minx = min(minx,minn[i]);
        printf("%d\n%d\n",1,minx);
    }
    else{
        printf("%d\n%d\n",0,nowp);
    }
}

int main(){
    //file();
    init();
    prepare();
    solve();
    return 0;
}