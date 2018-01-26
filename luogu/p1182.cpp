#include <cstdio>
using namespace std;

int N,M,a[100010];

bool check(int w){
    //是否还能把间隔改小一点
    int now = 0,num = 0;
    for(int i = 1;i<=N;i++){
        if(now+a[i]>=w){
            num++;
            now = a[i];
        }
        else{
            now+=a[i];
        }
        if(i == N)
            num++;
    }
    return num<=M;
}

int main(){
    int max = 0;
    scanf("%d %d",&N,&M);
    for(int i = 1;i<=N;i++){
        scanf("%d",a+i);
        if(a[i]>max)
            max = a[i];
    }
    int b = max,e = 200000000;
    while(e-b>1){
        int t = (b+e)/2;
        if(check(t)){
            e = t;
        }
        else{
            b = t;
        }
        //printf("b:%d,e:%d,t:%d,check:%d\n",b,e,t,check(t));
    }
    printf("%d\n",b);
    return 0;
}