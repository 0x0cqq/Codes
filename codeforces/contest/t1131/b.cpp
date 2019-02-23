#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN],b[MAXN];

int g(int x1,int y1,int x2,int y2){
	return max(min(y1,y2) - max(x1,x2)+1LL,0LL);
}

signed main() {
	cin >> n;
	int nowa = -1,nowb = 0,ans = 0;
  a[0] = -1;
  for(int i = 1;i<=n;i++){
		cin >> a[i] >> b[i];
    int flag = 0;
    if(a[i-1] == a[i] && b[i-1] == b[i]) continue;
    while(nowa < nowb && nowa <= a[i]){
      nowa++;flag = 1;
    }
    while(nowb < nowa && nowb <= b[i]){
      nowb++;flag = 1;
    }
    ans += max(0LL,min(a[i],b[i])-nowa+flag);
    nowa = a[i],nowb = b[i];
    // cout << ans << endl;
	}
	cout << ans << endl;
	return 0 ;
}