#include <cstdio>
using namespace std;

const int N = 60;
const int MAXN = 20*4*400,MAXM = MAXN * 2;

struct Edge{
  int from,to;
  int cap,flow;
  int nex;
}edge[MAXM];int ecnt = 2;
int fir[MAXN];
void addedge(int a,int b,int c){
  edge[ecnt] = (Edge){a,b,c,0,fir[a]};
  fir[a] = ecnt++;
  edge[ecnt] = (Edge){b,a,0,0,fir[b]};
  fir[b] = ecnt++;
}

void reset(int a,b,c,d,e,f,g)

int n,m;

int main(){
  return 0;
}