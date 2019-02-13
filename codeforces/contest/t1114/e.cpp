#include <bits/stdc++.h>
// #include <cstdlib>
using namespace std;

int n,times;

int query(int x){
  times++;
  cout << "> " << x << endl;
  int ans = -1;
  cin >> ans;
  return ans;
}

int pos(int x){
  times++;
  cout << "? " << x << endl;
  int ans = -1;
  cin >> ans;
  return ans;
}

int main(){
  cin >> n;
  int L = 0,R = 1e9;
  while(L!=R){
    int mid = (L+R)/2;
    if(query(mid)){
      L = mid + 1;
    }
    else{
      R = mid;
    }
  } 
  srand(time(0));
  int G = 0;
  vector<int> v;
  v.push_back(L);
  while(times <= 59){
    v.push_back(pos((1LL * rand() * rand())%n+1));
  }
  sort(v.begin(),v.end());
  for(unsigned i = 1;i < v.size();i++){
    G = __gcd(G,v[i]-v[i-1]);
  }
  cout << "! " << L - G*(n-1) << " " << G << endl;
  return 0;
}