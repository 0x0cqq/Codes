#include <cstdio>
#include <cstring>
#include <bitset>
using namespace std;

const int MAXN = 710;

inline int gg(int a,int b){
	return b == 0?a:gg(b,a%b);
}

int n;
int gcd[MAXN][MAXN];
int a[MAXN];
bitset<MAXN> vis[MAXN][MAXN];
bitset<MAXN> vis2[MAXN][MAXN];

int search(int l,int r,int p){
	if(r < l) return 1;
	if(l == r)
		return gcd[l][p] > 1;
	if(vis2[l][r][p])
		return vis[l][r][p];
	for(int i = l;i<=r;i++){
		if(gcd[i][p] > 1){
			if(search(l,i-1,i) && search(i+1,r,i)){
				vis2[l][r][p] = 1;
				return vis[l][r][p] = 1;
			}
		}
	}
	vis2[l][r][p] = 2;
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			gcd[i][j] = gg(a[i],a[j]);
		}
	}
	for(int i = 1;i<=n;i++){
		gcd[0][i] = gcd[i][0] = 2;
	}
	int ans = search(1,n,0);
	if(ans == 1){
		printf("Yes\n");
		return 0;
	}
	printf("No\n");
	return 0;
}