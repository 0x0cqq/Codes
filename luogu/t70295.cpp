#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 1e7;

ll l,r,T,n;
char s[MAXN];

pair<__int128,int> getnum(){
  if(s[0] == '-'){
    if(n == 1){
      return make_pair(0,1);
    }
    for(int i = 1;i<=1;i++){
      if('1' <= s[i] && s[i] <= '9') continue;
      else                           return make_pair(0,1);
    }
    for(int i = 2;i<n;i++){
      if('0' <= s[i] && s[i] <= '9') continue;
      else                           return make_pair(0,1);
    }
    __int128 ans = 0;
    for(int i = 1;i<n;i++){
      ans = ans * 10 + int(s[i] - '0');
      if(ans > 1e19) return make_pair(-2e19,0);
    }  
    return make_pair(-ans,0);
  }
  else{
    if(n == 1 && s[0] == '0') return make_pair(0,0);
    for(int i = 0;i<=0;i++){
      if('1' <= s[i] && s[i] <= '9') continue;
      else                           return make_pair(0,1);
    }
    for(int i = 1;i<n;i++){
      if('0' <= s[i] && s[i] <= '9') continue;
      else                           return make_pair(0,1);
    }  
    __int128 ans = 0;
    for(int i = 0;i<n;i++){
      ans = ans * 10 + int(s[i] - '0');
      if(ans > 1e19) return make_pair(-2e19,0);
    }  
    return make_pair(ans,0);
  }

}

int main(){
  cin >> l >> r >> T;
  for(int i = 1;i<=T;i++){
    scanf("%s",s);n = strlen(s);
    auto t = getnum();
    // cout << (ll)(t.first) << endl;
    if(t.second == 1)
      printf("1\n");
    else if(t.first < -1e19)
      printf("2\n");
    else if(l <= (ll)(t.first) && (ll)(t.first) <= r)
      printf("0\n");
    else
      printf("2\n");
  }
  return 0;
}