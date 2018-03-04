#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 50000;

int n,m;
vector<int> qwq;

set<int> mmm;

struct query{
	int a,b;
	bool r;
}q[MAXN];

int lll[MAXN];

int f[MAXN];
bool r[MAXN];//1代表相差为奇数

int find(int x){
	if(f[x] == x){
		return x;
	}
	int w = find(f[x]);
	r[x] ^= r[f[x]];
	return f[x] = w; 
}

bool un(int a,int b,bool re){
	int x = find(a),y = find(b);
	if(x!=y){
		f[x] = y;
		r[x] = re^r[a]^r[b];
		return true;
	}
	else{
		return r[a]^r[b] == re;
	}
}

void init(){
	scanf("%d %d",&n,&m);
	char op[20];
	for(int i = 1;i<=m;i++){
		scanf("%d %d",&q[i].a,&q[i].b);
		q[i].b++;
		if(!mmm.count(q[i].a))
			qwq.push_back(q[i].a);
		if(!mmm.count(q[i].b))
			qwq.push_back(q[i].b);
		mmm.insert(q[i].a),mmm.insert(q[i].b);
		scanf("%s",op);
		q[i].r = (op[0] == 'o');
	}
	sort(qwq.begin(),qwq.end());
	for(int i = 0;i<qwq.size();i++){
		lll[i] = qwq[i]; 
	}
	for(int i = 1;i<=m;i++){
		int x = lower_bound(lll,lll+qwq.size(),q[i].a)-lll+1;
		int y = lower_bound(lll,lll+qwq.size(),q[i].b)-lll+1;
		//printf("%d %d %d\n",x,y,q[i].r);
		q[i].a = x;
		q[i].b = y;
	}
}


void solve(){
    for(int i = 1;i<=qwq.size()+100;i++)
		f[i] = i,r[i] = 0;
	for(int i = 1;i<=m;i++){
		if(!un(q[i].a,q[i].b,q[i].r)){
			printf("%d\n",i-1);
			return;
		}
	}
	printf("%d\n",m);
}

int main(){
	init();
	solve();
	return 0;
}