#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
#define fuck printf("fuck\n")

int a[20],p[20],ans = 13,ansa = 0,ansb = 0;

void dfs(int n,int now,int a,int b,int c,int jin,int ra,int rb){//最小需要添加的位数
  if(now >= ans) return;
  if(!a&&!b&&!c&&!jin){
    ans = now,ansa = ra,ansb = rb;
    return;
  }
  if(!c){
    int t = (int)(log10(a+b+jin)+1);
    dfs(n,now+t,0,0,0,0,ra+a*p[n],rb+b*p[n]);
    return;
  }
  if((a+b+jin)%10 == c % 10){
    dfs(n+1,now,a/10,b/10,c/10,(a%10+b%10+jin)/10,ra+a%10*p[n],rb+b%10*p[n]);
  }
  else{
    dfs(n,now+1,a*10 + (c%10-b%10-jin+10)%10,b,c,jin,ra,rb);// 三种可能的办法
    dfs(n,now+1,a,b*10 + (c%10-a%10-jin+10)%10,c,jin,ra,rb);// 三种可能的办法
    dfs(n,now+1,a,b,c*10 + (b+a+jin+10)%10,jin,ra,rb);// 三种可能的办法
    //*10相当于平移一位
  }
}

signed main(){
  scanf("%lld+%lld=%lld",&a[0],&a[1],&a[2]);
  // for(int i = 0;i<3;i++){w[i] = int(log10(a[i])+1);}
  // printf("%lld %lld %lld:%lld %lld %lld\n",a[0],a[1],a[2],w[0],w[1],w[2]);
  p[0] = 1;
  for(int i = 1;i<=12;i++)p[i] = p[i-1]*10;
  dfs(0,0,a[0],a[1],a[2],0,0,0);
  
  printf("%lld+%lld=%lld\n",ansa,ansb,ansa+ansb);
  return 0;
}