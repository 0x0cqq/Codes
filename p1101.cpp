#include <cstdio>
using namespace std;

char z[1000][1000],a[10]="yizhong";
bool vis[1000][1000];
int n,d[8][2] = {{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};


bool go(int x,int y,int f,int m){
    x+=d[f][0];y+=d[f][1];
    if(x<0||y<0||y>=n||x>=n)
        return false;
    else if(z[x][y] == a[m])
        return true;
    else
        return false;
}

void dfs(int x,int y,int f,int m){
    if(m==0){
        if(z[x][y]==a[0])
            for(int i = 0;i<8;i++){
                if(go(x,y,i,m+1))
                    dfs(x+d[i][0],y+d[i][1],i,m+1);
            }
    }
    else if(m!=6){
        if(go(x,y,f,m+1)){
            dfs(x+d[f][0],y+d[f][1],f,m+1);
        }
    }
    else{
        for(int i = 0;i<7;i++){
            vis[x][y] = 1;
            x-=d[f][0];y-=d[f][1];
        }
    }
}

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++)
        scanf("%s",z[i]);
    for(int i = 0;i<n;i++){
        for(int w = 0;w<n;w++){
            dfs(i,w,0,0);
        }
    }
    for(int i = 0;i<n;i++){
        for(int w = 0;w<n;w++){
            if(vis[i][w])
                putchar(z[i][w]);
            else
                putchar('*');
        }
        putchar('\n');
    }
    return 0;
}