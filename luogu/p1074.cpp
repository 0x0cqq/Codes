#include <cstdio>
using namespace std;

struct gezi{
    int num = 0,p = (1<<11)-1,r,c,g;
    gezi();
    gezi(int x,int y){
        int n;
        scanf("%d",&n);
        num = n;
        r = x;c = y;
        g = (r/3-1)*3+(c/3);
    }
    void update(gezi **b){
        for(int i = 1;i<=9;i++){
            b[i][c].p &= (1<<10)-(1<<num)-1;
            b[r][i].p &= (1<<10)-(1<<num)-1;
            
        }
    }
}board[10][10];

int score[10][10] = 
{{0,0,0,0,0,0,0,0,0,0},
{0,6,6,6,9,6,6,6,6,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,9,10,9,8,7,6},
{0,6,7,8,9,9,9,8,7,6},
{0,6,7,8,8,8,8,8,7,6},
{0,6,7,7,7,7,7,7,7,6},
{0,6,6,6,6,6,6,6,6,6}};

int jg[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}},ans = 0,maxn = -0x3f3f3f3f;

void solve(){

}

int main(){
    for(int i = 1;i<=9;i++){
        for(int j = 1;j<=9;j++){
            board[i][j] = gezi(i,j);
            if(board[i][j].num!=0){
                ans += board[i][j].num*score[i][j];
                board[i][j].p = 0;
            }
        }
    }
    solve();
    if(maxn<0)
        printf("-1\n");
    else
        printf("%d\n",maxn);
    return 0;
}