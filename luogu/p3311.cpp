#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define mod 1000000007
#define ll long long
using namespace std;
#define sigma_size 10

const int MAXN = 1600;

struct AC_automaton{
    int c[MAXN][sigma_size],f[MAXN],is_end[MAXN];
    int root,cnt;
    AC_automaton(){root=cnt=0;}
    void insert(char *str){
        int n = strlen(str),nown = root;
        for(int i = 0;i<n;i++){
            if(!c[nown][str[i]-'0'])
                c[nown][str[i]-'0'] = ++cnt;
            nown = c[nown][str[i]-'0'];
        }
        is_end[nown] |= 1;
    }
    void get_fail(){
        queue<int> q;
        while(!q.empty()) q.pop();
        for(int i = 0;i<sigma_size;i++){
            if(c[root][i]){
                f[c[root][i]] = root;
                q.push(c[root][i]);
            }
        }
        while(!q.empty()){
            int nown = q.front();q.pop();
            for(int i = 0;i<sigma_size;i++){
                if(c[nown][i]){
                    f[c[nown][i]] = c[f[nown]][i];
                    is_end[c[nown][i]] |= is_end[f[c[nown][i]]];
                    q.push(c[nown][i]);
                }
                else c[nown][i] = c[f[nown]][i];
            }
        }
    }
}AC;

int n,m;
char s[MAXN],t[MAXN];
ll dp[MAXN][MAXN][3];

void init(){
    scanf("%s",s);
    n = strlen(s);
    scanf("%d",&m);
    for(int i = 1;i<=m;i++){
        scanf("%s",t);
        AC.insert(t);
    }
    AC.get_fail();
}

void solve(){
    for(int i = 0;i<=AC.cnt;i++){
        if(!AC.is_end[i]) 
            dp[i][0][0] = dp[i][0][1] = dp[i][0][2] = 1;
        //printf("    i:%d dp:%lld %lld\n",i,dp[i][0][0],dp[i][0][1]);
    }
    for(int j = 1;j<=n;j++){
        //printf("j:%d\n",j);
        for(int i = 0;i<=AC.cnt;i++){
            if(!AC.is_end[i]){
                for(int k = 0;k<10;k++){
                    dp[i][j][0] += dp[AC.c[i][k]][j-1][0];
                }
                int t = s[n-j]-48;
                for(int k = 0;k<t;k++){
                    dp[i][j][1] += dp[AC.c[i][k]][j-1][0];
                }
                dp[i][j][1] += dp[AC.c[i][t]][j-1][1];
                dp[i][j][2] = dp[i][j][0] - dp[AC.c[i][0]][j-1][0];
                dp[i][j][0] %= mod,dp[i][j][1] %= mod,dp[i][j][2] %= mod;
            }
            // printf("    i:%d dp:%lld %lld %lld\n",i,dp[i][j][0],dp[i][j][1],dp[i][j][2]);
        }
    }
    ll ans = dp[0][n][1];
    int nown = 0;
    for(int i = 1;i<=n;i++){
        nown = AC.c[nown][0];
        ans -= dp[nown][n-i][2];
        // printf("ans:%lld\n",ans);
    }
    for(int i = 1;i<n;i++){
        ans += dp[0][n-i][2];
    }
    ans = (ans%mod+mod)%mod;
    printf("%lld\n",ans);
}


int main(){
    init();
    solve();
    return 0;
}
