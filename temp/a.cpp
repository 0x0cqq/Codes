#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 210000;

int n;
int a[MAXN];
char s[MAXN];


int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	s[1] = 'a';
	for(int i = 2;i<=n;i++){
		if(a[i] == i){
      if(i!=2&&s[i-1] == 'a')
        s[i] = max(int(s[i]),int(s[2] + 1)); 
      s[i] = max(int(s[i]),int(s[(i-1)%a[i-1]+1]+1));
    }
		else{
			s[i] = s[i-a[i]];
		}
	}
	printf("%s\n",s+1);
	return 0;
}
