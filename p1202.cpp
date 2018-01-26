#include <cstdio>
using namespace std;

int k[13] = {-1,5,1,1,4,6,2,4,0,3,5,1,3};
int ans[13];

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 1900;i<=1900+n-1;i++){
        for(int j = 1;j<=2;j++){
            ans[k[j]]++;
            if(i%4==0){
                if(i%100!=0)
                    k[j]+=2;
                else if(i%400 == 0)
                    k[j]+=2;
                else
                    k[j]+=1;
            }
            else
                k[j]+=1;
            k[j]%=7;
        }
        for(int j = 3;j<=12;j++){
            ans[k[j]]++;
            if((i+1)%4==0){
                if((i+1)%100!=0)
                    k[j]+=2;
                else if((i+1)%400 == 0)
                    k[j]+=2;
                else
                    k[j]+=1;
            }
            else
                k[j]+=1;
            k[j]%=7;
        }
        //printf("%d\n",i+1);
        //for(int i = 1;i<=12;i++){
        //    printf("%d ",k[i]);
        //}
        //putchar('\n');
    }
    for(int i = 5;i<7;i++){
        printf("%d ",ans[i]);
    }
    for(int i = 0;i<5;i++){
        printf("%d ",ans[i]);
    }
    putchar('\n');
    return 0;
}