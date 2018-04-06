#include <cstdio>
#include <unistd.h>
#include <cstring>
#define ll long long
using namespace std;

const int MAXN = 1110000;

int n,p = 1000000007;
ll nex[MAXN],num[MAXN],cnt[MAXN];
char s[MAXN];
inline void m(ll &x){x%=p;}

void cal(){
    memset(nex,0,sizeof(nex));
    memset(num,0,sizeof(num));
    memset(cnt,0,sizeof(cnt));
    nex[0] = 0;
    int len = strlen(s);
    int j = 0;
    for(int i = 1;i<len;i++){
        //printf("%d\n",i);
        while(j > 0 && s[i]!=s[j])
            j = nex[j-1];
        if(s[i] == s[j]) ++j;
        nex[i] = j;
        m(cnt[i] = cnt[nex[i-1]]+1);
    }
    for(int i = 1;i<len;i++){
        j = nex[i];
        while(j>0 && 2*j > i+1){
            j = nex[j-1];
        }
        //printf("%d %d\n",i,j);
        num[i] = cnt[j];
        //num[i] = 0;
        //while(j){
        //    j = nex[j-1];
        //    num[i]++;
        //}
    }
    ll ans = 1;
    for(int i = 0;i<len;i++){
        //printf("%c%d: nex:%lld num:%lld cnt:%lld\n",s[i],i,nex[i],num[i],cnt[i]);
        m(ans*=(num[i]+1));
    }
    printf("%lld\n",ans);
}

void solve(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%s",s);
        cal();
    }
}

int main(){
    solve();
    return 0;
}