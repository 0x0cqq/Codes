#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 50005
#define INF 0x3f3f3f3f
#define ri register int

using namespace std;

int num;
int top;
int l, r;
int N = -1;
int sigma_size = 26;
int s[MAXN];
int id[MAXN], stk[MAXN];
int sa[MAXN], rnk[MAXN], height[MAXN];
bool vis[MAXN];
char a[10][MAXN];

inline int read_int()
{
    register int ret = 0, f = 1; register char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') {ret = (ret << 1) + (ret << 3) + int(c - 48); c = getchar();}
    return ret * f;
}

namespace Suffix_Array
{
    int cnt[MAXN];
    int x[MAXN], y[MAXN];

    inline void get_SA()
    {
//      cout << "ENTER SA" << endl;
        N++, sigma_size = 127;
        // printf("%d %d\n",N,sigma_size);
        s[N] = 0;
        for(ri i = 0; i < sigma_size; i++) cnt[i] = 0;
        for(ri i = 0; i < N; i++) cnt[s[i]]++;
        for(ri i = 0; i < sigma_size; i++) cnt[i] += cnt[i - 1];
        for(ri i = N - 1; i >= 0; i--) sa[--cnt[s[i]]] = i;
        sigma_size = rnk[sa[0]] = 0;
        for(ri i = 1; i < N; i++)
            rnk[sa[i]] = s[sa[i]] != s[sa[i - 1]] ? ++sigma_size : sigma_size;
//      cout << "BREAKPOINT" << endl;
        for(ri j = 1; ; j <<= 1)
        {
            if(++sigma_size == N) break;
            for(ri i = 0; i < j; i++) y[i] = N - j + i;
            for(ri i = 0, k = j; i < N; i++) if(sa[i] >= j) y[k++] = sa[i] - j;
            for(ri i = 0; i < N; i++) x[i] = rnk[y[i]];
            for(ri i = 0; i < sigma_size; i++) cnt[i] = 0;
            for(ri i = 0; i < N; i++) cnt[x[i]]++;
            for(ri i = 1; i < sigma_size; i++) cnt[i] += cnt[i - 1];
            for(ri i = N - 1; i >= 0; i--) sa[--cnt[x[i]]] = y[i], y[i] = rnk[i];
            sigma_size = rnk[sa[0]] = 0;
            for(ri i = 1; i < N; i++)
                rnk[sa[i]] = (y[sa[i]] != y[sa[i - 1]] || y[sa[i] + j] != y[sa[i - 1] + j]) ? ++sigma_size : sigma_size;
        }
//      cout << "LEAVE" << endl;
    }

    inline void get_height()
    {
        for(ri i = 0, h = height[0] = 0; i < N; i++)
        {
            ri j = sa[rnk[i] - 1];
            while(i + h < N && j + h < N && s[i + h] == s[j + h])
                h++;
            height[rnk[i]] = h;
            if(h)
                h--;
        }
    }
}

inline void init()
{
    r = INF;
    num = read_int();
    for(ri i = 1; i <= num; i++)
        scanf("%s", a[i]);
    for(ri i = 1; i <= num; i++)
    {
        r = min(r, (int) strlen(a[i]));
        int len = strlen(a[i]);
        for(ri j = 0; j < len; j++)
            s[++N] = a[i][j] - 'a' + 1, id[N] = i;
        s[++N] = ++sigma_size;
    }
    ++N;
    Suffix_Array::get_SA();
    Suffix_Array::get_height();
    // cout << "array" << endl;
    // for(ri i = 0; i < N; i++)
    //     cout << s[i] << " ";
    // cout << endl;
    // cout << "sa" << endl;
    // for(ri i = 0; i < N; i++)
    //     cout << sa[i] << " ";
    // cout << endl;
    // cout << "rnk" << endl;
    // for(ri i = 0; i < N; i++)
    //     cout << rnk[i] << " ";
    // cout << endl;
    // cout << "hgt" << endl;
    // for(ri i = 0; i < N; i++)
    //     cout << height[i] << " ";
    // cout << endl;
    // cout << "hgt" << endl;
    // for(ri i = 0; i < N; i++)
    //     cout << id[sa[i]] << " ";
    // cout << endl;
}

inline bool check(int k)
{
    // printf("k:%d\n",k);
    int cnt = 0;
    top = 0;
    memset(vis, 0, sizeof(vis));
    memset(stk, 0, sizeof(stk));
    stk[++top] = id[sa[0]], vis[id[sa[0]]] = true, cnt = 1;
    for(ri i = 1; i < N; i++)
    {
        // cout << "i = " << i << " sa[i] = " << sa[i] << " hgt[i] = " << height[i] << " id = " << id[sa[i]] << endl;
        // cout << "cnt = " << cnt << endl;
        if(height[i] < k)
        {
            cnt = 0;
            while(top)
                vis[stk[top]] = 0,stk[top] = 0,top--;
            // memset(vis,0,sizeof(vis));
        }
        if(!vis[id[sa[i]]] && id[sa[i]] > 0)
            vis[id[sa[i]]] = true, cnt++, stk[++top] = id[sa[i]];
        if(cnt == num)
            return true;
    }
    return false;
}

inline void calc()
{
    while(l < r)
    {
        ri mid = (l + r + 1) >> 1;
        int t = check(mid);
        // printf("%d:%d\n",mid,t);
        if(t)
            l = mid;
        else
            r = mid - 1;
    }
    printf("%d\n", l);
}

int main()
{
    init();
    calc();
    return 0;
}