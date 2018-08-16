#include <cstdio>
#include <algorithm>
using namespace std;

int b[5][110][110];

int n;

int z[220][220];

void push(int *w){
    for(int k = 1;k<=4;k++){
        int a = w[k];
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                z[(a&1)*n+i][((a-1)/2)*n+j] = b[k][i][j];
            }
        }
    }
}

int judge(){
    int ans1 = 0,ans2= 0 ;
    for(int i = 1;i<=2*n;i++){
        for(int j = 1;j<=2*n;j++){
            if(z[i][j]!=((i+j)&1)) ans1++;
            else{ans2++;}
        }
    }
    return min(ans1,ans2);
}

int main(){
    scanf("%d",&n);
    getchar();
    for(int k = 1;k<=4;k++){
        for(int i = 1;i<=n;i++){
            for(int j = 1;j<=n;j++){
                b[k][i][j] = getchar()-48;
            }
            getchar();
        }
        getchar();
    }
    int a[5],ans = 0x3f3f3f3f;
    for(int i = 1;i<=4;i++){
        a[i] = i;
    }
    do{
        push(a);
        ans = min(ans,judge());
    }while(next_permutation(a+1,a+5));
    printf("%d\n",ans);
    return 0;
}