#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAX=100;
const int MAXL=10000;
struct Line
{
       int v,next;
}e[MAXL];
int h[MAX],cnt=0,tot;
int T,n;
int home[MAX];
int school[MAX],a,sum;
inline void Add(int u,int v)
{
       e[cnt]=(Line){v,h[u]};
       h[u]=cnt++;
}
int match[MAX];
bool vis[MAX];
bool DFS(int x)
{
       for(int i=h[x];i!=-1;i=e[i].next)
       {
              int v=e[i].v;
              if(!vis[v])
              {
                    vis[v]=true;
                    if(!match[v]||DFS(match[v]))
                    {
                            match[v]=x;
                            return true;
                    }
              }
       }
       return false;
}
int main()
{
        freopen("1.in","r",stdin);
       cin>>T;
       while(T--)
       {
             cnt=tot=0;
             memset(h,-1,sizeof(h));
             cin>>n;
             for(int i=1;i<=n;++i)
                cin>>school[i];
             for(int i=1;i<=n;++i)
             {
                  cin>>home[i];
                  if(home[i]==0&&school[i])//如果此人是在校学生并且不回家 
                     Add(i,i);//可以睡自己的床 
             }
             for(int i=1;i<=n;++i)//统计要床的人 
               if(!school[i]||(school[i]&&!home[i]))
                    ++tot;
             for(int i=1;i<=n;++i)
             {
                  for(int j=1;j<=n;++j)
                  {
                         cin>>a;
                         if(a&&school[j])//如果i认识j并且j是学生
                               Add(i,j);//i可以睡j的床 
                  }
             }
             memset(match,0,sizeof(match));
             sum=0;
             for(int i=1;i<=n;++i)
             {
                   if((school[i]&&home[i]==0)||!school[i])//要么是学生在学校，要么是外来的人
                   {
                         memset(vis,0,sizeof(vis));
                         if(DFS(i))++sum;
                   }
             }
             printf("%d\n",sum);
             if(sum==tot)
                cout<<"^_^"<<endl;
             else
                cout<<"T_T"<<endl;
       }
       return 0;
}