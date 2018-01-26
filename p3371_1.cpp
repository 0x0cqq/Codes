#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

inline int qr(){
    int f = 1,s = 0;char ch = getchar();
    while(ch<'0'||ch>'9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        s = (s<<3)+(s<<1)+ch-48;
        ch = getchar();
    }
    return f*s;
}

int t,c,ts,te,tot = 0;

struct road{
    int p,l;
    road *next = NULL;    
}pool[1000000];


road *r[11000];
int dis[11000],times[11000];
bool vis[11000];


int main(){
    scanf("%d %d %d",&t,&c,&ts);
    for(int i = 0;i<c;i++){
        int rs,re,ci;
        rs = qr();re = qr();ci = qr();
        road *newr = &pool[tot++];
        newr->p = re;newr->l = ci;
        if(r[rs]!=NULL){
            newr->next = r[rs]->next;
            r[rs]->next = newr;
        }
        else
            r[rs] = newr;     
    }
    memset(dis,0x3f,sizeof(dis));
    queue<int> b;
    dis[ts] = 0;
    vis[ts] = 1;
    b.push(ts);
    while(!b.empty()){
        int nown = b.front();
        b.pop();
        //printf(":%d %d\n",nown,dis[nown]);
        vis[nown] = 0;
        if(++times[nown] >=t+1){
            printf("-1\n");
            return 0;
        }
        road *now = r[nown];
        while(now!=NULL){
            if(dis[nown]+now->l<dis[now->p]){
                dis[now->p] = dis[nown]+now->l;
                if(vis[now->p]==0){
                    vis[now->p] = 1;
                    b.push(now->p);
                }
            }
            now = now->next;
        }
    }
    for(int i = 1;i<=t;i++){
        if(dis[i]>= 0x3f3f3f3f)
            printf("2147483647 ");
        else{
            printf("%d ",dis[i]);
        }
    }
    putchar('\n');
    return 0;
}