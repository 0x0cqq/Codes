#include <cstdio>
using namespace std;

int n;
int b[40][40];

void dfs(int i,int j,int c,int nt){
    if(i<0||j<0||i>=n||j>=n)
        return;
    if(b[i][j]!=nt)
        return;
    b[i][j] = c;
    dfs(i,j+1,c,nt);
    dfs(i+1,j,c,nt);
    dfs(i,j-1,c,nt);
    dfs(i-1,j,c,nt);
    return;
}

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            scanf("%d",&b[i][j]);
        }
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(b[i][j] == 0){
                dfs(i,j,2,0);
            }
        }
    }
    for(int i = 0;i<n;i++){
        if(b[i][0] == 2){
            dfs(i,0,0,2);
        }
        if(b[i][n-1] == 2){
            dfs(i,n-1,0,2);
        }
        if(b[n-1][i] == 2){
            dfs(n-1,i,0,2);
        }
        if(b[0][i] == 2){
            dfs(0,i,0,2);
        }
    }
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            printf("%d ",b[i][j]);
        }
        putchar('\n');
    }
    return 0;
}