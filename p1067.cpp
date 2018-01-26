#include <cstdio>
using namespace std;

int main(){
    int n;
    scanf("%d",&n);
    for(int i = n;i >=0;i--){
        int t;
        scanf("%d",&t);
        if(t==0) continue;
        if(i>1){
            if(t>0&&i!=n)
                putchar('+');
            if(t==1)
                printf("x^%d",i);
            else if(t==-1)
                printf("-x^%d",i);
            else
                printf("%dx^%d",t,i);
        }
        else if(i == 1){
            if(t>0&&i!=n)
                putchar('+');
            if(t==1)
                printf("x");
            else if(t==-1)
                printf("-x");
            else 
                printf("%dx",t);
        }
        else if(i == 0){
            if(t>0)
                putchar('+');
            printf("%d",t);
        }
        
    }
    putchar('\n');
    return 0;
}