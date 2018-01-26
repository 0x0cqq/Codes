#include <cstdio>
#define ll long long
using namespace std;

int n,m,a,b;
int ma[9][2] = {{0,0},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1},{-2,1}};
bool v[100][100];
ll dd[100][100];

ll dfs(int nowx,int nowy){
    ll res = 0;
    if(nowx<0||nowy<0||nowx>n||nowy>m||v[nowx][nowy] == 1)
        return 0;
    else if(nowx == n&&nowy ==m)
        return 1;
    else if(dd[nowx][nowy])
        return dd[nowx][nowy];
    else{
        v[nowx][nowy] = 1;
        res += dfs(nowx+1,nowy);
        res += dfs(nowx,nowy+1);
        v[nowx][nowy] = 0;
    }
    return dd[nowx][nowy] = res;
}

int main(){
    scanf("%d %d %d %d",&n,&m,&a,&b);
    for(int i = 0;i<9;i++){
        a+=ma[i][0];b+=ma[i][1];
        if(a>=0&&b>=0)
            v[a][b] = 1;
        a-=ma[i][0];b-=ma[i][1];
    }
    printf("%lld\n",dfs(0,0));
    return 0;
}