#include <cstdio>
using namespace std;

const int MAXN = 100000;

int num[MAXN];

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
    }
    if(n == 1 || n == 2 && num[1] == num[2]){
        printf("-1\n");
    }
    else{
        int sum = 0;
        for(int i = 1;i<=n;i++){
            sum += i;
        }
        int tmp = 0;
        for(int i = 1;i<=n;i++){
            tmp += num[i]; 
            if(tmp*2 != sum){
                printf("%d\n",i);
                for(int j = 1;j<=i;j++){
                    printf("%d ",j);
                }
                printf("\n");
                return 0;
            }
        }
    }
    return 0;
}