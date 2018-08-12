#include <cstdio>
using namespace std;


const int MAXN = 1100000;

int n;
char s[MAXN];
int nex[MAXN],near[MAXN];

void solve(){
    int j;j = nex[0] = 0;
    for(int i = 1;i<n;i++){
        while(j > 0 && s[i] != s[j])
            j = nex[j-1];
        if(s[i]==s[j]) j++;
        nex[i] = j;
    }
    j = 0;
    long long ans = 0;
    near[0] = 0;
    for(int i = 1;i<n;i++){
        int w = nex[i] - 1;
        if(w >= 0)
            near[i] = near[w] == -1?w:near[w];
        else
            near[i] = -1;
        j = near[i]+1;
        if(j > 0 && j <= (i+1)/2)
            ans += (i+1)-j;
        // printf("i:%d j:%d\n",i,j);
    }
    printf("%lld\n",ans);
}

void init(){
    scanf("%d",&n);
    scanf("%s",s);
}

int main(){
    init();
    solve();
    return 0;
}
