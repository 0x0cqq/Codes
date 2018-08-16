#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
using namespace std;

int n,m;

int mat[200][200];
int a[200],b[200];

int main(int argc, char const *argv[]){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i =1 ;i<=m;i++){
        scanf("%d",&b[i]);
    }
    for(int i = 1;i<=n-1;i++){
        for(int j = 1;j<=m-1;j++){
            mat[i][j] = rand()%(min(a[i],b[j]));
        }
    }
    for(int i = 1;i<=n-1;i++){
        int sum = 0;
        for(int j = 1;j<=m-1;j++){
            sum ^= mat[i][j];
        }
        mat[i][m] = a[i]^sum; 
    }
    for(int j = 1;j<=m;j++){
        int sum = 0;
        for(int i = 1;i<=n-1;i++){
            sum ^= mat[i][j];
        }
        mat[n][j] = b[j]^sum;
    }
    int sum = 0;
    for(int i = 1;i<=n;i++){
        sum ^= mat[i][m];
    }
    if(sum == mat[n][m]){
        printf("YES\n");
    }
    else{
        printf("NO\n");
    }
    return 0;
}
