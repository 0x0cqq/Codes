#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define pp pair<int,int>
using namespace std;



int d[2010],ans[2010],n,m;
bool v[2010];
queue<int> q;

int r[2010][2010]; 



void spfa(){
    memset(d,0x1f,sizeof(d));
    d[1] = 0,ans[1] = 1;q.push(1);
    while(!q.empty()){
        int nown = q.front();
        //printf("%d\n",nown);
        q.pop();
        v[nown] = 0;
        for(int i = 1;i<=n;i++){
            if(r[nown][i]+d[nown]<=d[i]){
                if(r[nown][i]+d[nown] == d[i])
                    ans[i]+=ans[nown];
                else if(r[nown][i]+d[nown]<d[i])
                    d[i] = r[nown][i]+d[nown],ans[i] = ans[nown];
                
                if(v[i] == 0)
                    q.push(i),v[i] = 1;
            }
        }
    }
}

int main(){
    memset(r,0x3f,sizeof(r));
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        r[a][b] = min(r[a][b],c);
    }
    spfa();
    if(ans[n] == 3)
        ans[n] = 2;
    if(d[n]>=100000000)
        printf("No answer\n");
    else
        printf("%d %d\n",d[n],ans[n]);
    return 0;
}