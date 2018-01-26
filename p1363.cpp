#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;


int n,m,sx,sy;;
char board[5000][5000];
bool v[5000][5000];
queue<pair<int,int> > w;


bool dfs(int x,int y){
    if(x<0||y<0||x>=3*m||y>=3*n){
        pair<int,int> tem;
        tem.first = (x+3*m)%(3*m);
        tem.second = (y+3*n)%(3*n);
        w.push(tem);
        return 0;
    }
    if(v[x][y] == 1)
        return 0;
    if(board[x][y]=='#')
        return 0;
    if(x != sx && y!=sy && board[x][y] == 'S')
        return 1;
    //printf(":");
    v[x][y] = 1;
    return dfs(x-1,y)||dfs(x,y-1)||dfs(x,y+1)||dfs(x+1,y);
}


int main(){
    while(scanf("%d %d ",&n,&m) == 2){
        queue<pair<int,int> > empty;
        swap(w, empty);
        memset(board,0,5000*5000);
        memset(v,0,5000*5000);
        char c = getchar();
        //printf(":%c\n",c);
        for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                for(int k = 0;k<3;k++)
                    for(int w = 0;w<3;w++)
                        board[i+k*n][j+w*m] = c;
                if(c == 'S'){
                    sx = j+m;sy = i+n;
                    //printf("\n:%d %d",i,j);
                }
                c = getchar();
            }
            while(i!=n-1&&(c=='\n'||c=='\r')){
                c = getchar();
            }
        }
        //printf("%d %d %c\n",sx,sy,board[sx][sy]);
        for(int i = 0;i<3*n;i++){
            for(int j = 0;j<3*m;j++){
                putchar(board[i][j]);
            }
            putchar('\n');
        }
        if(dfs(sx,sy))
            printf("Yes\n");
        else{
            //printf("HAHAHA");
            bool flag = 0;
            while (!w.empty()){
                if(v[w.front().first][w.front().second] == 1||board[w.front().first][w.front().second] == 'S')
                    flag = 1;
                w.pop();
            }
            if(flag)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }
    return 0;
}