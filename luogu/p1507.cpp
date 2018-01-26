#include <cstdio>
#include <algorithm>
using namespace std;

int dd[400][400][100],n,am,bm;

struct item{
    int a,b,c;
}t[100];

int dp(int lefta,int leftb,int nown){//nown未取
    if(lefta<0||leftb<0)
        return -0x3f3f3f3f;
    if((lefta == 0&&leftb == 0)||nown == n)
        return 0;
    if(dd[lefta][leftb][nown])
        return dd[lefta][leftb][nown];
    else{
        int res;
        res = max(t[nown].c+dp(lefta-t[nown].a,leftb-t[nown].b,nown+1),dp(lefta,leftb,nown+1));
        return dd[lefta][leftb][nown] = res;
    }
}

int main(){
    scanf("%d %d",&am,&bm);
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d %d %d",&t[i].a,&t[i].b,&t[i].c);
    }
    printf("%d\n",dp(am,bm,0));
    return 0;
}