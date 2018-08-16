#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1100000;

int n;
char str[MAXN];
int a[MAXN],sum[MAXN];
int minsum = 0;
int fir[MAXN],nex[MAXN],to[MAXN];
// fir仅做建图方便用，nex表示下一个sum相同的位置
// to表示区间最远能够延伸的距离

void init(){
    scanf("%d",&n);
    scanf("%s",str + 1);
    memset(fir,-1,sizeof(fir));
    for(int i = 1;i<=n;i++){
        a[i] = str[i] == 'p' ? 1 : -1;
        sum[i] = sum[i-1] + a[i];
        minsum = min(sum[i],minsum);
    }
    for(int i = n;~i;--i){
        int x = sum[i] - minsum;
        nex[i] = fir[x],to[i] = i,fir[x] = i;
    }
}

void solve(){
    static int ans = 0;
    int r = n;
    for(int l = n;l>=1;--l){
        if(a[l] == -1){
            r = l-1;
        }
        else{
            int t = nex[l-1];
            if(~t && sum[to[t]] >= sum[r])
                r = to[t];
            to[l-1] = r;
            ans = max(ans,r-l+1);
        }
    }
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}
