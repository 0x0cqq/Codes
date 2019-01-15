#include <cstdio>
#include <algorithm>
using namespace std;

int a[9];

int main(){
    for(int i = 0;i<9;i++){
        a[i] = i+1;
    }
    do{
        int x = a[0]*100+a[1]*10+a[2];
        int y = a[3]*100+a[4]*10+a[5];
        int z = a[6]*100+a[7]*10+a[8];
        // if(x*2==y&&x*3==z){
            printf("%d %d %d\n",x,y,z);
        // }
    }while(next_permutation(a,a+9));
}