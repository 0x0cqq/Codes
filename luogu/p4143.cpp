#include <cstdio>
#include <cmath>
#define ll long long
#define lson (nown<<1)
#define rson (nown<<1|1)
#define mid ((l+r)>>1)
using namespace std;

int n,m;

ll tree[500000];

void maintain(int nown){
	tree[nown] = tree[lson]+tree[rson];
}

void build(int nown,int l,int r){
	if(l == r)
		scanf("%lld",&tree[nown]);
	else{
		build(lson,l,mid);
		build(rson,mid+1,r);
		maintain(nown);
	}
} 

ll query(int nown,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return tree[nown];
	else{
		if(ql<=mid&&qr>=mid+1) return query(lson,l,mid,ql,qr)+query(rson,mid+1,r,ql,qr);
		else if(qr<=mid) return query(lson,l,mid,ql,qr);
		else if(ql>=mid+1) return query(rson,mid+1,r,ql,qr);
	}
}

void update(int nown,int l,int r,int ql,int qr){
	if(query(1,1,n,l,r) == r-l+1) return;
	if(l == r) tree[nown] = int(sqrt(tree[nown]));
	else{
		if(ql<=mid&&qr>=mid+1) update(lson,l,mid,ql,qr),update(rson,mid+1,r,ql,qr);
		else if(qr<=mid) update(lson,l,mid,ql,qr);
		else if(ql>=mid+1) update(rson,mid+1,r,ql,qr);
		maintain(nown);
	}
}

int main(){
	while(scanf("%d",&n) == 1){
		build(1,1,n);
		scanf("%d",&m);
		for(int i = 1;i<=m;i++){
			int op,a,b;
			scanf("%d %d %d",&op,&a,&b);
			if(a>b)
				a ^= b,b ^= a,a ^= b; 
			if(op == 0)
				update(1,1,n,a,b);
			else if(op == 1)
				printf("%lld\n",query(1,1,n,a,b));
		}
		putchar('\n');
	}
	return 0;
}