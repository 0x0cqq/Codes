#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;

const int N = 250010;
int n, m, clock = 0, cnt = 0;
int head[N], in[N], out[N], T[N], X[N], Y[N];
char ch[3];

struct Edge{
    int to, nex;
}e[N<<1];

inline int read()
{
    char ch = getchar(); int x = 0, flag = 0;
    while (!isdigit(ch)){ if (ch == '-') flag = 1; ch = getchar(); }
    while (isdigit(ch)){ x = x * 10 + ch - '0'; ch = getchar(); }
    return flag ? -x : x;
}

inline void write(int a){ if (a >= 10) write(a/10); putchar('0'+a%10); }
inline void writeln(int a){ write(a); puts(""); }

inline void add(int x, int y){ e[++ cnt].to = y; e[cnt].nex = head[x]; head[x] = cnt; }

inline void dfs(int u, int fa)
{
    in[u] = ++ clock;
    for (int i = head[u]; i; i = e[i].nex)
        if (e[i].to != fa) dfs(e[i].to, u);
    out[u] = clock;
}

inline void change(int k, int v){ for (; k < N; k += k&-k) T[k] += v; }
inline int getSum(int k){ int ret = 0; for (; k; k -= k&-k) ret += T[k]; return ret; }

int main()
{
    n = read();
    for (int i = 1; i < n; i ++){
        X[i] = read(), Y[i] = read();
        add(X[i], Y[i]); add(Y[i], X[i]);
    }
    dfs(1, 0);
    for (int i = 1; i < n; i ++){
        if (in[X[i]] < in[Y[i]]) swap(X[i], Y[i]);
        change(in[X[i]], 1); change(out[X[i]]+1, -1); //本来所有边都是公路
    }
    m = read();
    for (int i = 1; i <= n+m-1; i ++){
        scanf("%s", ch);
        if (ch[0] == 'A'){
            int x = read(), y = read();
            if (in[x] < in[y]) swap(x, y);
            change(in[x], -1); change(out[x]+1, 1); //修改为土路
        } else{
            int x = read();
            writeln(getSum(in[x]));
        }
    }
    return 0;
}