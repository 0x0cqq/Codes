#include <cstdio>
#include <algorithm>
using namespace std;

int d,g,dd[200][200][1100];

struct Laji{
    int t,f,h;
    Laji(){

    }
    Laji(int a,int b,int c){
        t = a;f = b;h = c;
    }
}l[200];

bool cmp(Laji a,Laji b){
    return a.t<b.t;
}

int dp(int nown,int h,int t){
    if(dd[nown][h][t]!=0)
        return dd[nown][h][t];
    //printf("b: nown:%d h:%d t:%d\n",nown,h,t);
    int res;
    if(h>=d)
        res = l[nown-1].t-100000000;
    else if(t<0)
        res = -(l[nown].t+t);
    else if(nown == g+1)
        res = -(l[nown].t+t);
    else{
        res = min(dp(nown+1,h+l[nown].h,t+l[nown].t-l[nown+1].t),dp(nown+1,h,t+l[nown].f+l[nown].t-l[nown+1].t));
    }
    //printf("e: nown:%d h:%d t:%d res:%d\n",nown,h,t,res);
    return dd[nown][h][t] = res;
}

int main(){
    scanf("%d %d",&d,&g);
    for(int i = 1;i<=g;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        l[i] = Laji(a,b,c);
    }
    l[0] = Laji(0,0,0);
    sort(l,l+g+1,cmp);
    l[g+1] = l[g];
    int ans = dp(0,0,10);
    if(ans<=-1000000)
        printf("%d",ans+100000000);
    else{
        printf("%d",-ans);
    }
    return 0;
}