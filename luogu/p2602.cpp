#include <cstdio>
using namespace std;
#define ll long long 

ll a,b;

const int MAXN = 20;

struct sum{
    ll num[10];
    sum(int pos = -1,ll d = 1){
        for(int i = 0;i<10;i++) num[i] = 0;
        if(~pos)
            num[pos] = d;
    }
    sum operator +(const sum a)const{
        sum ans = sum();
        for(int i = 0;i<=9;i++)
            ans.num[i] = this->num[i] + a.num[i];
        return ans;
    }
    sum operator *(const int a)const{
        sum ans = sum();
        for(int i = 0;i<=9;i++)
            ans.num[i] = this->num[i] * a;
        return ans;
    }
    sum operator -(const sum a)const{
        sum ans = sum();
        for(int i = 0;i<=9;i++)
            ans.num[i] = this->num[i] - a.num[i];
        return ans;
    }
};

sum dp[MAXN][MAXN];
ll t[MAXN];
//dp[i][j] -> 后i位，倒数第i位为j,j == 10 代表为先导0

void init(){
    scanf("%lld %lld",&a,&b);
    t[0] = 1;
    for(int i = 1;i<=15;i++)
        t[i] = 10*t[i-1];
}

void build(){
    for(int j = 0;j<=9;j++)
        dp[1][j] = sum(j,1); 
    for(int i = 2;i<=15;i++){
        for(int j = 0;j<=9;j++){
            dp[i][j] = sum(j,t[i-1]);
            for(int w = 0;w<=9;w++)
                dp[i][j] = dp[i][j] + dp[i-1][w];
        }
        dp[i][10] = sum();
        for(int w = 1;w<=10;w++)
            dp[i][10] = dp[i][10] + dp[i-1][w]; 
    }
    // for(int i = 1;i<=15;i++){
    //     printf("%d\n",i);
    //     for(int j = 0;j<=10;j++){
    //         printf("    %d: ",j);
    //         for(int w = 0;w<=9;w++){
    //             printf("%lld ",dp[i][j].num[w]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
}

sum getnum(ll a){
    ll tmp = a;
    // printf("solve:%lld\n",a);
    sum ans = sum(0,1);
    if(a == 0){
        return sum(0,1);
    }
    int num[15],cnt = 0;
    while(a){
        num[++cnt] = a % 10;
        a/=10;
    }
    // for(int i = cnt;i>=1;--i){
    //     printf("%d:%d\n",i,num[i]);
    // }
    ans = ans + dp[cnt][10] - dp[cnt][0];
    for(int i = cnt;i>=1;--i){
        for(int j = 0;j<num[i];++j){
            ans = ans + dp[i][j];
        }
        ans = ans + sum(num[i],tmp%t[i-1]+1);
        // printf("%d:\n",i);
        // for(int i = 0;i<=9;i++)
        //     printf("%lld ",ans.num[i]);
        // printf("\n");
    }
    // for(int i = 0;i<=9;i++){
    //     printf("%lld ",ans.num[i]);
    // }    
    // printf("\n");
    return ans;
}

void solve(){
    sum ans = getnum(b)-getnum(a-1);
    for(int i = 0;i<=9;i++){
        printf("%lld ",ans.num[i]);
    }
    printf("\n");
}

int main(){
    init();
    build();
    solve();
    return 0;
}