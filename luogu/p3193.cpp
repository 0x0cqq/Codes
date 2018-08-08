#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXM = 30;

int n,m,k;
char s[MAXM];
int nex[MAXM];


struct Matrix{
    int a[MAXM][MAXM];
    Matrix(){memset(a,0,sizeof(a));}
};

Matrix mul(Matrix &_a,Matrix &_b){
    Matrix ans;
    for(int i = 0;i<=m;i++){
        for(int j = 0;j<=m;j++){
            for(int k = 0;k<=m;k++){
                ans.a[i][j] += _a.a[i][k] * _b.a[k][j];
            }
            if(ans.a[i][j] >= k) ans.a[i][j] %= k;
        }
    }
    return ans;
}

Matrix pow(Matrix x,int k){
    Matrix ans;
    for(int i = 0;i<=m;i++) ans.a[i][i] = 1;
    for(int i = k;i;i>>=1,x = mul(x,x)) if(i & 1) ans = mul(ans,x);
    return ans;
}

void init(){
    scanf("%d %d %d",&n,&m,&k);
    scanf("%s",s);
}

//dp[i][j]表示已经匹配了i位，模版已经匹配了j位

void get_next(){
    nex[0] = 0;
    int j = 0;
    for(int i = 1;i<m;i++){
        while(j > 0 && s[i] != s[j]) 
            j = nex[j-1];
        if(s[i] == s[j]) j++;
        nex[i] = j;
    }
    // printf("next:\n");
    // for(int i = 0;i<m;i++)
    //     printf("%d ",nex[i]);
    // printf("\n");
}



void solve(){
    get_next();
    Matrix tmp;
    for(int i = 0;i<m;i++){
        int t = i;
        for(int w = '0';w<='9';w++){
            t = i;
            while(t > 0 && s[t] != w)
                t = nex[t-1];
            if(s[t] == w) t++;
            tmp.a[t][i]++;
        }
    }
    // for(int i = 0;i<m;i++){
    //     for(int j = 0;j<m;j++){
    //         printf("%d ",tmp.a[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    tmp = pow(tmp,n);
    // for(int i = 0;i<m;i++){
    //     for(int j = 0;j<m;j++){
    //         printf("%d ",tmp.a[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    int ans = 0;
    for(int i = 0;i<m;i++){
        ans += tmp.a[i][0];
    }
    ans %= k;
    printf("%d\n",ans);
}

int main(){
    init();
    solve();
    return 0;
}