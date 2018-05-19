#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long

int main(){
    int n;
    scanf("%d",&n);
    ll ans = 0,tmp = 0;
    for(int i = 1;i<=n;i++){
        scanf("%lld",&tmp);
        ans+=tmp;
    }
    if(ans&1)
        printf("Alice\n");
    else
        printf("Bob\n");
    return 0;
}