#include<cstdio>
using namespace std;

const int Maxn=2011;
struct T{
    int llx,lly;
    int rrx,rry;
}ju[Maxn];
int n,m,x,y,ans = 0,pos;

int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%d%d%d%d",&ju[i].llx,&ju[i].lly,&ju[i].rrx,&ju[i].rry);
    }
    for (int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        ans = 0;
        for (int j=1;j<=n;j++){
            if (x>=ju[j].llx && x<=ju[j].rrx && y>=ju[j].lly && y<=ju[j].rry){
                ans++;
                pos=j;
            }
        }
        if (ans==0)
            printf("NO\n");
        else
            printf("YES %d %d\n",ans,pos);
    }
    return 0;
}