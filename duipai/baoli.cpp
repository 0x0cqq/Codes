#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2100;

int n,k;
char s[MAXN][MAXN];

int _hash(int i,int j){
	if(i > n || j > n || i <= 0 || j <= 0){
		return -1;
	}
	return (i-1)*n + j;
}

struct Edge{
    int to,len,nex;
}edge[MAXN*MAXN*2];int ecnt = 2;
int fir[MAXN*MAXN];
void addedge(int u,int v,int c){
	if(u == -1 || v == -1)
		return;
	//printf("%d %d %d\n",u,v,c);
    edge[ecnt] = (Edge){v,c,fir[u]};
    fir[u] = ecnt++;
}



struct Node{
    int x,d;
    bool operator < (const Node &_n)const{
        return d > _n.d;
    }
};

int ss;
priority_queue<Node> q;
int vis[MAXN*MAXN],dis[MAXN*MAXN];

void dij(){
    while(!q.empty()) q.pop();
    memset(dis,0x3f,sizeof(dis));
    dis[ss] = 0;
    q.push((Node){ss,0});
    while(!q.empty()){
        Node now = q.top();q.pop();
        int nown = now.x,nowd = now.d;
        if(vis[nown]) continue;
        vis[nown] = 1;
        dis[nown] = nowd;
        for(int nowe = fir[nown];nowe;nowe = edge[nowe].nex){
            int v = edge[nowe].to,l = edge[nowe].len;
            if(dis[v] > nowd + l){
                dis[v] = nowd+l;
                q.push((Node){v,nowd+l});
            }
        }
    }
//    for(int i = 1;i<=n*n;i++){
//        if(dis[i] <= 1e9){
//            printf("%d ",dis[i]);
//        }
//        else{
//            printf("%d ",2147483647);
//        }
//    }
}



struct NN{
	int x,a,b;
	bool operator < (const NN &w)const{
		if(a == w.a){
			return b < w.b;
		}
		else{
			return a < w.a;
		}
	}
	bool operator == (const NN &w)const{
		return a == w.a && b == w.b;
	}
};

vector<NN> tt;
int nex[MAXN][MAXN];
int rnk[MAXN][MAXN];

void solve(){
	for(int i = 2*n;i>=1;i--){
		tt.clear();
		for(int x = 1;x <= n && i-x >= 1;x++){
			int y = i-x;
			if(y > n) continue;
			int minn = 0x3f3f3f3f;
			if(x + 1 <= n){
				if(rnk[x+1][y] < minn){
					nex[x][y] = 1;
				}
				minn = min(minn,rnk[x+1][y]);
			}
			if(y + 1 <= n){
				if(rnk[x][y+1] < minn){
					nex[x][y] = 2;
				}
				minn = min(minn,rnk[x][y+1]);
			}
			tt.push_back((NN){x,int(s[x][y]),minn});
		}
		sort(tt.begin(),tt.end());
		int cnt = -1;
		for(int r = 0;r<tt.size();r++){
			//printf("r:%d x:%d a:%d b:%d\n",r,tt[r].x,tt[r].a,tt[r].b);
			if(r == 0 || !(tt[r] == tt[r-1])) cnt++;
			rnk[tt[r].x][i-tt[r].x] = cnt;
		}
	}
//	printf("rnk:\n");
//	for(int i = 1;i<=n;i++){
//		for(int j = 1;j<=n;j++){
//			printf("%d ",rnk[i][j]);
//		}
//		printf("\n");
//	}
}


int main(){
	scanf("%d %d",&n,&k);
	for(int i = 1;i<=n;i++){
		scanf("%s",s[i] + 1);
	}
//	printf("s:\n");
//	for(int i = 1;i<=n;i++){
//		printf("%s\n",s[i] + 1);
//	}
	ss = 0;
	addedge(ss,_hash(1,1),s[1][1] == 'a' ? 0 : 1);
	for(int i = 1;i<=n;i++){
		for(int j = 1;j<=n;j++){
			int l = s[i][j] == 'a' ? 0 : 1;
			addedge(_hash(i,j-1),_hash(i,j),l);
			addedge(_hash(i-1,j),_hash(i,j),l);
		}
	}
	dij();
	solve();
	
	for(int i = 2*n;i>=2;i--){
		bool flag = 1;
		for(int j = 1;j <= n && i-j >= 1;j++){
			int x = j,y = i-j;
			if(x > n || y > n){
				continue;
			}
			//printf("%d %d\n",x,y);
			if(dis[_hash(x,y)] <= k){
				flag = 0;
				break;
			}
		}
		if(flag == 1) continue;
		int minpos = n,minn = 0x3f3f3f3f;
		for(int x = 1;x <= n && i-x >= 1;x++){
			int y = i - x;
			if(x > n || y > n) continue;
			if(dis[_hash(x,y)] <= k){
				if(x+1 <= n && rnk[x+1][y] < minn){
					minpos = x,minn = rnk[x+1][y];
				}
				if(y+1 <= n && rnk[x][y+1] < minn){
					minpos = x,minn = rnk[x][y+1];
				}
			}
		}
		//printf("i:%d\n",i);
		for(int w = 1;w<i;w++){
			putchar('a');
		}
		int nowx = minpos,nowy = i-minpos;
		while(nowx != n || nowy != n){
			//printf("nowx:%d nowy:%d\n",nowx,nowy);
			//system("pause");
			int nexx = nex[nowx][nowy];
			if(nexx == 1)
				nowx++;
			else if(nexx == 2)
				nowy++;
			putchar(s[nowx][nowy]);
		}
		printf("\n");
		return 0;
	}
	putchar(s[1][1]);
		int nowx = 1,nowy = 1;
		while(nowx != n || nowy != n){
			//printf("nowx:%d nowy:%d\n",nowx,nowy);
			//system("pause");
			int nexx = nex[nowx][nowy];
			if(nexx == 1)
				nowx++;
			else if(nexx == 2)
				nowy++;
			putchar(s[nowx][nowy]);
		}
		printf("\n");
	return 0;
}