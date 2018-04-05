#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 110000;

int num[MAXN];
int n,m,ans;
int s[MAXN];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++)
        scanf("%d",&num[i]);
    for(int i = 1;i<=n;i++)
        scanf("%d",&s[i]);
    for(int i = 1;i<=n;i++)
        if(s[i]) ans+=num[i];
    int maxtmp = 0;
    int tmp = 0;
    for(int i = 1;i<=m;i++)
        if(s[i] == 0) tmp+=num[i];
    maxtmp = tmp;
    for(int b = 1,e = m;e<=n;){
        //printf("%d %d %d\n",b,e,tmp);
        if(s[b] == 0) tmp -= num[b];b++;
        if(s[++e] == 0) tmp += num[e];
        maxtmp = max(maxtmp,tmp);
    }
    printf("%d\n",ans+maxtmp);
    return 0;
}