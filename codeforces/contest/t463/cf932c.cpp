#include <cstdio>
using namespace std;


int exgcd(int a,int b,int &x,int &y)  {  
    if(b==0){  
        x=1,y=0;  
        return a;  
    }  
    int r=exgcd(b,a%b,x,y);  
    int t=x;x=y;y=t-a/b*y;  
    return r;  
}   

int gcd(int a,int b){
    if(a == 0 || b == 0)
        return a+b;
    else{
        if(a>b)
            a%=b;
        else
            b%=a;
        return gcd(a,b);
    }
}

int linear_equation(int a,int b,int c,int &x,int &y){  
    int d=exgcd(a,b,x,y);  
    if(c%d)  
        return -1;  
    int k=c/d;  
    x*=k; y*=k;    //求得的只是其中一组解  
    return k;  
}  

int ans[1100000];

int main(){
    int n,a,b,x,y;
    scanf("%lld %lld %lld",&n,&a,&b);
    int w = linear_equation(a,b,n,x,y);
    int k = gcd(a,b);
    if(w == -1){
        printf("-1\n");
    }
    else{
        int f = x > 0?-1:1;
        //printf("%d %d %d\n",x,y,w);
        for(int i = 1;i<=1000000;i++){
            if(x >= 0 && y>=0){break;}
            //printf("%d %d %d\n",x,y,w);
            if(x < 0 && y< 0) break;
            if(y <= 0 && f == 1) break;
            if(x <= 0 && f == -1) break;
            x+=(b/k)*f;y-=(a/k)*f;
        }
        if(x>=0&&y>=0){
            int i = 1;
            for(int j = 1;j<=x;j++){
                for(int k = 1;k<=a;k++){
                    ans[i] = i+1;
                    i++;
                }
                ans[i-1] = i-a;
            }
            for(int j = 1;j<=y;j++){
                for(int k = 1;k<=b;k++){
                    ans[i] = i+1;
                    i++;
                }
                ans[i-1] = i-b;
            }
            for(int i = 1;i<=n;i++){
                printf("%lld ",ans[i]);
            }
            putchar('\n');
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}