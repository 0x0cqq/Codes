
#include<iostream>  
#include<cstdio>  
#define N 400000  
using namespace std;  

int phi[N+10],prime[N+10],tot,ans;  
bool mark[N+10];  
void getphi(){  
   int i,j;  
   phi[1]=1;  
   for(i=2;i<=N;i++)//相当于分解质因式的逆过程  
   {  
       if(!mark[i])  {  
             prime[++tot]=i;//筛素数的时候首先会判断i是否是素数。  
             phi[i]=i-1;//当 i 是素数时 phi[i]=i-1  
        }  
       for(j=1;j<=tot;j++)  
       {  
          if(i*prime[j]>N)  break;  
          mark[i*prime[j]]=1;//确定i*prime[j]不是素数  
          if(i%prime[j]==0)//接着我们会看prime[j]是否是i的约数  
          {  
             phi[i*prime[j]]=phi[i]*prime[j];break;  
          }  
          else  phi[i*prime[j]]=phi[i]*(prime[j]-1);//其实这里prime[j]-1就是phi[prime[j]]，利用了欧拉函数的积性  
       }  
   }  
}  

int gcd(int a,int b){
    return b == 0?a:gcd(b,a%b);
}
int main()  {  
    getphi(); 
    int n,m;
    scanf("%d %d",&n,&m);
    long long sum = 0; 
    for(int i = 2;i<=n;i++){
        sum += phi[i];
    }
    if(sum < m || m < n-1)
        printf("Impossible\n");
    else{
        int cnt = 0;
        printf("Possible\n");
        for(int i = 2;i<=n;i++){
            printf("%d %d\n",1,i),cnt++;
            if(cnt == m) break;
        }
        for(int i = 3;i<=n;i++){
            if(cnt == m) break;
            for(int j = 2;j<i;j++){
                if(cnt == m) break;
                if(gcd(i,j) == 1)
                    printf("%d %d\n",j,i),cnt++;
                if(cnt == m) break;
            }
            if(cnt == m) break;
        }
    }
    return 0;
} 