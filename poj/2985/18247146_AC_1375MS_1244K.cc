#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 200010;

int f[MAXN],siz[MAXN];

int tree[MAXN<<1],t,n,m;



void init(){
	//printf("%d\n",n);
	t = 1;
	while(t<=n){
		t<<=1;
	}
	//printf("%d\n",t);
	for(int i = 1;i<=n;i++){
		f[i] = -1;
	}
}

void update(int nown,int d){
	for(int w = nown+t;w;w>>=1)
		tree[w]+=d;
}

int query(int k){
	int nown = 1;
	while(nown <= t){
		if(k<=tree[nown<<1|1]){
			nown = nown<<1|1;
		}
		else{
			k-=tree[nown<<1|1];
			nown = nown<<1;
		}
	}
	return nown-t;
}

int find(int x){
	return f[x] <= 0?x:f[x] = find(f[x]);
}


void solve(){
	scanf("%d %d",&n,&m);
	init();
	update(1,n);
	for(int i = 1;i<=m;i++){
		//for(int i = 1;i<=n;i++){
		//	printf("%d ",tree[t+i]);
		//}
		//putchar('\n');
		int op,a,b;
		scanf("%d",&op);
		if(op == 0){
			scanf("%d %d",&a,&b);
			int x = find(a),y = find(b);
			//printf("x:%d,f[x]:%d y:%d,f[y]:%d\n",x,f[x],y,f[y]);
			if(x == y){
				continue;
			}
			update(-f[x],-1);
			update(-f[y],-1);
			update(-(f[x]+f[y]),1);
			f[x] += f[y];
			f[y] = x;
		}
		else{
			scanf("%d",&a);
			printf("%d\n",query(a));
		}
	}
}


int main(){
	solve();
	return 0;
}