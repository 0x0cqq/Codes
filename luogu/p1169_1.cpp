#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define of(i,j,k) for(int i=j;i>=k;i--)
#define fo(i,j,k) for(int i=j;i<=k;i++)
using namespace std;
const int mxn=2005;
int n,m,ans1,ans2;
int h[mxn][mxn],l[mxn],r[mxn],s[mxn];
bool map[mxn][mxn];
inline void ddz(bool flag){
    memset(h,0,sizeof h);
    fo(i,1,n) fo(j,1,m) if(map[i][j]==flag) h[i][j]=h[i-1][j]+1;
    fo(i,1,n){
        int top=0;
        s[top]=0;
        fo(j,1,m){
            while(h[i][s[top]]>=h[i][j] && top) top--;
            l[j]=s[top]+1; 
            s[++top]=j;
        }
        top=0;s[0]=m+1;
        of(j,m,1){
            while(h[i][s[top]]>=h[i][j] && top) top--;
            r[j]=s[top]-1;
            s[++top]=j;
            ans2=max(ans2,(r[j]-l[j]+1)*h[i][j]);
            if(r[j]-l[j]+1>=h[i][j]) ans1=max(ans1,h[i][j]*h[i][j]);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    fo(i,1,n)
      fo(j,1,m){
          scanf("%d",&map[i][j]);
          if((i+j)%2==0) map[i][j]=!map[i][j];
      }
    ddz(0);ddz(1);
    printf("%d\n%d\n",ans1,ans2);
    return 0;
}