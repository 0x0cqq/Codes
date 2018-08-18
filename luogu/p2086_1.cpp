#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define enter putchar('\n')
#define space putchar(' ')
#define MAXN 500005
//#define ivorysi
using namespace std;
typedef long long int64;
template<class T>
void read(T &res) {
    res = 0;char c = getchar();T f = 1;
    while(c < '0' || c > '9') {
	if(c == '-') f = -1;
	c = getchar();
    }
    while(c >= '0' && c <= '9') {
	res = res * 10 - '0' + c;
	c = getchar();
    }
    res = res * f;
}
template<class T>
void out(T x) {
    if(x < 0) {x = -x;putchar('-');}
    if(x >= 10) out(x / 10);
    putchar('0' + x % 10);
}

int N,M,X,Y,T,Rt,Ncnt,tot;
int64 D[MAXN],V,A[MAXN],num[MAXN];
struct Matrix {
    int X1,X2,Y1,Y2;
}MK[15];
struct node {
    int lc,rc,rt;
    int64 G;
}tr[MAXN * 70];
int64 gcd(int64 a,int64 b) {
    return b == 0 ? a : gcd(b,a % b);
}
int c(int x,int y) {
    return (x - 1) * M + y;
}

void update(int u) {
    tr[u].G = gcd(abs(tr[tr[u].lc].G),abs(tr[tr[u].rc].G));
}
void build(int& u,int t,int L,int R) {
    u = ++Ncnt;
    if(L == R) {
	tr[u].G = D[c(t,L)];
	return;
    }
    int mid = (L + R) >> 1;
    build(tr[u].lc,t,L,mid);
    build(tr[u].rc,t,mid + 1,R);
    update(u);
}
void Union(int &u,int Lu,int Ru,int L,int R) {
    u = ++Ncnt;
    if(L == R) {
	tr[u].G = gcd(abs(tr[Lu].G),abs(tr[Ru].G));
	return;
    }
    int mid = (L + R) >> 1;
    Union(tr[u].lc,tr[Lu].lc,tr[Ru].lc,L,mid);
    Union(tr[u].rc,tr[Lu].rc,tr[Ru].rc,mid + 1,R);
    update(u);
}
void Build(int &u,int L,int R) {
    u = ++Ncnt;
    if(L == R) {
	build(tr[u].rt,L,1,M);
	return;
    }
    int mid = (L + R) >> 1;
    Build(tr[u].lc,L,mid);
    Build(tr[u].rc,mid + 1,R);
    Union(tr[u].rt,tr[tr[u].lc].rt,tr[tr[u].rc].rt,1,M);
}
void modify(int u,int L,int R,int p,int64 v) {
    if(L == R) {tr[u].G += v;return;}
    int mid = (L + R) >> 1;
    if(p <= mid) modify(tr[u].lc,L,mid,p,v);
    else modify(tr[u].rc,mid + 1,R,p,v);
    update(u);
}
void Union_modify(int u,int Lu,int Ru,int L,int R,int p) {
    if(L == R) {
	tr[u].G = gcd(abs(tr[Lu].G),abs(tr[Ru].G));
	return;
    }
    int mid = (L + R) >> 1;
    if(p <= mid) Union_modify(tr[u].lc,tr[Lu].lc,tr[Ru].lc,L,mid,p);
    else Union_modify(tr[u].rc,tr[Lu].rc,tr[Ru].rc,mid + 1,R,p);
    update(u);
}
void Modify(int u,int L,int R,int x,int y,int64 v) {
    
    if(L == R) {modify(tr[u].rt,1,M,y,v);return;}
    int mid = (L + R) >> 1;
    if(x <= mid) Modify(tr[u].lc,L,mid,x,y,v);
    else Modify(tr[u].rc,mid + 1,R,x,y,v);
    Union_modify(tr[u].rt,tr[tr[u].lc].rt,tr[tr[u].rc].rt,1,M,y);
    return;
}
int64 query(int u,int L,int R,int ql,int qr) {
    if(L == ql && R == qr) return abs(tr[u].G);
    int mid = (L + R) >> 1;
    if(qr <= mid) return query(tr[u].lc,L,mid,ql,qr);
    else if(ql > mid) return query(tr[u].rc,mid + 1,R,ql,qr);
    else return gcd(query(tr[u].lc,L,mid,ql,mid),query(tr[u].rc,mid + 1,R,mid + 1,qr));
}
int64 Query(int u,int L,int R,Matrix t) {
    if(L == t.X1 && R == t.X2) return query(tr[u].rt,1,M,t.Y1,t.Y2);
    int mid = (L + R) >> 1;
    if(t.X2 <= mid) return Query(tr[u].lc,L,mid,t);
    else if(t.X1 > mid) return Query(tr[u].rc,mid + 1,R,t);
    else return gcd(Query(tr[u].lc,L,mid,(Matrix){t.X1,mid,t.Y1,t.Y2}),
		    Query(tr[u].rc,mid + 1,R,(Matrix){mid + 1,t.X2,t.Y1,t.Y2}));
}
void Init() {
    read(N);read(M);read(X);read(Y);read(T);
    for(int i = 1 ; i <= N ; ++i) {
	for(int j = 1 ; j <= M ; ++j) {
	    read(D[c(i,j)]);A[c(i,j)] = D[c(i,j)];
	}
    }
    V = D[c(X,Y)];
    for(int i = 1 ; i <= N ; ++i) {
	for(int j = 1 ; j <= Y - 1 ; ++j) {
	    D[c(i,j)] = D[c(i,j)] - D[c(i,j + 1)];
	}
	for(int j = M ; j >= Y + 1 ; --j) {
	    D[c(i,j)] = D[c(i,j)] - D[c(i,j - 1)];
	}
    }
    for(int j = 1 ; j <= M ; ++j) {
	for(int i = 1 ; i <= X - 1 ; ++i) {
	    D[c(i,j)] = D[c(i,j)] - D[c(i + 1,j)];
	}
	for(int i = N ; i >= X + 1 ; --i) {
	    D[c(i,j)] = D[c(i,j)] - D[c(i - 1,j)];
	}
    }
    Build(Rt,1,N);
    MK[++tot] = (Matrix){X,X,1,Y - 1};
    MK[++tot] = (Matrix){X,X,Y + 1,M};
    MK[++tot] = (Matrix){1,X - 1,Y,Y};
    MK[++tot] = (Matrix){X + 1,N,Y,Y};
    MK[++tot] = (Matrix){1,X - 1,1,Y - 1};
    MK[++tot] = (Matrix){1,X - 1,Y + 1,M};
    MK[++tot] = (Matrix){X + 1,N,1,Y - 1};
    MK[++tot] = (Matrix){X + 1,N,Y + 1,M};
}
int64 Calc(Matrix a,Matrix b) {
    Matrix c;
    c.X1 = max(a.X1,b.X1);c.X2 = min(a.X2,b.X2);
    c.Y1 = max(a.Y1,b.Y1);c.Y2 = min(a.Y2,b.Y2);
    if(c.X1 > c.X2 || c.Y1 > c.Y2) return 0;
    return Query(Rt,1,N,c);
}
void Add_pos(int x,int y,int64 v) {
    if(x < 1 || x > N || y < 1 || y > M) return;
    Modify(Rt,1,N,x,y,v);
    D[c(x,y)] += v;
}
void Add(Matrix a,Matrix b,int64 v) {
    Matrix c;
    c.X1 = max(a.X1,b.X1);c.X2 = min(a.X2,b.X2);
    c.Y1 = max(a.Y1,b.Y1);c.Y2 = min(a.Y2,b.Y2);
    if(c.X1 > c.X2 || c.Y1 > c.Y2) return; 
    if(c.X1 == X) {
	if(c.Y1 <= Y) {
	    Add_pos(c.X1,c.Y2,v);Add_pos(c.X1,c.Y1 - 1,-v);
	    Add_pos(c.X1 - 1,c.Y1 - 1,v);Add_pos(c.X1 + 1,c.Y1 - 1,v);
	    Add_pos(c.X1 - 1,c.Y2,-v);Add_pos(c.X1 + 1,c.Y2,-v);
	}
	else {
	    Add_pos(c.X1,c.Y1,v);Add_pos(c.X1,c.Y2 + 1,-v);
	    Add_pos(c.X1 - 1,c.Y2 + 1,v);Add_pos(c.X1 + 1,c.Y2 + 1,v);
	    Add_pos(c.X1 - 1,c.Y1,-v);Add_pos(c.X1 + 1,c.Y1,-v);
	}
    }
    else if(c.Y1 == Y) {
	if(c.X1 <= X) {
	    Add_pos(c.X2,c.Y1,v);Add_pos(c.X1 - 1,c.Y1,-v);
	    Add_pos(c.X1 - 1,c.Y1 - 1,v);Add_pos(c.X1 - 1,c.Y1 + 1,v);
	    Add_pos(c.X2,c.Y1 - 1,-v);Add_pos(c.X2,c.Y1 + 1,-v);
	}
	else {
	    Add_pos(c.X1,c.Y1,v);Add_pos(c.X2 + 1,c.Y1,-v);
	    Add_pos(c.X1,c.Y1 - 1,-v);Add_pos(c.X1,c.Y1 + 1,-v);
	    Add_pos(c.X2 + 1,c.Y1 - 1,v);Add_pos(c.X2 + 1,c.Y1 + 1,v);
	}
    }
    else if(c.X1 < X) {
	if(c.Y1 < Y) {
	    Add_pos(c.X2,c.Y2,v);Add_pos(c.X2,c.Y1 - 1,-v);
	    Add_pos(c.X1 - 1,c.Y2,-v);Add_pos(c.X1 - 1,c.Y1 - 1,v);
	}
	else {
	    Add_pos(c.X2,c.Y1,v);Add_pos(c.X1 - 1,c.Y1,-v);
	    Add_pos(c.X2,c.Y2 + 1,-v);Add_pos(c.X1 - 1,c.Y2 + 1,v);
	}
    }
    else {
	if(c.Y1 < Y) {
	    Add_pos(c.X1,c.Y2,v);Add_pos(c.X1,c.Y1 - 1,-v);
	    Add_pos(c.X2 + 1,c.Y2,-v);Add_pos(c.X2 + 1,c.Y1 - 1,v);
	}
	else {
	    Add_pos(c.X1,c.Y1,v);Add_pos(c.X1,c.Y2 + 1,-v);
	    Add_pos(c.X2 + 1,c.Y1,-v);Add_pos(c.X2 + 1,c.Y2 + 1,v);
	}
    }
}

