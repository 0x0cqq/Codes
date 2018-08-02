#include<algorithm>
#include<cstdio>
#include<cstring>
using std::swap;
const int N=1e6+5;
typedef int arr[N];
arr sa,rk;
void pre(char*s,int n){
	static arr cnt,v,q;
	int m=127;
	for(int i=0;i<m;++i) cnt[i]=0;
	for(int i=0;i<n;++i) ++cnt[s[i]];
	for(int i=1;i<m;++i) cnt[i]+=cnt[i-1];
	for(int i=n-1;~i;--i) sa[--cnt[s[i]]]=i;
	m=rk[sa[0]]=0;
	for(int i=1;i<n;++i) rk[sa[i]]=s[sa[i]]!=s[sa[i-1]]?++m:m;
	for(int j=1;;j<<=1){
		if(++m==n)break;
		for(int i=0;i<j;++i) v[i]=n-j+i;
		for(int i=0,k=j;i<n;++i)if(sa[i]>=j) v[k++]=sa[i]-j;
		for(int i=0;i<n;++i) q[i]=rk[v[i]];
		for(int i=0;i<m;++i) cnt[i]=0;
		for(int i=0;i<n;++i) ++cnt[q[i]];
		for(int i=1;i<m;++i) cnt[i]+=cnt[i-1];
		for(int i=n-1;~i;--i) sa[--cnt[q[i]]]=v[i],v[i]=rk[i];
		m=rk[sa[0]]=0;
		for(int i=1;i<n;++i) rk[sa[i]]=v[sa[i]]!=v[sa[i-1]]||v[sa[i]+j]!=v[sa[i-1]+j]?++m:m;
	}
}
struct buf{
	char e[1<<25],*p;
	buf():p(e){}
	~buf(){fwrite(e,1,p-e,stdout);}
	void out(int x){
		static char z[12];
		char*i=z;
		if(!x)*p++=48;
		else{
			while(x){
				int y=x/10;
				*i++=x-y*10+48,x=y;
			}
			while(i!=z)*p++=*--i;
		}
		*p++=32;
	}
}it;
int main(){
	static char s[N];
	int n=strlen(gets(s));
	pre(s,n+1);
	for(int i=1;i<=n;++i)
		it.out(sa[i]+1);
}