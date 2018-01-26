#include <cstdio>
using namespace std;

int main(){
    int n,nowx = 1,nowh = 2,f = 1;
    scanf("%d",&n);
    if(n==1){
        printf("1/1\n");
        return 0;
    }
    for(int i = 2;i<=n;i++){
        if(nowx==1&&f == -1){
            nowh++;
            f = 1;
        }
        else if(nowh-nowx == 1&&f == 1){
            nowh++;
            nowx++;
            f = -1;
        }
        else{
            nowx+=f;
        }
    }
    printf("%d/%d\n",nowh-nowx,nowx);
    return 0;
}