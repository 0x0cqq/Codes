#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110000;
int n;
string s[MAXN];
int len[MAXN][2];
int maxn[MAXN][26];

void init(){
  cin >> n;
  for(int i = 1;i<=n;i++){
    cin >> s[i];
    for(int x = 0;x < s[i].length();x++){
      s[i][x] = s[i][x] - 'a';
    } 
  }
  for(int x = 1;x<=n;x++){
    for(int i = 0;i <= s[x].length();i++){
      if(i == s[x].length() || s[x][i] != s[x].front()){len[x][0] = i;break;}
    }
    for(int i = s[x].length()-1;;--i){
      if(i == -1 || s[x][i] != s[x].back()){len[x][1] = s[x].length()-i-1;break;}
    }
  }
  for(int x = 1;x<=n;x++){
    int last = 0;
    for(int i = 1;i <= s[x].length();i++){
      if(i == s[x].length() || s[x][i] != s[x][i-1]){
        maxn[x][s[x][i-1]] = i-last,last = i;
      }
    }
  }
  // for(int i = 1;i<=n;i++){
  //   printf("%d:%d %d\n",i,len[i][0],len[i][1]);
  //   for(int x = 0;x<26;x++){
  //     if(maxn[i][x]) printf("    %d:%d\n",x,maxn[i][x]);
  //   }
  // }
}

int nowmaxn[26],newmaxn[26];

void solve(){  
  int ans = 0;
  for(int x = 0;x<26;x++) nowmaxn[x] = maxn[1][x];
  // for(int x = 0;x<26;x++) {printf("  %c",x+'a');}printf("\n");
  for(int i = 2;i<=n;i++){
    // for(int x = 0;x<26;x++) {printf("%3d",nowmaxn[x]);}printf("\n");
    if(len[i][0] == s[i].length()){
      if(nowmaxn[s[i].front()])
        newmaxn[s[i].front()] = (nowmaxn[s[i].front()]+1) * (s[i].length()+1) - 1;
      else
        newmaxn[s[i].front()] = s[i].length();
    }
    else{
      
      if(s[i].front() == s[i].back()){
        if(nowmaxn[s[i].front()])
          newmaxn[s[i].front()] = len[i][0] + len[i][1] + 1;
        else
          newmaxn[s[i].front()] = max(len[i][0],len[i][1]);
      }
      else{
        newmaxn[s[i].front()] = len[i][0] + (nowmaxn[s[i].front()]?1:0);
        newmaxn[s[i].back()] = len[i][1] + (nowmaxn[s[i].back()]?1:0);
      }
    }
    for(int x = 0;x < 26;x++)if(x != s[i].front() && x != s[i].back()){
      newmaxn[x] = max(nowmaxn[x]?1:0,maxn[i][x]);
    }
    memcpy(nowmaxn,newmaxn,sizeof(newmaxn));
  }
  for(int x = 0;x<26;x++) ans = max(ans,nowmaxn[x]);
  // for(int x = 0;x<26;x++) {printf("%3d",nowmaxn[x]);}printf("\n");

  printf("%d\n",ans);
}



int main(){
  init();
  solve();
  return 0;
}