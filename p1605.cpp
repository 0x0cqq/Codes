#include <cstdio>
using namespace std;
int n,m,t,dd[100][100],sx,sy,fx,fy;


int cal(int nowx,int nowy){
    int res = 0;
    if(dd[nowx][nowy] == -1||nowx==0||nowx==n+1||nowy==m+1||nowy==0){
        ;
    }
    else if(nowx == fx && nowy== fy)
        res = 1;
    else{
        dd[nowx][nowy] = -1;
        res += cal(nowx-1,nowy);
        res += cal(nowx,nowy-1);
        res += cal(nowx,nowy+1);
        res += cal(nowx+1,nowy);
        dd[nowx][nowy] = 0;
    }
    return res;
}

int main(){
    scanf("%d %d %d",&n,&m,&t);
    scanf("%d %d",&sx,&sy);
    scanf("%d %d",&fx,&fy);
    for(int i = 0;i<t;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        dd[x][y] = -1;
    }
    printf("%d\n",cal(sx,sy));
    return 0;
}