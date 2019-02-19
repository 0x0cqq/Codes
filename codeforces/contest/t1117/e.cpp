#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXN = 210000;

int n;
char s[MAXN],Q[MAXN],A[4][MAXN];
int ans[MAXN];

vector<int> S[30];
vector<int> SS[30][30];
int SSS[30][30][30];

char get(int pos,int c){// c == 1,2,3
	for(int i = 0;i<(3-c);i++) pos /= 26;
	return pos % 26 + 'a';
}

void init(){
	scanf("%s",s);n = strlen(s);
	// 3 次询问 每次二十六分答案
	// 考虑 (i/26/26) % 26 + 'a', (i/26) % 26 + 'a',i % 26 + 'a' 
	for(int x = 1;x<=3;x++){
		for(int i = 0;i<n;i++) Q[i] = get(i,x);	
		printf("? %s\n",Q);
		fflush(stdout);
		scanf("%s",A[x]);
//		printf("%s\n",A[x]);
	}
}


int get(int x,int y,int z){
//	printf("%d %d %d\n",x,y,z);
	return x * 26 * 26 + y * 26 + z;
}

void solve(){
	for(int i = 0;i<n;i++){
		ans[get(A[1][i]-'a',A[2][i]- 'a',A[3][i] - 'a')] = i;
	}
	
	printf("! ");
	for(int i = 0;i<n;i++){
//		printf("i:%d ans:%d\n",i,ans[i]);
		putchar(s[ans[i]]);
	}
	printf("\n");fflush(stdout);
}

int main(){
	init();
	solve();
	return 0;
}