void Solve() {
    int op,X1,X2,Y1,Y2;
    int64 c;
    while(T--) {
	read(op);read(X1);read(Y1);read(X2);read(Y2);
	Matrix t;
	if(op == 0) {
	    int64 res = V;
	    t = (Matrix){X - X1,X + X2,Y - Y1,Y + Y2};
	    for(int i = 1 ; i <= tot ; ++i) {
		res = gcd(res,Calc(MK[i],t));
	    }
	    out(abs(res));enter;
	}
	else {
	    t = (Matrix){X1,X2,Y1,Y2};
	    
	    read(c);
	    
	    if(X1 <= X && X <= X2 && Y1 <= Y && Y <= Y2) {
		V += c;
		Add_pos(X,Y,c);
		Add_pos(X - 1,Y,-c);
		Add_pos(X + 1,Y,-c);
		Add_pos(X,Y - 1,-c);
		Add_pos(X,Y + 1,-c);
		Add_pos(X - 1,Y - 1,c);
		Add_pos(X - 1,Y + 1,c);
		Add_pos(X + 1,Y - 1,c);
		Add_pos(X + 1,Y + 1,c);
	    }
	    for(int i = 1 ; i <= tot ; ++i) {
		Add(MK[i],t,c);
	    }
	}
    }
}
int main() {
#ifdef ivorysi
    freopen("f1.in","r",stdin);
#endif
    Init();
    Solve();
}