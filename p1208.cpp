#include <cstdio>
#include <algorithm>
using namespace std;

struct nc{
    int p,n;
    bool operator < (const nc &b)const{
        return p<b.p;
    }
    int cal(){
        return p*n;
    }
}nainiu[10000];

int main(){
    int m,k,ans = 0;
    scanf("%d %d",&m,&k);
    for(int i = 0;i<k;i++){
        int a,b;
        scanf("%d %d",&(nainiu[i].p),&(nainiu[i].n));
    }
    sort(nainiu,nainiu+k);
    for(int i =0;i<k;i++){
        if(m-nainiu[i].n>0){
            m-=nainiu[i].n;
            ans+=nainiu[i].cal();
        }else{
            ans+=m*nainiu[i].p;
            break;
        }
    }
    printf("%d\n",ans);
    return 0;
}