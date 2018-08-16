#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;

int t[500];

int main(){
    int a,b,c,d,sum,tot;
    scanf("%d",&n);
    scanf("%d %d %d %d",&a,&b,&c,&d);
    sum = a+b+c+d;
    for(int i = 2;i<=n;i++){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        tot = a+b+c+d;
        t[tot]++;
    }
    int ans = 0;
    for(int i = 400;i>sum;i--){
        ans += t[i];
    }
    printf("%d\n",ans+1);
    return 0;
}