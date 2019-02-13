#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int x,y,z;
int a,b,c;

signed main(){
  cin >> x >> y >> z  >> a >> b >> c;
  cout << (a >= x && a + b - x >= y && a + b + c - x - y >= z? "YES\n" : "NO")<< endl;
  return 0;
}