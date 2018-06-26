#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int num[10000];

int main(){
    int n;
    scanf("%d",&n);
    int sum = 0;
    for(int i = 1;i<=n;i++){
        scanf("%d",&num[i]);
        
    }
    sort(num+1,num+n+1);
    for(int j = 1;j<=n;j++)
        sum += num[j];
    sum = round(double(sum)/n);
    if(sum >= 5){
        printf("%d\n",0);
        return 0;
    }
    for(int i = 1;i<=n;i++){
        sum = 0;
        num[i] = 5;
        for(int j = 1;j<=n;j++){
            sum += num[j];
        }
        sum = round(double(sum)/n);
        if(sum >= 5){
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}