#include <cstdio>
using namespace std;

long long ans = 0;
int res[20000][20000];

int cal(int a,int b){
    if(a<20000&&b<20000&&res[a][b])
        return res[a][b];
    int ans = 0;
    if(b-a>0)
        ans+=cal(b-a,a);
    ans++;
    ans%=1000000007;
    if(a<20000&&b<20000)
        res[a][b] = ans;
    return ans;
}


int n = 2;
int main(){
    //freopen("111.txt","w",stdout);
    for(int i = 1;i<n;i++){
        ans += cal(i,n-i);
        ans%=1000000007;
    }
    printf("%d,%5lld\n",n,ans);
    ans = 0;
    n++;
    }
    return 0;
}