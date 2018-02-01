// luogu-judger-enable-o2
#include <cstdio>
#include <queue>
#include <cstring>
#define ll long long
using namespace std;

inline void qr(ll &t){
    t = 0;char c = getchar();
    while(c<'0'||c>'9'){
        c = getchar();
    }
    while(c>='0'&&c<='9'){
        t = (t<<3)+(t<<1)+c-48;
        c = getchar();
    }
}

int n,m;

struct edge{
    ll start,end,len;
    edge *next = NULL;
}pool[1000100];

edge *r[1000100];

ll d[1000100];
bool v[1000100];

queue<int> q;

inline void insert(edge *t){
    t->next = r[t->start];
    r[t->start] = t;
}

void spfa(){
    memset(d,0x3f,sizeof(d));
    memset(v,0,sizeof(v));
    d[1] = 0;
    v[1] = 1;
    q.push(1);
    while(!q.empty()){
        int nown = q.front();
        q.pop();
        v[nown] = 0;
        edge* tmp = r[nown];
        while(tmp!=NULL){
            if(d[nown]+tmp->len < d[tmp->end]){
                d[tmp->end] = d[nown]+tmp->len;
                if(v[tmp->end] == 0){
                    q.push(tmp->end);
                    v[tmp->end] = 1;
                }
            }
            tmp = tmp->next;
        }
    }
}

int main(){
    memset(r,0,sizeof(r));
    scanf("%d %d",&n,&m);
    for(int i = 0;i<m;i++){
        qr(pool[i].start),qr(pool[i].end),qr(pool[i].len);
        insert(&pool[i]);
    }
    spfa();
    ll ans = 0;
    for(int i = 1;i<=n;i++){
        ans+=d[i];
    }
    memset(r,0,sizeof(r));
    for(int i = 0;i<m;i++){
        pool[i].next = NULL;
        swap(pool[i].start,pool[i].end);
        insert(&pool[i]);
    }
    spfa();
    for(int i = 1;i<=n;i++){
        ans+=d[i];
    }
    printf("%lld\n",ans);
    return 0;
}