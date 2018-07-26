#include <cstdio>
#include <deque>
using namespace std;

const int MAXN = 20000;

int n;
int sum[MAXN],dis[MAXN];
int tot;

double cal(int j,int k){// 连接 j 和 k 两点的斜率
	//x_i sum[i],y_i sum[i] * dis[i]
	return double(sum[j]*dis[j] - sum[k]*dis[k])/(sum[j]-sum[k]); 
}

int calt(int i,int j){//i > j
	return tot - sum[j]*dis[j] - (sum[i] - sum[j])*dis[i];
}

void solve(){
	// front 为最优值，push 从 back 进入
	static int q[MAXN],fi,la;
	// [fi,la]
	int ans = 2147483647;
	for(int i = 1;i<=n;i++){
		while(fi < la && cal(q[fi],q[fi+1]) > dis[i]) fi++;
		// 这个地方相当于sum[0] = 0，不会对结果产生影响
		ans = min(ans,calt(i,q[fi]));//i > q[fi]
		while(fi < la && cal(q[la-1],q[la]) < cal(q[la],i)) --la;
		q[++la] = i;
	}
	printf("%d\n", ans);
}

void init(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
		scanf("%d %d",&sum[i],&dis[i]);
	for(int i = n;i>=1;--i) dis[i] += dis[i+1];
	for(int i = 1;i<=n;i++) tot += sum[i] * dis[i],sum[i] += sum[i-1];
}

int main(){
	init();
	solve();
	return 0;
}