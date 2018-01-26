#include <cstdio>
#include <algorithm>
using namespace std;

int a[9];

int main(){
    int A,B,C,f = 0;
    scanf("%d %d %d",&A,&B,&C);
    for(int i = 0;i<9;i++){
        a[i] = i+1;
    }
    do{
        double x = a[0]*100+a[1]*10+a[2];
        double y = a[3]*100+a[4]*10+a[5];
        double z = a[6]*100+a[7]*10+a[8];
        if(x/A*B==y&&y/B*C==z){
            printf("%g %g %g\n",x,y,z);
            f++;
        }
    }while(next_permutation(a,a+9));
    if(f==0)
        printf("No!!!\n");
    return 0;
}