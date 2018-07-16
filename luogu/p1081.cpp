#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
#define maxn 18
typedef set<int>::iterator si;

const int MAXN = 210000;

struct pos{
    int id,h;
}p[MAXN];

struct Point{
    int p,h,dis;
    Point(int _p,int _h,int _d){p = _p,h = _h,dis = _d;}
    Point(){};
    bool operator < (const Point c){
        if(c.dis != dis) return dis < c.dis;
        else return h < c.h;
    }
};

int n,m,to[MAXN],back[MAXN];
bool cmp1(pos a,pos b){return a.h < b.h;}
bool cmp2(pos a,pos b){return a.id < b.id;}

int a[MAXN],b[MAXN],h[MAXN];

void init(){
    scanf("%lld",&n);
    for(int i = 1;i<=n;i++){
        int t;scanf("%lld",&t);
        p[i] = (pos){i,t};
        h[i] = t;
    }
    sort(p+1,p+n+1,cmp1);
    for(int i = 1;i<=n;i++){
        to[i] = p[i].id;
        back[p[i].id] = i;
    }
    sort(p+1,p+n+1,cmp2);
}

void build1(){
    static int l[MAXN],r[MAXN];
    for(int i = 1;i<=n;i++){
        l[i] = to[back[i]-1],r[i] = to[back[i]+1];
        //printf("l:%d r:%d\n", l[i],r[i]);
    }
    for(int i = 1;i<=n;i++){
        vector<Point> v;
        int t = i;
        //printf("%d:\n",i);
        if((t = l[t])!=0) v.push_back(Point(t,h[t],abs(h[t] - h[i])));
        if((t = l[t])!=0) v.push_back(Point(t,h[t],abs(h[t] - h[i])));
        t = i;
        if((t = r[t])!=0) v.push_back(Point(t,h[t],abs(h[t] - h[i])));
        if((t = r[t])!=0) v.push_back(Point(t,h[t],abs(h[t] - h[i])));
        sort(v.begin(),v.end());
        // for(auto i:v){
        //     printf("    p:%d h:%d d:%d\n",i.p,i.h,i.dis);
        // }
        if(v.size() > 1) a[i] = v[1].p;
        if(v.size() > 0) b[i] = v[0].p;
        r[l[i]] = r[i],l[r[i]] = l[i];
        l[0] = r[0] = 0;
    }
}

int f[MAXN][20];
ll A[MAXN][20];
ll B[MAXN][20];

void cal(int pos,ll x,ll &ansa,ll &ansb){
    ansa = ansb = 0;
    for(int j = maxn;~j;--j){
        if(f[pos][j] && x >= A[pos][j] + B[pos][j]){
            ansa += A[pos][j];
            ansb += B[pos][j];
            x -= A[pos][j] + B[pos][j];
            pos = f[pos][j];
        }
    }
    if(a[pos] && x >= A[pos][0]) ansa += A[pos][0];
}

void build2(){
    // for(int i = 1;i<=n;i++){
    //     printf("a:%d b:%d\n",a[i],b[i]);
    // }
    for(int i = 1;i<=n;i++){
        f[i][0] = b[a[i]];
        A[i][0] = abs(h[a[i]]-h[i]);
        B[i][0] = abs(h[b[a[i]]] - h[a[i]]);
        //printf("%d 0:%d %d %d\n",i,f[i][0],A[i][0],B[i][0]);
    }
    for(int j = 1;j<=maxn;j++)
        for(int i = 1;i<=n;i++){
            //qwq;
            f[i][j] = f[f[i][j-1]][j-1];
            A[i][j] = A[f[i][j-1]][j-1] + A[i][j-1];
            B[i][j] = B[f[i][j-1]][j-1] + B[i][j-1];
            // printf("%d %d:%d %d %d\n",i,j,f[i][j],A[i][j],B[i][j]);
        }
}

void solve1(){
    ll x0;
    scanf("%lld",&x0);
    int minp = to[n];double mind = 1e20;
    for(int i = 1;i<=n;i++){
        ll x,y;
        cal(i,x0,x,y);
        // printf("%d:%d %d\n",i,x,y);
        if(y == 0){
            if(mind > 1e15 || (mind == 1e15 && h[i] > h[minp])){
                mind = 1e15;
                minp = i;
            }
        }
        else if(double(x)/y < mind || (double(x)/y == mind && h[i] > h[minp])){
            mind = double(x)/y;
            minp = i;
        }
    }
    printf("%lld\n",minp);
}

void solve2(){
    int m,s;ll x;
    scanf("%lld",&m);
    for(int i = 1;i<=m;i++){
        scanf("%lld %lld",&s,&x);
        ll ansa,ansb;
        cal(s,x,ansa,ansb);
        printf("%lld %lld\n",ansa,ansb);
    }
}

signed main(){
    init();
    build1();
    build2();
    solve1();
    solve2();
    return 0;
}