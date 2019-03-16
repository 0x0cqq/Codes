#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1000;

int f[MAXN];

int find(int x){
	if(f[x]<=0)
		return x;
	f[x] = find(f[x]);
	return f[x];
}

bool addedge(int a,int b){
	int x = find(a),y = find(b);
	if(x == y)
		return false;
	if(f[b]>0)
		return false;
	f[b] = a;
	f[a] = -1;
	return true;
}

bool solve(){
	int a,b;
	bool flag = 1;
	while(true){
		scanf("%d %d",&a,&b);
		if(a == 0&&b == 0)
			return flag;
		if(!addedge(a,b))
			flag = 0;
	}
}

void init(){
	static int ccc = 1;
	int a,b;
	while(true){
	memset(f,0,sizeof(f));
	scanf("%d %d",&a,&b);
	if(a == -1&&b == -1){
		return;
	}
	bool flag,ff1;
	if(a !=0 && b != 0){
		addedge(a,b);
		flag = solve(),ff1 = 0;
		for(int i = 1;i<MAXN;i++){
			if(f[i] == -1&&ff1 == 0)
				ff1 = 1;
			else if(f[i] == -1&&ff1)
				flag = 0;
		}
		if(ff1 == 0)
			flag = 0;
	}
	else{
		flag = 1;
	}
	if(flag){
		printf("Case %d is a tree.\n",ccc);
	}
	else{
		printf("Case %d is not a tree.\n",ccc);
	}
	ccc++;
	}
}

int main(){
	init();
	return 0;
}