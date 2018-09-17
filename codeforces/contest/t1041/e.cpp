#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 210000;

struct T{
  int id,num;
  bool operator < (const T a)const{
    return id > a.id;
  }
};

int n;
int num[MAXN];
int times[MAXN];

int link[MAXN];

queue<int> q;
priority_queue<T> Q;
int u[MAXN],v[MAXN],cnt;

int main(){
  scanf("%d",&n);
  int a,b;
  for(int i = 1;i<=n-1;i++){
    scanf("%d %d",&a,&b);
    if(max(a,b)!=n){
      printf("NO\n");
      return 0;
    }
    else{
      num[i] = min(a,b);
      times[num[i]]++;
    }
  }
  for(int i = 1;i<=n-1;i++){
    if(times[i] == 0){
      q.push(i);
    }
    else{
      Q.push((T){i,times[i]});
    }
  }
  while(!Q.empty()){
    T now = Q.top();Q.pop();
    //printf("id:%d num:%d\n",now.id,now.num);
    int last = n;
    for(int i = 1;i<now.num;i++){
      if(q.empty() || q.front() > now.id){
        printf("NO\n");
        return 0;
      }
      else{
        int tmp = q.front();q.pop();
        u[++cnt] = last,v[cnt] = tmp;
        last = tmp;
      }
    }
    u[++cnt] = last,v[cnt] = now.id;
  }
  printf("YES\n");
  for(int i = 1;i<=cnt;i++){
    printf("%d %d\n",u[i],v[i]);
  }
  return 0;
}