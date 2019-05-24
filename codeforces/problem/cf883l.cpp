#include <bits/stdc++.h>
#define int long long
#define ll long long
using namespace std;
template <typename T> bool chkmax(T &x,T y) { return x < y ? x = y , 1 : 0;}
template <typename T> bool chkmin(T &x,T y) { return y < x ? x = y , 1 : 0;}

const int MAXN = 210000;

int n,k,m;
int x[MAXN];
ll t[MAXN],ans[MAXN];int a[MAXN],b[MAXN];

struct Car{
  Car(int _id,ll _last):id(_id),last(_last){}
  int id;
  ll last;
  bool operator < (const Car &c)const{
    return last != c.last ? last < c.last : id < c.id;
  } 
};

struct Node{
  int id,pos;
  ll tim;
  bool operator < (const Node &c)const{
    return tim < c.tim;
  } 
};

multiset<Car> car[MAXN];
multiset<int> car_pos;
multiset<Node> w;

void add_car(int i,int pos,ll tim){
  car[pos].insert(Car(i,tim));
  car_pos.insert(pos);
}

void pop_wait(ll tim){
  // printf("size:w:%lld\n",int(w.size()));
  while(!w.empty() && w.begin()->tim <= tim){
    auto it = w.begin();
    // printf("add:%lld %lld %lld\n",it->id,it->pos,it->tim);
    add_car(it->id,it->pos,it->tim);
    w.erase(w.begin());
  }  
}

void init(){
  scanf("%lld %lld %lld",&n,&k,&m);
  for(int i = 1;i<=k;i++) scanf("%lld",&x[i]),w.insert({i,x[i],0});
}

void solve(){
  for(int i = 1;i<=m;i++) scanf("%lld %lld %lld",&t[i],&a[i],&b[i]);
  for(int i = 1;i<=m;i++){
    pop_wait(t[i]);
    // printf("size:%lld\n",int(car_pos.empty()));
    if(car_pos.empty()) pop_wait(w.begin()->tim);
    // find_car
    auto it = car_pos.lower_bound(a[i]);
    Car c(1e6,1e15);
    int pos,mind = 1e9;
    if(it != car_pos.end()){// 可以向后
      int tmpx = *it;
      if(chkmin(mind,abs(a[i]-tmpx)) || (mind == abs(a[i]-tmpx) && *car[tmpx].begin() < c)){
        c = *car[tmpx].begin();
        pos = tmpx;
      }
    }
    if(it != car_pos.begin()){// 可以向前
      int tmpx = *(--it);
      if(chkmin(mind,abs(a[i]-tmpx)) || (mind == abs(a[i]-tmpx) && *car[tmpx].begin() < c)){
        c = *car[tmpx].begin();
        pos = tmpx;
      }
    }
    printf("%lld %lld\n",c.id,max(c.last,t[i]) + mind - t[i]);
    car[pos].erase(car[pos].begin());
    car_pos.erase(car_pos.find(pos));
    // printf("car:%lld last:%lld mind:%lld pos:%lld tim:%lld\n",c.id,c.last,mind,b[i],max(c.last,t[i]) + mind + abs(a[i]-b[i]));
    w.insert({c.id,b[i],max(c.last,t[i]) + mind + abs(a[i]-b[i])});
  }
}

signed main(){
  init();
  solve();
  return 0;
}