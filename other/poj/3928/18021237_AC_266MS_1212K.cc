#include <cstdio>
#include <cstring>
#define lowbit(x) ((x)&(-(x)))
using namespace std;

int n;
int t_b[100010],t_e[100010],neng[20010];

void add(int nown,int addn,bool opt){
	for(;nown<=100009;nown+=lowbit(nown)){
		if(opt)
			t_b[nown]+=addn;
		else
			t_e[nown]+=addn;
	}
}

int query(int nown,bool opt){
	int res = 0;
	for(;nown>=1;nown-=lowbit(nown))
		if(opt)
			res += t_b[nown];
		else
			res += t_e[nown];
	return res;
}


int main(){
	int t;
	scanf("%d",&t);
	for(int j = 1;j<=t;j++){
		scanf("%d",&n);
		long long res = 0;
		memset(t_b,0,sizeof(t_b));
		memset(t_e,0,sizeof(t_e));
		memset(neng,0,sizeof(neng));
		for(int i = 1;i<=n;i++){
			scanf("%d",&neng[i]);
			add(++neng[i],1,0);
		}
		/*for(int i = 1;i<=10;i++){
			printf("i:%d num:%d\n",i,query(i,0));
		}*/
		for(int i = 1;i<=n;i++){
			//printf("%d:%d\n",i,neng[i]);
			add(neng[i],-1,0);
			//printf("%d %d\n",query(neng[i]-1,1),query(neng[i],0));
			res += query(neng[i]-1,1)*(n-i-query(neng[i],0));
			//printf("%d %d\n",query(neng[i],1),query(neng[i]-1,0));
			res += (i-query(neng[i],1)-1)*query(neng[i]-1,0);
			add(neng[i],1,1);
		}
		printf("%lld\n",res);
	}	
	return 0;
}