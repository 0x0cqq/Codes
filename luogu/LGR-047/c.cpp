#include <cstdio>
#include <algorithm>
using namespace std;


#define pp pair<int,int>
int n;

const int MAXN = 210000;

pp q[MAXN];

int main(){
    scanf("%d",&n);
    int a,b;
    for(int i = 1;i<=n;i++){
        scanf("%d %d",&a,&b);
        if(b>a) swap(a,b);
        q[i].first = a,q[i].second = b;
    }
    sort(q+1,q+n+1);
    int ans = 0,t = 0;
    for(int i = 1;i<=n;i++){
        if(q[i].second > t)
            ans++,t = q[i].first;
    }
    printf("%d\n",(ans-1)/2+1);
    return 0;
}