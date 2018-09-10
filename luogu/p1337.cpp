#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAXN = 2100;

double rnd(){
  return 2*(double)(rand())-RAND_MAX;
}

struct Point{
  double x,y;
  Point(double _x = 0,double _y = 0){x = _x,y = _y;}
  Point operator + (const Point &_a){
    return Point(x+_a.x,y+_a.y);
  }
}p[MAXN];
int n;
int w[MAXN];

inline double caldis(Point &_a,Point &_b){
  return sqrt((_a.x-_b.x)*(_a.x-_b.x)+(_a.y-_b.y)*(_a.y-_b.y));
}

inline double cal_energy(Point _p){
  double ans = 0;
  for(int i = 1;i<=n;i++)
    ans += caldis(_p,p[i])*w[i];
  return ans;
}

namespace simulate_annealing{
  double eps = 1e-14,T = 1e-2,D = 0.9993;
  void solve(Point &now,int times = 1){
    for(double t = T/times;t>=eps;t*=D){
      //printf("%.10lf\n",rnd());
      //printf("t:%6.6lf ",t);
      Point tmp = Point(now.x+t*rnd(),now.y+t*rnd());
      //printf("x:%.3lf y:%.3lf\n",tmp.x,tmp.y);
      double nowe = cal_energy(now),tmpe = cal_energy(tmp);
      if(tmpe <= nowe || exp((nowe-tmpe)/t)*RAND_MAX > rand()){
        now = tmp;
      }
    }
    // printf("%.3lf %.3lf\n",ans.x,ans.y);
    // printf("%.6lf\n",energy);
  }
  void output(Point ans){
    printf("%.3lf %.3lf\n",ans.x,ans.y);
    //printf("%.6lf\n",energy);
  }
}

void init(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++){
    scanf("%lf %lf %d",&p[i].x,&p[i].y,&w[i]);
  }
}

void solve(){
  Point now;
  for(int i = 1;i<=n;i++) now = now + p[i];
  now.x/=n,now.y/=n;
  //printf("%.3lf %.3lf\n",now.x,now.y);
  simulate_annealing::solve(now);
  // for(int i = 1;i<=10;i++){
  //   simulate_annealing::solve(now,(i+1)/2);
  // }
  simulate_annealing::output(now);
}

int main(){
  srand(time(NULL));
  init();
  solve();
  return 0;
}