#include <cstdio>
using namespace std;

const int MAXN = 1000000,MAXM = 6000000;

struct Edge{
    int from,to;
    int cap,flow;
    int nex;
}edge[MAXM];

int n,m,s,t,ecnt = 2;
int fir[MAXN],cur[MAXN];

inline int sss(int i,int j){
    return (i-1)
}

void addedge(int a,int b,int c){
    edge[ecnt] = (Edge){a,b,c,0,fir[a]};
    fir[a] = ecnt++;
    edge[ecnt] = (Edge){b,a,0,0,fir[b]};
    fir[b] = ecnt++;    
}

void init(){
    read(n),read(m);
    for(int i)
}

int main(){
    return 0;
}