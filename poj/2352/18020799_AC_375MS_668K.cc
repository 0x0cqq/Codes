#include <cstdio>
#include <cstring>
#define lowbit(x) x&(-x)
using namespace std;

int n;
int tree[40001],level[40001];

void add(int nown){
	for(;nown<=40000;nown+=lowbit(nown))
		tree[nown]++;
}

int query(int nown){
	int res = 0;
	for(;nown>=1;nown-=lowbit(nown))
		res += tree[nown];
	return res;
}


int main(){
	while(scanf("%d",&n) == 1){
		memset(tree,0,sizeof(tree));
		memset(level,0,sizeof(level));
		for(int i = 1;i<=n;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			level[query(x+1)]++;
			//printf("%d\n",query(x+1));
			add(x+1);
		}
		for(int i = 0;i<n;i++){
			printf("%d\n",level[i]);
		}
	}	
	return 0;
}