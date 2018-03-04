#include <cstdio>
using namespace std;

const int MAXN = 110000;

int f[MAXN],n,m,t;
bool r[MAXN];

int find(int x){
	if(f[x] == x)
		return x;
	int w = find(f[x]);
	r[x] ^= r[f[x]];
	return f[x] = w;
}

int ask(int a,int b){
	int x = find(a),y = find(b);
	if(x == y)
		return r[a]^r[b];
	else
		return -1;
}

void un(int a,int b){
	int x = find(a),y = find(b);
	if(x == y){
		return;
	}
	else{
		f[x] = y;
		r[x] = r[a]^r[b]^1;
	}
}

void solve(){
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=n;i++){
		f[i] = i;
		r[i] = 0;
	}
	for(int i = 1;i<=m;i++){
		char op[20];int a,b;
		scanf("%s %d %d",op,&a,&b);
		if(op[0] == 'D'){
			un(a,b);
		}
		else if(op[0] == 'A'){
			int w = ask(a,b);
			if(w == 1){
				printf("In different gangs.\n");
			}
			else if(w == 0){
				printf("In the same gang.\n");
			}
			else{
				printf("Not sure yet.\n");
			}
		}
	}
}

int main(){
	int t;
	scanf("%d",&t);
	for(int i = 1;i<=t;i++){
		solve();
	}
	return 0;
}