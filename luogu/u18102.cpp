#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#define minn(x,y) ((x)>(y)?(y):(x))
#define c1(a,b,c,d) (cc[1].ai*(a)+cc[2].ai*(b)+cc[3].ai*(c)+cc[4].ai*(d)+1)
#define c2(a,b,c,d) (cc[1].bi*(a)+cc[2].bi*(b)+cc[3].bi*(c)+cc[4].bi*(d)+1)
using namespace std;

int n,m,k;
struct cc{
    int num,ai,bi;
}cc[5];

double board[1100][1100],dd[2][310][200][200];

int main(){
    freopen("1.txt","r",stdin);
    clock_t t1 = clock();
    scanf("%d %d %d",&n,&m,&k);
    for(int i = 1;i<=4;i++)
        scanf("%d %d %d",&cc[i].ai,&cc[i].bi,&cc[i].num);
    for(int i = 1;i<=n;i++)
        for(int j = 1;j<=m;j++)
            scanf("%lf",&board[i][j]);
    clock_t t2 = clock();
    //printf("%lf\n",double(t2-t1)/CLOCKS_PER_SEC);
    for(int w = 1,tmp = w&1;w<=k;++w,tmp = w&1){
        for(int i = minn(w,cc[1].num);i>=0;i--){
            for(int j = minn(w-i,cc[2].num);j>=0;j--){
                for(int l = minn(w-i-j,cc[3].num);w-i-j-l<=cc[4].num&&l>=0;l--){
                    int cx = c1(i,j,l,w-i-j-l),cy = c2(i,j,l,w-i-j-l);
                    double res = -100000000;
                    if(i>0&&res<dd[tmp][i-1][j][l]) res = dd[tmp][i-1][j][l];
                    if(j>0&&res<dd[tmp][i][j-1][l]) res = dd[tmp][i][j-1][l];  
                    if(l>0&&res<dd[tmp][i][j][l-1]) res = dd[tmp][i][j][l-1];
                    if(w-i-j-l>0&&res<dd[tmp][i][j][l]) res = dd[tmp][i][j][l];
                    dd[tmp?0:1][i][j][l] = res + board[cx][cy];
                }
            }
        }
    }
    printf("%.4lf\n",dd[k&1?0:1][cc[1].num][cc[2].num][cc[3].num]+board[1][1]);
    return 0;
}