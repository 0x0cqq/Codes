#include <cstdio>
#include <vector>
#define int long long
using namespace std;

int n,k,s;
int now = 1;
vector<int> h;

bool hefa(int x){
    return x>=1 && x<=n;
}

signed main(){
    scanf("%lld %lld %lld",&n,&k,&s);
    int a = s/(n-1),b = s-a*(n-1);
    if(k > s || s > (n-1)*k){
        printf("NO\n");
        return 0;
    }
    while(b < k-a){
        a--;
        b = s-a*(n-1);
    }
    for(int i = 1;i<=a;i++){
        if(now == 1){
            h.push_back(n),now = n;
        }
        else if(now == n){
            h.push_back(1),now = 1;
        }
    }
    if(k-a != 0){
        if(now == 1){
            h.push_back(now+(1+b-(k-a)));
            now = now+(1+b-(k-a));
        }
        else if(now == n){
            h.push_back(now-(1+b-(k-a)));
            now = now-(1+b-(k-a));            
        }
        b = k-a - 1;
    }
    else{
        b = 0;
    }
    for(int i = 1;i<=b;i++){
        if(hefa(now-1)){
            h.push_back(now-1);
            now = now-1;
        }
        else if(hefa(now+1)){
            h.push_back(now+1);
            now = now+1;
        }
    }
    printf("YES\n");
    for(int i = 0;i<h.size();i++){
        printf("%lld ",h[i]);
    }
    return 0;
}