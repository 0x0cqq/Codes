#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

bool cmp1(const int a,const int b){
    return (a%10000)>(b%10000);
}
bool cmp2(const int a,const int b){
    return (a/10000)<(b/10000);
}

struct Pair{
    int x1,y1,x2,y2;
    bool cut(int t,int a){
        if(a==1&&x1+x2==2*t+1||a==2&&y1+y2==2*t+1)
            return true;
        else
            return false;
    }
};

int cot(int k,int a,int num,Pair *di){
    int tot = 0;
    for(int i = 0;i<num;i++)
        if(di[i].cut(k,a))
            tot++;
    return tot;
}

int main(){
    int m,n,k,l,d;
    scanf("%d%d%d%d%d",&m,&n,&k,&l,&d);
    Pair p[d];
    int x[m],y[n];
    memset(x,0,m*4);memset(y,0,n*4);
    for(int i =0;i<d;i++){
        scanf("%d%d%d%d",&(p[i].x1),&(p[i].y1),&(p[i].x2),&(p[i].y2));
        int t,a;
    }
    for(int i = 0;i<m;i++)
        x[i]= (i)*10000+cot(i,1,d,p);
    for(int i = 0;i<n;i++)
        y[i]= (i)*10000+cot(i,2,d,p);
    sort(x,x+m,cmp1);sort(y,y+n,cmp1);
    sort(x,x+k,cmp2);sort(y,y+l,cmp2 );    
    for(int i = 0;i<k;i++)
        printf("%d ",x[i]/10000);
    printf("\n");
    for(int i = 0;i<l;i++)
        printf("%d ",y[i]/10000);
    printf("\n");
    return 0;
}