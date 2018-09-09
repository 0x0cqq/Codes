#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int N=110;typedef unsigned long long ll;
int n;int m;int l;int siz;ll mod=1e9+7;ll tp[2*N][2*N];
struct mar//矩阵类 
{
    ll m[2*N][2*N];
    void operator *=(const mar& a)
    {
        for(int i=1;i<=2*siz;i++){for(int j=1;j<=2*siz;j++){tp[i][j]=0;}}
        for(int i=1;i<=2*siz;i++)
        {
            for(int j=1;j<=2*siz;j++)
            {for(int k=1;k<=2*siz;k++){tp[i][j]=(tp[i][j]+m[i][k]*a.m[k][j])%mod;}}
        }
        for(int i=1;i<=2*siz;i++){for(int j=1;j<=2*siz;j++){m[i][j]=tp[i][j];}}
    }
}st,r,tr;
struct trie//trie图 
{
    int mp[N][30];int fil[N];bool ed[N];int cnt;queue <int> q;trie(){cnt=1;}
    inline int add(int p,int c){return mp[p][c]=(mp[p][c])?mp[p][c]:++cnt;}
    inline void end(int p){ed[p]=true;}
    inline void build()//建图函数 
    {
        for(int i=1;i<=26;i++)
        {if(mp[1][i]){q.push(mp[1][i]);fil[mp[1][i]]=1;}else {mp[1][i]=1;}}
        for(;!q.empty();q.pop())//bfs 
        {
            for(int p=q.front(),i=1;i<=26;i++)
            {
                if(mp[p][i])
                {
                    q.push(mp[p][i]);fil[mp[p][i]]=mp[fil[p]][i];//连边 
                    ed[mp[p][i]]=ed[mp[p][i]]||ed[fil[mp[p][i]]];//记得递推结束标记 
                }
                else {mp[p][i]=mp[fil[p]][i];}
            }
        }
    }
    inline void trv(int& p,int c){p=(ed[mp[p][c]])?-1:mp[p][c];}//转移函数 
}t;
char mde[N][N];int len[N];int dp[N][N];char rd[N];ll res;
int main()
{
    scanf("%d%d%d",&n,&m,&l);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",mde[i]+1);//暴力计算len 
        for(len[i]=1;mde[i][len[i]+1]!='\0';len[i]++);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%s",rd+1);int p=1;
        for(int i=1;rd[i]!='\0';i++){p=t.add(p,rd[i]-'a'+1);}t.end(p);
    }t.build();siz=t.cnt;
    if(l<=100)//判下l 
    {
        dp[0][1]=1;
        for(int i=0;i<=l;i++)
        {
            for(int j=1;j<=siz;j++)
            {
                if(dp[i][j]==0){continue;}
                for(int k=1;k<=n;k++)
                {
                    if(i+len[k]>l){continue;}int p=j;//判一下转移是否合法 
                    for(int q=1;q<=len[k]&&p!=-1;q++){t.trv(p,mde[k][q]-'a'+1);}
                    if(p!=-1){dp[i+len[k]][p]=(dp[i+len[k]][p]+dp[i][j])%mod;}
                }
            }
        }
        for(int i=1;i<=siz;i++){res=(res+dp[l][i])%mod;}printf("%lld",res);
    }
    else 
    {
        st.m[1][siz+1]=1;//我们从第-1项和第0项开始dp 
        for(int i=1;i<=siz;i++){tr.m[siz+i][i]=1;}//左下方的单位矩阵 
        for(int i=1;i<=siz;i++)
        {
            for(int q=1;q<=n;q++)
            {
                if(len[q]!=1)continue;int p=i;if(t.ed[p])continue;//一步的矩阵 
                t.trv(p,mde[q][1]-'a'+1);if(p!=-1){tr.m[siz+i][siz+p]++;}
            }
        }
        for(int i=1;i<=siz;i++)
        {
            for(int q=1;q<=n;q++)
            {
                if(len[q]!=2)continue;int p=i;if(t.ed[p])continue;
                t.trv(p,mde[q][1]-'a'+1);if(p==-1)continue;//两步的矩阵 
                t.trv(p,mde[q][2]-'a'+1);if(p!=-1){tr.m[i][siz+p]++;}
            }
        }
        for(int i=1;i<=2*siz;i++){r.m[i][i]=1;}//单位元 
        for(int p=l;p;p>>=1,tr*=tr){if(p&1){r*=tr;}}st*=r;//矩阵快速幂 
        for(int i=1;i<=siz;i++){res=(res+st.m[1][siz+i])%mod;}//最后答案是在后边 
        printf("%lld",res); 
    }return 0;//拜拜程序~ 
}