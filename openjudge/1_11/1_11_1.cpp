#include <cstdio>
using namespace std;

int w[100000];
int main(){
    int m,n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
        scanf("%d",&(w[i]));
    scanf("%d",&m);
    while(m--){
        int tem,b = 0,e = n-1,r;    
        scanf("%d",&(tem));
        while(e>b+1){
            int t = (b+e)>>1;
            tem>=w[t]?b = t:e = t;
        }
        tem-w[b]>w[e]-tem?r = w[e]:r = w[b];
        printf("%d\n",r);
    }
    return 0;
}
