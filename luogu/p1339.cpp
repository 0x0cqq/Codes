#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int t,c,ts,te,tot = 0;

struct road{
    int p,l;
    road *next = NULL;    
}pool[300000];


road *r[3000];
int dis[3000],times[3000];
bool vis[3000];


int main(){
    scanf("%d %d %d %d",&t,&c,&ts,&te);
    for(int i = 0;i<c;i++){
        int rs,re,ci;
        scanf("%d %d %d",&rs,&re,&ci);
        road *newr = &pool[tot++];
        newr->p = re;newr->l = ci;
        if(r[rs]!=NULL){
            newr->next = r[rs]->next;
            r[rs]->next = newr;
        }
        else
            r[rs] = newr;
        newr = &pool[tot++];
        newr->p = rs;newr->l = ci;
        if(r[re]!=NULL){
            newr->next = r[re]->next;
            r[re]->next = newr;
        }
        else
            r[re] = newr;        
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
    printf("%d\n",dis[te]);
    return 0;
}