#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 310000;

int n,m,d;
struct T{
  int id,num;
  bool operator < (const T a)const{
    return num < a.num;
  }
  bool operator > (const T a)const{
    return num > a.num;
  }  
}t[MAXN];


int day = 1;
int ans[MAXN];

priority_queue<T,vector<T>,greater<T> > q;

int main(){
  scanf("%d %d %d",&n,&m,&d);
  for(int i = 1;i<=n;i++){
    scanf("%d",&t[i].num);
    t[i].id = i;
  }
  sort(t+1,t+n+1);
  // for(int i = 1;i<=n;i++){
  //   printf("%d:%d\n",t[i].id,t[i].num);
  // }
  q.push((T){1,-0x3f3f3f3f});
  for(int i = 1;i<=n;i++){
    //printf("%d\n",i);
    if(q.empty()){
      day++;
      q.push((T){day,t[i].num});
      ans[t[i].id] = day;      
    }
    else{
      T now = q.top();q.pop();
      //printf("id:%d num:%d\n",now.id,now.num);
      if(now.num >= t[i].num - d){// tiaojian 
        //printf("op:1\n");
        q.push(now);
        day++;
        q.push((T){day,t[i].num});
        ans[t[i].id] = day;
      }
      else{
        //printf("op:2\n");
        ans[t[i].id] = now.id;
        q.push((T){now.id,t[i].num});
      }
    }
  }
  printf("%d\n",day);
  for(int i = 1;i<=n;i++){
    printf("%d ",ans[i]);
  }
  printf("\n");
  return 0;
}