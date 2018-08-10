#include <cstdio>
#include <cstring>
#include <queue>
#define mod 10007
#define sigma_size 26
using namespace std;

const int MAXN = 7000,MAXM = 110;


int c[MAXN][sigma_size],f[MAXN],is_end[MAXN];
int root,cnt;
void insert(char *str){
    int n = strlen(str),nown = root;
    for(int i = 0;i<n;i++){
        if(!c[nown][str[i]-'A']) 
            c[nown][str[i]-'A'] = ++cnt;
        nown = c[nown][str[i]-'A'];;
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

int n,m;
char ch[MAXN];

void init(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%s",ch);
        insert(ch);
    }
    get_fail();
}

void solve(){
    static int dp[MAXN][MAXM];
    for(int i = 0;i<=cnt;i++){
        if(!is_end[i]) dp[i][0] = 1;
    }
    for(int j = 1;j<=m;j++){
        // printf("%d:\n",j);
        for(int i = 0;i<=cnt;i++){
            if(!is_end[i]){
                for(int k = 0;k<sigma_size;k++){
                    dp[i][j] += dp[c[i][k]][j-1];
                }
                // printf("    %d:%lld\n",i,dp[i][j]);
                dp[i][j] %= mod;
            }
        }
    }
    int ans = 1;
    for(int i = 1;i<=m;i++){
        ans *= sigma_size;
        ans %= mod;
    }
    printf("%d\n",(ans-dp[0][m]+mod)%mod);
}


int main(){
    init();
    solve();
    return 0;
}