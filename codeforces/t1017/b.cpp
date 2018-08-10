#include<cstdio>
using namespace std;

const int MAXN = 210000;

int n;
char a[MAXN],b[MAXN];

int num[5];

int main(){
    scanf("%d",&n);
    scanf("%s",a+1);
    scanf("%s",b+1);
    for(int i = 1;i<=n;i++){
        if(a[i] == '0' && b[i] == '0'){
            num[1]++;
        }
        else if(a[i] == '0' && b[i] == '1'){
            num[2]++;
        }
        else if(a[i] == '1' && b[i] == '0'){
            num[3]++;
        }
        else{
            num[4]++;
        }
    }
    long long ans = 0;
    ans += 1LL*num[1]*num[3];
    ans += 1LL*num[1]*num[4];
    ans += 1LL*num[2]*num[3];
    printf("%lld\n",ans);
    return 0;
}