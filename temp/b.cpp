#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1110000;

namespace fast_io {
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

namespace Suffix_Array{
int s[MAXN],sa[MAXN],rk[MAXN],ht[MAXN],x[MAXN],y[MAXN];
int cnt[MAXN];
void get_sa(int n,int m){
  printf("%d %d\n",n,m);
	for(int i = 0;i<m;i++) cnt[i] = 0;
	for(int i = 0;i<n;i++) cnt[s[i]]++;
	for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
	for(int i = n-1;~i;--i) sa[--cnt[s[i]]] = i;
	m = rk[sa[0]] = 0;
	for(int i = 1;i<n;i++) rk[sa[i]] = s[sa[i]] != s[sa[i-1]] ? ++m: m;
	for(int j=1;;j<<=1){
		if(++m == n) break;
		for(int i = 0;i<j;i++) y[i] = n-j+i;
		for(int i = 0,k=j;i<n;i++) if(sa[i] >= j) y[k++] = sa[i]-j;
		for(int i = 0;i<n;i++) x[i] = rk[y[i]];
		for(int i = 0;i<m;i++) cnt[i] = 0;
		for(int i = 0;i<n;i++) cnt[x[i]]++;
		for(int i = 1;i<m;i++) cnt[i] += cnt[i-1];
 		for(int i = n-1;~i;--i) sa[--cnt[x[i]]] = y[i],y[i] = rk[i];
 		m = rk[sa[0]] = 0;
 		for(int i = 1;i<n;i++) rk[sa[i]] =(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+j]!=y[sa[i-1]+j])?++m:m;
	 }
}
template<typename T>
int mapCharToInt(int n,const T *str){
	// int m = *max_element(str,str+n);
	// for(int i = 0;i<=m;i++) rk[i] = 0;
	// for(int i = 0;i<n;i++) rk[int(str[i])] = 1;
	// for(int i = 1;i<=m;i++) rk[i] += rk[i-1];
	// for(int i = 0;i<n;i++) s[i] = rk[int(str[i])]-1;
	// return rk[m];
  return 0;
}
void getheight(int n){
    for(int i = 0,h = ht[0] = 0;i<n;i++){
        int j = sa[rk[i]-1];
        while(i+h < n && j+h < n && s[i+h] == s[j+h]) ++h;
        ht[rk[i]] = h;
        if(h) --h;
    }
}
void build(int n,const char *str){
	int m = 127;
  for(int i = 0;i<n;i++){
    s[i] = str[i] - 'a' + 1;
  }
  n++;
  s[n] = 0;
  for(int i = 0;i<n;i++){
    printf("%d ",s[i]);
  }
  printf("\n");
	get_sa(n,m);
	getheight(n);
}
}


int main(){
	static char s[MAXN];
	scanf("%s",s);
	int n = strlen(s);
	s[n] = 0;
	Suffix_Array::build(n,s);
	for(int i = 1;i<=n;i++){
		print(Suffix_Array::sa[i]),print(' ');
	}
	print('\n');
	for(int i = 1;i<=n;i++){
		print(Suffix_Array::ht[i]),print(' ');
	}
	flush();
	return 0;
}