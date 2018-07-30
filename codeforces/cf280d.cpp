#include <cstdio>
using namespace std;

const int MAXN = 1100000;

double ans;
int n,u,v;
vector<int> edge[MAXN];

void dfs(int x,int fa = 0,int depth = 1){
	ans += 1/double(depth);
	for(int i = 0;i<edge[x].size();i++){
		int v = edge[x][i];
		if(v == fa) continue;
		dfs(v,x,depth+1);
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n-1;i++){
		scanf("%d %d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs1(1);
	printf("%.10lf\n",ans);
	return 0;
}