#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int board[500][500];
int mov[8][2] = {{-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
bool v[500][500];

struct bo{
    int x,y;
    int nown;
};

queue<bo> w;

int main(){
    memset(board,-1,500*500*4);
    int m,n,a,b;
    scanf("%d %d %d %d",&m,&n,&a,&b);
    bo first;
    first.x = a;first.y = b;first.nown = 0;
    w.push(first);
    while(!w.empty()){
        bo no = w.front();
        w.pop();
        board[no.x][no.y] = no.nown;
        v[no.x][no.y] = 1;
        for(int i = 0;i<8;i++){
            bo need = no;
            need.x += mov[i][0];
            need.y += mov[i][1];
            need.nown++;
            if(need.x<=0||need.y<=0||need.x>m||need.y>n||v[need.x][need.y]){
                continue;
            }
            else{
                v[need.x][need.y] = 1;
                w.push(need);
            }
        }
    }
    for(int i = 1;i<=m;i++){
        for(int j = 1;j<=n;j++){
            printf("%-5d",board[i][j]);
        }
        putchar('\n');
    }
    return 0;
}