#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	int r[MAXN],c[MAXN];
	for(int i = 1;i<=n;i++){
		scanf("%d",&r[i]);
	}
	for(int i = 1;i<=m;i++){
		scanf("%d",&c[i]);
	}
	int now = 1,ans = 0;
	for(int i = 1;i<=n && now <= m;i++){
		if(r[i] <= c[now])
			now++,ans++;
	}
	printf("%d\n",ans);
	return 0;
}