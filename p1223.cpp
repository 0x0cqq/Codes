#include <cstdio>
#include <algorithm>
using namespace std;

struct p{
    int id;
    double water;
    bool operator < (const p &c)const{
        return water < c.water;
    }
}k[10000];

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%lf",&(k[i].water));
        k[i].id = i;
    }
    sort(k,k+n);
    long double ans = 0;
    for(int i = 0;i<n;i++){
        ans += k[i].water*(n-i-1);
        printf("%d ",k[i].id+1);
    }
    printf("\n%.2Lf\n",(ans/n));
    return 0;
}