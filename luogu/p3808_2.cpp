#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#define reg register
using namespace std;
int cnt, n, ans;
char s[1000050];
struct node {
    int id, cnt, vis, visf;
    node *nxt[30], *fail, *fa;
}pool[2000500], *GG, *rt, *q[2000500];
void ins() {
    int len = strlen(s);
    node *u = rt;
    for(int i = 0; i < len; i++) {
        if(!u->nxt[s[i]-'a']) 
            u->nxt[s[i]-'a'] = &pool[cnt++], u->nxt[s[i]-'a']->id = s[i]-'a', u->nxt[s[i]-'a']->fa = u;
        u = u->nxt[s[i]-'a'];
    }
    u->cnt++;
}
void get_fail() {
    rt->fail = GG;
    int front = 0, rear = 0;
    for(int i = 0; i < 26; i++) if(rt->nxt[i]) q[rear++] = rt->nxt[i];
    while(front < rear) {
        node *u = q[front++];
        node *ff = u->fa->fail;
        while(ff != GG && !ff->nxt[u->id]) ff = ff->fail;
        if(ff == GG) u->fail = rt;
        else u->fail = ff->nxt[u->id];
        for(int i = 0; i < 26; i++) if(u->nxt[i]) q[rear++] = u->nxt[i];
    }
}
void calc() {
    int len = strlen(s);
    node *u = rt; u->fail = GG;
    for(int i = 0; i < len; i++) {
        //cout<<i<<' '<<u->id<<' ';
        while(u->fail != GG && !u->nxt[s[i]-'a']) u = u->fail;
        if(u->nxt[s[i]-'a']) u = u->nxt[s[i]-'a'];
        else u = rt;
        if(!u->vis) u->vis = 1, ans += u->cnt;
        node *v = u;
        while(v->fail != GG && !v->visf) {
            if(!v->fail->vis) v->fail->vis = 1, ans += v->fail->cnt;
            v = v->fail;
        }
        u->visf = 1; 
    }
}
int main() {
    GG = &pool[cnt++], rt = &pool[cnt++];
    scanf("%d", &n);
    while(n--) {
        scanf("%s", s);
        ins();
    }
    //cout<<"QWQ";
    get_fail();
    //cout<<"QWQ";
    scanf("%s", s);
    calc();
    printf("%d", ans);
    return 0;
}
