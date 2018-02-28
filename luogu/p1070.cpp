#include <cstdio>
using namespace std;

const int MAXN = 1100;

int n,m,p,coin[2*MAXN][MAXN],cost[MAXN];

struct dq{
    int v[2*MAXN],ti[2*MAXN],head = 0,tail = 0;
    void push(int val,int times){
        v[tail] = val;
        ti[tail] = times;
        tail++;
    }
    int max(int times){//仅允许时间大于等于times的元素出现
        if(head == tail)
            return -0x3f3f3f3f;
        while(ti[head]<times)
            head++;
        return v[head];
    }
};

void init(){
    scanf("%d %d %d",&n,&m,&p);
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            scanf("%d",&coin[i][j]);
        }
    }
    for(int i = 1;i<=n;i++){
        scanf("%d",&cost[i]);
    }
}


int main(){
    return 0;

}