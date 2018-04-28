#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define N 100
using namespace std;
struct node {int x,y,z;} a[N];
pair<int,int> b[N];
int f[N][N][N];
int n,K;
inline int read()
{
    int a=0,f=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {a=a*10+c-'0'; c=getchar();}
    return a*f;
}
inline bool cmp(node a,node b)
{
    return a.x<b.x;
}
int main()
{
    n=read(); K=read();
    for (int i=1;i<=n;i++) a[i].x=read();
    for (int i=1;i<=n;i++) a[i].y=read();
    for (int i=1;i<=n;i++) a[i].z=read();
    sort(a+1,a+n+1,cmp);
    for (int i=1;i<=n;i++)
        b[i]=make_pair(a[i].y,i);
    sort(b+1,b+n+1);
    for (int i=1;i<=n;i++)
        a[b[i].second].y=i;
    for (int i=1;i<=n;i++)
        a[i].z+=a[i-1].z;
    memset(f,0x3f,sizeof(f));
    for (int i=1;i<=n+1;i++)
        for (int w=0;w<=n;w++)
            f[i][i-1][w]=0;
    for (int w=n;~w;w--)
        for (int i=n;i;i--)
            for (int j=i;j<=n;j++)
                for (int k=i;k<=j;k++)
                {
                    if (a[k].y>=w)
                        f[i][j][w]=min(f[i][j][w],f[i][k-1][a[k].y]+f[k+1][j][a[k].y]+a[j].z-a[i-1].z);
                    f[i][j][w]=min(f[i][j][w],f[i][k-1][w]+f[k+1][j][w]+K+a[j].z-a[i-1].z);
                }
    cout << f[1][n][0] << endl;
    return 0;
}