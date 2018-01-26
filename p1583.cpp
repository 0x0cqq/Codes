#include <cstdio>
#include <algorithm>
using namespace std;


int e[11];
struct person{
    int w;
    int id,d;
    void cal(){
        w += e[(d-1)%10+1];
    }
}p[40000];

bool cmp1(person a,person b){
    if(a.w!=b.w)
        return a.w>b.w;
    else
        return a.id < b.id;
}


int main(){
    int n,k;
    scanf("%d %d",&n,&k);
    for(int i = 1;i<=10;i++){
        scanf("%d",&(e[i]));
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&(p[i].w));
        p[i].id = i;
    }
    sort(p+1,p+n+1,cmp1);
    for(int i = 1;i<=n;i++){
        p[i].d = i;
        p[i].cal();
        //printf("%d:%d\n",i,p[i].sum);
    }
    sort(p+1,p+n+1,cmp1);
    for(int i = 1;i<=k;i++){
        printf("%d ",p[i].id);
    }
    printf("\n");
    return 0;
}