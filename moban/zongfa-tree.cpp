#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN = 200005;
const int ra = 5;
int n, cnt, fa, root, tot;
int siz[MAXN], ls[MAXN], rs[MAXN], val[MAXN], trash[MAXN];
int newnode(int v){
    int cur;
    if(tot) cur = trash[tot--];
    else cur = ++cnt;
    siz[cur] = 1;
    val[cur] = v;
    ls[cur] = rs[cur] = 0; //maybe trash
    return cur;
}
void copynode(int cur, int pre){
    siz[cur] = siz[pre];
    val[cur] = val[pre];
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];
}
int merge(int l, int r){
    int cur;
    if(tot) cur = trash[tot--];
    else cur = ++cnt;
    siz[cur] = siz[l] + siz[r];
    val[cur] = val[r];
    ls[cur] = l, rs[cur] = r;
    return cur;
}
void rotate(int cur, bool flag){
    if(flag){ // to left
        ls[cur] = merge(ls[cur], ls[rs[cur]]);
        trash[++tot] = rs[cur];
        rs[cur] = rs[rs[cur]];
    }
    else{ // to right
        rs[cur] = merge(rs[ls[cur]], rs[cur]);
        trash[++tot] = ls[cur];
        ls[cur] = ls[ls[cur]];
    }
}
void maintain(int cur){
    if(siz[ls[cur]] > siz[rs[cur]] * ra)
        rotate(cur, 0);
    else if(siz[rs[cur]] > siz[ls[cur]] * ra)
        rotate(cur, 1);
    if(siz[ls[cur]] > siz[rs[cur]] * ra)
        rotate(ls[cur], 1), rotate(cur, 0);
    else if(siz[rs[cur]] > siz[ls[cur]] * ra)
        rotate(rs[cur], 0), rotate(cur, 1);
}
void update(int cur){
    if(!siz[ls[cur]]) return;
    siz[cur] = siz[ls[cur]] + siz[rs[cur]];
    val[cur] = val[rs[cur]];
}
void insert(int cur, int x){
    if(siz[cur] == 1){
        ls[cur] = newnode(min(x, val[cur]));
        rs[cur] = newnode(max(x, val[cur]));
        update(cur);
        return;
    }
    maintain(cur);
    insert(x > val[ls[cur]] ? rs[cur] : ls[cur], x);
    update(cur);
}
void erase(int cur, int x){
    if(siz[cur] == 1){
        cur = ls[fa] == cur ? rs[fa] : ls[fa];
        copynode(fa, cur);
        return;
    }
    maintain(cur); fa = cur;
    erase(x > val[ls[cur]] ? rs[cur] : ls[cur], x);
    update(cur);
}
int find(int cur, int x){
    if(siz[cur] == x) return val[cur];
    maintain(cur);
    if(x > siz[ls[cur]]) 
        return find(rs[cur], x - siz[ls[cur]]);
    return find(ls[cur], x);
}
int rnk(int cur, int x){
    if(siz[cur] == 1) return 1;
    maintain(cur);
    if(x > val[ls[cur]]) 
        return rnk(rs[cur], x) + siz[ls[cur]];
    return rnk(ls[cur], x);
}
int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d", &n);
    root = newnode(2147383647);
    while(n--){
        int s, a; scanf("%d %d", &s, &a);
        if(s == 1) insert(root, a);
        if(s == 2) erase(root, a);
        if(s == 3) printf("%d\n", rnk(root, a));
        if(s == 4) printf("%d\n", find(root, a));
        if(s == 5) printf("%d\n", find(root, rnk(root, a) - 1));
        if(s == 6) printf("%d\n", find(root, rnk(root, a + 1)));
    }
    return 0;
}
