#include <cstdio>
#include <algorithm>
using namespace std;

int m,n,dd[3500];
struct wupin{
    int weight,value,father,son;
}k[1000];

int main(){
    scanf("%d %d",&m,&n);
    m/=10;
    for(int i = 1;i<=n;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        k[i].weight = a/10;k[i].value = a*b;k[i].father = c;
        k[c].son++;   
    }
    for(int i = 1;i<=n;i++)
        if(k[i].son){
            int a,b,f = 0;
            for(int j = 1;j<=n;j++){
                if(k[j].father == i){
                    k[j].weight+=k[i].weight;
                    k[j].value+=k[i].value;
                    f++?a = j:b = j;
                }
                if(f == 2){
                    k[++n].weight = k[a].weight+k[b].weight-k[i].weight;
                    k[n].value = k[a].value+k[b].value-k[i].value;
                    k[n].father = i;
                    break;
                }
            }
        }
    for(int j = 1;j<=n;j++){
        if(k[j].father!=0)
            continue;
        for(int i = m;i>=0;i--)
            for(int x = n;x>=1;x--)
                if((k[x].father == j||x == j)&&i>=k[x].weight)
                    dd[i] = max(dd[i],dd[i-k[x].weight]+k[x].value);
    }
    printf("%d\n",dd[m]);
    return 0; 
}