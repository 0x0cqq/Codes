#include <cstdio>
using namespace std;

int n,m,g[100][100];

char w[1000][1000];

char a[6][8] = {
    "  +---+",
    " /xxx/|",
    "+---+x|",
    "|xxx|x+",
    "|xxx|/ ",
    "+---+  "
};

int maxx = 0,maxy = 0;

void draw(int y,int x,int h){
    int y1 = 6+3*(h-1)+2*(n-y-1);
    int x1 = 4*x+2*(n-y-1)+1;
    if(maxx<x1)
        maxx = x1;
    if(maxy<y1)
        maxy = y1;        
    for(int i = 5;i>=0;i--)
        for(int j = 6;j>=0;j--)
            if(a[i][j]!=' ')
                w[y1-i][x1+j] = a[i][j];
}

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 0;i<n;i++)
        for(int j = 0;j<m;j++)
            scanf("%d",&(g[i][j]));
    for(int h = 1;h<=100;h++)
        for(int i = 0;i<n;i++)
            for(int j = 0;j<m;j++)
                if(g[i][j]>=h)
                    draw(i,j,h);
    for(int i = maxy;i>=1;i--){
        for(int j = 1;j<=maxx+6;j++){
            if(w[i][j]=='\0')
                w[i][j]='.';
            if(w[i][j]=='x')
                w[i][j]=' ';
            putchar(w[i][j]);
        }
        putchar('\n');
    }
    return 0;
}