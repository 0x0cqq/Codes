#include <bits/stdc++.h>
#define ui unsigned 
using namespace std;

ui n,st;
string s,t;

int main(){
  cin >> s;n = s.length();

  s = s+s;
  for(ui i = 1;i<s.length();i++){
    if(s[i] != s[i-1]){st = i;break;}
  }
  s = s.substr(st,n);
  int ans = 0;
  for(ui i = 0;i < s.length();){
    for(ui j = i+1;;j++){
      if(j == s.length() || s[j] != s[i]){
        t.push_back(j - i == 1?'1':'2');
        i = j;
        break;
      }
    }
  }
  int M = t.length();
  t = t + t;
  for(int i = 1;i<=M;i++){
    if(i == M || t[i] != t[i-1]){
      t = t.substr(i,M);
      break;
    }
  }
  for(ui i = 0;i<t.length();){
    for(ui j = i+1;;j++){
      if(j == t.length() || t[j] != t[i]){
        ans += (j-i) / (t[i]=='1'?2:1);
        i = j;
        break;
      }
    }
  }
  cout << ans << endl;
  return 0;
}