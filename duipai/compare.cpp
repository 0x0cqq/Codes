#include <bits/stdc++.h>
#define inf 1e18
using namespace std;

FILE *in,*o1,*o2,*a1;
void file_open(){
  in = fopen("in.txt","r");
  o1 = fopen("out1.txt","r");
  o2 = fopen("out2.txt","r");
  a1 = fopen("diff.txt","w");
}
void file_close(){
  fclose(in);
  fclose(o1);
  fclose(o2);
  fclose(a1);
}


int diff(){
  return system("diff out1.txt out2.txt > /dev/null 2>&1");
}

const int MAXN = 110000;
const int MAXQ = 500;

struct Query{
  int l,r,t,id;
  bool operator < (const Query &a)const{
    return t < a.t;
  }
}q[MAXN];

int n,m;

struct P{
  int a,b,id;
  bool operator < (const P &x) const{
    if(b != x.b) return b < x.b;
    if(a != x.a) return a > x.a;
    return 0;
  }
}p[MAXN];


double calv(P x,int t){
  return double(x.a) + double(x.b)*t;
}


void init(){
  fscanf(in,"%d %d",&n,&m);
  for(int i = 1;i<=n;i++){
    fscanf(in,"%d %d",&p[i].a,&p[i].b);
    p[i].id = i;
  }
  for(int i = 1;i<=m;i++){
    fscanf(in,"%d %d %d",&q[i].l,&q[i].r,&q[i].t);
  }
}

int check(){
  int ans1,ans2;
  for(int i = 1;i<=m;i++){
    fscanf(o1,"%d",&ans1),fscanf(o2,"%d",&ans2);
    double t1 = calv(p[ans1],q[i].t),t2 = calv(p[ans2],q[i].t);
    fprintf(a1,"%d:%lf %lf\n",i,t1,t2);
    if(t1 != t2)
      return 1;
  }
  return 0;
}

int main(){
  // file_open();
  // init();
  // int t = check();
  // fprintf(a1,"RESULT:%d\n",t);
  // file_close();
  // return t;
  return diff();
}