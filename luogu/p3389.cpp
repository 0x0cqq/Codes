#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 110;
const double eps = 1e-7;

bool gauss(double a[MAXN][MAXN],int n){
    for(int i = 1;i<=n;i++){
        int r = i;
        for(int j = i+1;j<=n;j++)
            if(fabs(a[r][i]) < fabs(a[j][i])) r = j;
        if(r!=i)
            for(int j = 1;j<=n+1;j++) 
                swap(a[r][j],a[i][j]);
        if(fabs(a[i][i]) < eps) return false;
        for(int j = 1;j<=n;j++)if(j!=i){
            double t = a[j][i]/a[i][i];
            for(int k = i+1;k<=n+1;k++)
                a[j][k] -= a[i][k] * t;
        }
        // for(int i = 1;i<=n;i++){
        //     for(int j = 1;j<=n+1;j++){
        //         printf("%lf ",a[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("\n");
    }
    for(int i = 1;i<=n;i++)
        a[i][n+1]/=a[i][i];
    return true;
}
int n;
double num[MAXN][MAXN];

void init(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n+1;j++){
            scanf("%lf",&num[i][j]);
        }
    }
}

void solve(){
    if(gauss(num,n))
        for(int i = 1;i<=n;i++)
            printf("%.2lf\n",num[i][n+1]);
    else
        printf("No Solution\n");
}

int main(){
    init();
    solve();
    return 0;
}