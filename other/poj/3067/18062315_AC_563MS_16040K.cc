#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

int n,m,t,k;
ll tree[2000];

struct road{
	int l,r;
}ro[2000000];

bool cmp(road a,road b){
	if(a.l!=b.l)
		return a.l>b.l;
	return a.r>b.r;
}

int lowbit(int x){
    return x&(-x);
}

inline void add(int nown){
	for(int i = nown;i<=m;i+=lowbit(i))
		tree[i]++;
}

inline ll query(int nown){
	ll res = 0;
	for(int i = nown;i>0;i-=lowbit(i))
		res += tree[i];
	return res;
}

int main(){
	scanf("%d",&t);
	for(int w = 1;w<=t;w++){
		ll ans = 0;
		scanf("%d %d %d",&n,&m,&k);
		memset(ro,0,sizeof(ro));
		memset(tree,0,sizeof(tree));
		for(int i = 1;i<=k;i++)
			scanf("%d %d",&ro[i].l,&ro[i].r);
		sort(ro+1,ro+k+1,cmp);
		for(int i = 1;i<=k;i++){
			ans+=query(ro[i].r-1);
			add(ro[i].r);
		}
		printf("Test case %d: %lld\n",w,ans);
	}
	return 0;
}