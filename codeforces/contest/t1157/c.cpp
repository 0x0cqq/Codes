#include <bits/stdc++.h>
using namespace std;

const int MAXN = 210000;
int n;
int a[MAXN];

vector<int> ans;
string s;

int main(){
  scanf("%d",&n);
  for(int i = 1;i<=n;i++) scanf("%d",&a[i]);
  int last = 0,L = 1,R = n;
  while(L <= R){
    if(a[L] <= last && a[R] <= last) break;
    else if((a[L] > last)^(a[R] > last)){
      if(a[L] > last) ans.push_back(last = a[L]),s.push_back('L'),L++;
      else            ans.push_back(last = a[R]),s.push_back('R'),R--;
    }
    else if(a[L] > last && a[R] > last){  
      if(a[L] < a[R]) ans.push_back(last = a[L]),s.push_back('L'),L++;
      else if(a[L] > a[R]) ans.push_back(last = a[R]),s.push_back('R'),R--;
      else if(a[L] == a[R]){
        int ansa = 0,ansb = 0;
        for(int i = L+1;i<=R;i++) if(a[i] > a[i-1]) ansa++;else break;
        for(int i = R-1;i>=L;--i) if(a[i] > a[i+1]) ansb++;else break;
        if(ansa > ansb) ans.push_back(last = a[L]),s.push_back('L'),L++;
        else ans.push_back(last = a[R]),s.push_back('R'),R--;
      }
    }
  }
  printf("%d\n",int(ans.size()));
  cout << s << endl;
  return 0;
}