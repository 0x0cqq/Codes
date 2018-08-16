#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 210000;

namespace BCJ{
    int f[MAXN<<2];
    void init(int n){
        for(int i =1;i<=n;i++) f[i] = i;
    }
    int find(int x){
        return f[x] == x?x:f[x] = find(f[x]);
    }
    int un(int x,int y){
        int fx = find(x),fy = find(y);
        if(fx == fy) return 0;
        f[fx] = fy;
        return 1;
    }
}

int n,m,q;


int main(){
    scanf("%d %d %d",&n,&m,&q);
    int ans = n+m;
    BCJ::init(n+m);
    for(int i = 1;i<=q;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        ans -= BCJ::un(x,y+n);
    }
    printf("%d\n",ans-1);
    return 0;
}
