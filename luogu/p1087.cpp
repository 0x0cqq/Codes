#include <cstdio>
#include <cmath>
using namespace std;

int n;
char s[10000];


int print(int b,int e){//0代表全是0，1代表全是1，-1代表有0有1
    if(e-b == 1){
        if(s[b] == '1')
            putchar('I');
        else
            putchar('B');
        return (s[b] == '1');
    }
    int l = print(b,(b+e)/2);
    int r = print((b+e)/2,e);
    if(l==0&&r==0){
        putchar('B');
        return 0;
    }
    else if(l==1&&r==1){
        putchar('I');
        return 1;
    }
    else{
        putchar('F');
        return -1;
    }
}


int main(){
    scanf("%d",&n);
    scanf("%s",s);
    print(0,int(pow(2,n)));
    putchar('\n');
    return 0;
}


