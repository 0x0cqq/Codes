#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll n,k,w;
ll f[1000],g[1000],h[1000];

int main(){
	int t;
	scanf("%d",&t);
	for(int i = 1;i<=31;i++){
		f[i] = f[i-1] * 4 + 1;
	}
	g[1] = 1;
	for(int i = 2;i<=60;i++){
		g[i] = g[i-1] * 2 + 3;
	}
	for(int i = 1;i<=60;i++){
		h[i] = h[i-1] * 2 + 1;
	}
	for(int i = 1;i<=t;i++){
		scanf("%lld %lld",&n,&k);
		ll w = k;
		ll sqr = 0;
		for(int i = 1;i<=n;i++){
			//printf("%d:%lld\n",i,h[i]);
			if(w - h[i] >= 0){
				sqr++;
				w -= h[i];
			}
			else{
				break;
			}
		}
		
		bool flag = 0;
		//printf("w:%lld f:%lld\n",w,f[n]);
		if(n >= 32 || f[n-1] >= w){
			flag = 1;
		}
		else{
			ll ans = 0;
			for(int i = 1;i<=min(n,sqr);i++){
				//printf("%lld %lld\n",g[i],f[n-i]);
				ans += g[i] * f[n-i];
				if(ans >= w){
					flag = 1;
					break;
				}
			}
		}
		if(flag)
			printf("YES %lld\n",n-sqr);	
		else
			printf("NO\n");
	}
	return 0;
}