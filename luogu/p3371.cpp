#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;


inline void qr(int &x){
    int f = 1;int w = 0;char ch = getchar();
    while(ch<='0'||ch>'9')
        ch = getchar();
    while(ch>='0'&&ch<='9'){
        w = (w<<3) + (w<<1)+ch-48;
        ch = getchar();
    }
    x = f*w;
}

struct edge{
    int dst;
    int length;
    edge *next = NULL;
}pool[600000];

struct point{
    int no;
    int l;
    bool operator >(const point a)const{
        return l>a.l;
    }
};

edge *p[20000];

priority_queue<point,vector<point>,greater<point> > a;

int dst[20000];

int main(){
    int n,m,s;
    qr(n);qr(m);qr(s);
    for(int i  = 0;i<m;i++){
        int a,b,c;
        qr(a);qr(b);qr(c);
        pool[i].dst = b;pool[i].length = c;
        pool[i].next = p[a];
        p[a] = &pool[i];
    }
    /*for(int i = 1;i<=n;i++){
        printf("%d:\n",i);
        edge *now = p[i];
        while(now!=NULL){
            printf("%d %d\n",now->dst,now->length);
            now  = now ->next;
        }
        putchar('\n');
    }*/
    for(int i = 1;i<=n;i++){
        point tmp;
        tmp.no = s;
        tmp.l = 0;
        a.push(tmp);   
    }
    memset(dst,-1,sizeof(dst));

    while(!a.empty()){
        point t = a.top();
        a.pop();
        if(dst[t.no]!=-1)
            continue;
        else{
            dst[t.no] = t.l;
            edge *now =p[t.no];
            while(now!=NULL){
                point tmp;
                tmp.no = now->dst;
                tmp.l = t.l + now->length;
                a.push(tmp);
                now  = now ->next;
            }
        }
    }
    for(int i = 1;i<=n;i++){
        if(dst[i] == -1)
            printf("2147483647 ");
        else
            printf("%d ",dst[i]);
    }
    putchar('\n');
    return 0;
}