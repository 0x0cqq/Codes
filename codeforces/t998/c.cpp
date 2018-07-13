#include <cstdio>
#include <algorithm>
#define int long long
using namespace std;

const int MAXN = 400000;

int n,a,b;
char s[MAXN];

signed main(){
    scanf("%lld %lld %lld",&n,&a,&b);
    scanf("%s",s+1);
    s[0] = '1';
    int tmp = 0;
    for(int i = 1;i<=n;i++){
        if(s[i] == '0' && s[i-1] == '1')
            tmp++;
    }
    if(tmp == 0){
        printf("%d\n",0);
    }
    else
        printf("%lld\n",min((tmp-1)*a+b,tmp*b));
    //printf("%lld\n",tmp);
    return 0;
}