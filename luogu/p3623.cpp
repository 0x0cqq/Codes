#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define no_solution printf("no solution\n");
using namespace std;
                  
const int MAXN = 20200;
const int MAXM = 100100;
int n, m, k, fa[MAXN], tot, cnt;
struct edge {  
    int u, v, w;    
}e[MAXM], ans[MAXM];  
bool cmp1(edge e1, edge e2) {
    return e1.w > e2.w;
}
bool cmp2(edge e1, edge e2) {
    return e1.w < e2. w;
}
int find(int x) {
    if(fa[x] == x) return x;
    else return fa[x] = find(fa[x]);
}
bool Union(int x, int y) {
    x = find(x), y = find(y);
    if(x == y) return false;
    fa[x] = y;
    return true;
}
void init() {
    cnt = tot = 0;
    for(int i = 1; i <= n; i++) fa[i] = i;
}
void check() {
    int tmp = find(1);
    for(int i = 2; i <= n; i++) {
        int f = find(i);
        if(f != tmp) {
            no_solution;
            exit(0);
        }
        tmp = f;
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= m; i++) scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    init(); sort(e + 1, e + m + 1, cmp1);
    for(int i = 1; i <= m; i++)
        if(Union(e[i].u, e[i].v) && e[i].w == 0)
                tot++, e[i].w = -1;

    if(tot > k) {
        no_solution;
        return 0;
    }
    check();
    init(); sort(e + 1, e + m + 1, cmp2);

    for(int i = 1; i <= m; i++) {
        int f1 = find(e[i].u), f2 = find(e[i].v);
        if(f1 == f2) continue;
        if(e[i].w == 1 || tot < k) {
            ans[++cnt] = e[i]; fa[f1] = f2;
            if(e[i].w < 1)
                tot++, e[i].w = 0;
        }
    }
    if(tot < k) {
        no_solution;
        return 0;
    }
    check(  );
    for(int i = 1; i <= cnt; i++) {
        if(ans[i].w == -1) ans[i].w = 0;
        printf("%d %d %d\n", ans[i].u, ans[i].v, ans[i].w);
    }
    return 0;
}