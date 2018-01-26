#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

int n,m;

int a[10010];

struct nnn{
    int a,b,c,d;
    long long cal(long long x){
        long long ans = a*x*x+b*x+c;
        return ans;
    }
}num[10100];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<n;i++){
        scanf("%d %d %d",&(num[i].a),&(num[i].b),&(num[i].c));
    }
    for(int i = 0;i<m;i++){
        a[i] = 0x3f3f3f3f;
    }
    for(int i = 0;i<n;i++){
        for(int x = 1;;x++){
            int t = num[i].cal(x);
            if(t>=a[0])
                break;
            else{
                pop_heap(a,a+m);
                a[m-1] = t;
                push_heap(a,a+m);
            }
        }
    }
    sort(a,a+m);
    for(int i = 0;i<m;i++){
        printf("%d ",a[i]);
    }
    putchar('\n');
    return 0;
}