#include <cstdio>
#include <vector>
using namespace std;

vector<int> ans;

int n;

void calc(int x,int d){
  if(x == 1){
    ans.push_back(d);
    return;
  }
  if(x == 2){
    ans.push_back(d);
    ans.push_back(2*d);
    return;
  }
  if(x == 3){
    ans.push_back(d);
    ans.push_back(d);
    ans.push_back(3*d);
    return;
  }
  int w = (x+1)/2;
  for(int i = 1;i<=w;i++){
    ans.push_back(d);
  }
  calc(x/2,d*2);
}

int main(){
  scanf("%d",&n);
  calc(n,1);
  for(unsigned i = 0;i<ans.size();i++){
    printf("%d ",ans[i]);
  }
  printf("\n");
  return 0;
}