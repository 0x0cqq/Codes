#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=10000;
int n,G[MAXN+10][2],vis[MAXN+10],linker[MAXN+10],rlinker[MAXN+10];
bool dfs(int x)
{
    for(int i=0;i<=1;i++)//应当先考虑边所对应的另一个点较小的
    {
        if(!vis[G[x][i]])
        {
            vis[G[x][i]]=true;
            if(linker[G[x][i]]==-1||dfs(linker[G[x][i]]))
            {
                linker[G[x][i]]=x;
                rlinker[x]=G[x][i];
                return true;
            }
        }
    }
    return false;
}
bool work()
{
    memset(linker,-1,sizeof linker);
    for(int i=n-1;i>=0;i--)//倒过来扫
    {
        memset(vis,0,sizeof vis);
        if(!dfs(i))
        {
            return false;
        }
    }
    return true;
} 
int main()
{
    scanf("%d",&n);
    int k,a,b;
    for(int i=0;i<n;i++)
    {
        scanf("%d",&k);
        a=(i-k+n)%n;
        b=(i+k)%n;
        G[i][0]=min(a,b);
        G[i][1]=max(a,b);
    }
    if(!work())
    {
        printf("No Answer");
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        printf("%d ",rlinker[i]);
    }
    putchar('\n');
    return 0;
}