#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 1000,sigma_size = 26;

namespace AC{
  int c[MAXN][sigma_size],end[MAXN],f[MAXN],root,cnt;
  void insert(char *s){
    int n = strlen(s),nown = root;
    for(int i = 0;i<n;i++){
      if(c[nown][s[i]-'a'] == 0)
        c[nown][s[i]-'a'] = ++cnt;
      nown = c[nown][s[i]-'a'];
    }
    end[nown] |= 1;
  }
  void get_fail(){
    queue<int> q;
    for(int i = 0;i<sigma_size;i++){
      if(c[root][i]){
        f[c[root][i]] = root;
        q.push(c[root][i]);
      }
    }
    while(!q.empty()){
      int nown = q.front();q.pop();
      for(int i = 0;i<sigma_size;i++){
        if(c[nown][i] == 0){
          c[nown][i] = c[f[nown]][i];
        }
        else{
          f[c[nown][i]] = c[f[nown]][i];
          end[c[nown][i]] |= end[f[c[nown][i]]];
          q.push(c[nown][i]);
        }
      }
    }
  }
  
}



void init(){

}

int main(){
  return 0;
}