#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n,m,hq[3000][3000],sq[3000][3000],maxn[3000][3000],maxx = -1;

bool fish[3000][3000];

int main(){
    scanf("%d %d",&n,&m);
    getchar();getchar();
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            fish[i][j] = (getchar() == '1');
            hq[i][j] = hq[i][j-1]+fish[i][j];
            getchar();
        }
        getchar();
    }
    for(int j = 1;j<=m;j++)
        for(int i = 1;i<=n;i++)
            sq[i][j] = sq[i-1][j]+fish[i][j];
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            if(fish[i][j] == 0)
                maxn[i][j] = 0;
            else{
                if(hq[i][j] == hq[i][j-maxn[i-1][j-1]-1]+1 && sq[i][j] == sq[i-maxn[i-1][j-1]-1][j]+1)
                    maxn[i][j] = maxn[i-1][j-1]+1;
                else{
                    for(int w = 1;;w++){
                        if(fish[i-w][j]||fish[i][j-w]){
                            maxn[i][j] = w;
                            break;
                        }
                    }
                }
            }
            maxx = max(maxx,maxn[i][j]);
        }
    }
    memset(maxn,0,sizeof(maxn));
    memset(hq,0,sizeof(hq));
    for(int i = 1;i<=n;i++)
        for(int j = m;j>=1;j--)
            hq[i][j] = hq[i][j+1]+fish[i][j];
    /*putchar('\n');
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            printf("%d ",hq[i][j]);
        }
        putchar('\n');
    }*/
    for(int i = 1;i<=n;i++){
        for(int j = m;j>=1;j--){
            if(fish[i][j] == 0)
                maxn[i][j] = 0;
            else{
                if(hq[i][j] == hq[i][j+maxn[i-1][j+1]+1]+1 && sq[i][j] == sq[i-maxn[i-1][j+1]-1][j]+1)
                    maxn[i][j] = maxn[i-1][j+1]+1;
                else{   
                    for(int w = 1;;w++){
                        if(fish[i-w][j]||fish[i][j+w]){
                            maxn[i][j] = w;
                            break;
                        }
                    }
                }
            }
            maxx = max(maxx,maxn[i][j]);
        }
    }
    /*putchar('\n');
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            printf("%d ",maxn[i][j]);
        }
        putchar('\n');
    }*/
    printf("%d\n",maxx);
    return 0;
}