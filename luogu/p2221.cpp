#include <bits/stdc++.h>
#define gcd __gcd
#define ll long long
using namespace std;

const int MAXN = 110000;

namespace SegTree{
	//0->sigma(w_i),1->sigma(i*w_i),2->sigma(i^2*w_i)
	struct node{
		ll sum[3];
		node(ll _a = 0,ll _b = 0,ll _c = 0){
			sum[0] = _a,sum[1] = _b,sum[2] = _c;
		}
		node operator + (const node &a)const{
			node newnode;
			newnode.sum[0] = sum[0] + a.sum[0];
			newnode.sum[1] = sum[1] + a.sum[1];
			newnode.sum[2] = sum[2] + a.sum[2];
			return newnode;
		}
	}sumn[MAXN];
	ll tag[MAXN<<2];
	#define lson (nown<<1)
	#define rson (nown<<1|1)
	#define mid ((l+r)>>1)
	inline void build(int nown,int l,int r){
		;
	}
	inline ll cal(int n){
		return 1LL*n*(n+1)*(2*n+1)/6;
	}
	inline void addtag(int nown,int l,int r,ll v){
		tag[nown] += v;
		static node tmp;
		tmp = node(v*(r-l+1),v*(l+r)*(r-l+1)/2,v*(cal(r)-cal(l-1)));
		sumn[nown] = sumn[nown] + tmp;
	}
	inline void push_down(int nown,int l,int r){
		if(tag[nown]){
			addtag(lson,l,mid,tag[nown]),addtag(rson,mid+1,r,tag[nown]);
			tag[nown] = 0;
		}
	}
	inline void push_up(int nown){
		sumn[nown] = sumn[lson] + sumn[rson];
	}
	inline void update(int nown,int l,int r,int ql,int qr,int v){
		if(ql <= l && r <= qr){
			addtag(nown,l,r,v);
		}
		else{
			push_down(nown,l,r);
			if(ql <= mid) update(lson,l,mid,ql,qr,v);
			if(qr >= mid+1) update(rson,mid+1,r,ql,qr,v);
			push_up(nown);
		}
	}
	inline node query(int nown,int l,int r,int ql,int qr){
		if(ql <= l && r <= qr){
			return sumn[nown];
		}
		else{
			push_down(nown,l,r);
			node ans;
			if(ql <= mid) ans = ans + query(lson,l,mid,ql,qr);
			if(qr >= mid+1) ans = ans + query(rson,mid+1,r,ql,qr);
			return ans;
		}
	}
	void print(int nown,int l,int r,int depth = 0){
		for(int i = 0;i<depth;i++) putchar(' ');
		printf("%d: l:%d r:%d 0:%lld 1:%lld 2:%lld tag:%lld\n",nown,l,r,sumn[nown].sum[0],sumn[nown].sum[1],sumn[nown].sum[2],tag[nown]);
		if(l == r) return;
		print(lson,l,mid,depth+1);
		print(rson,mid+1,r,depth+1);
	}
}

int n,m;

void update(int l,int r,int v){
	SegTree::update(1,1,n,l,r-1,v);
}

void query(int l,int r,ll &x,ll &y){
	SegTree::node tmp = SegTree::query(1,1,n,l,r-1);
	x = -1LL*r*(l-1)*tmp.sum[0] + 1LL * (r+l-1)*(tmp.sum[1]) - tmp.sum[2];
	y = 1LL*(r-l+1)*(r-l)/2;
	ll d = gcd(x,y);
	x/=d,y/=d;
} 

void init(){
	scanf("%d %d",&n,&m);
}

void solve(){
	ll x, y;
	for(int i = 1;i<=m;i++){
		char op[10];int l,r,c;
		scanf("%s %d %d",op,&l,&r);
		if(op[0] == 'C'){
			scanf("%d",&c),update(l,r,c);
		}
		else{
			query(l,r,x,y);
			printf("%lld/%lld\n",x,y);
		}
		//SegTree::print(1,1,n);
	}
}

int main(){
	init();
	solve();
	return 0;
}