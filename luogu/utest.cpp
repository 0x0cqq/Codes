// luogu-judger-enable-o2
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>

#define MAXN 4000005
#define INF 0x3f3f3f3f
#define ri register int
#define chkmin(a, b) (a < b ? a : a = b)
#define chkmax(a, b) (a > b ? a : a = b)
#define debug(i) (cout << "BREAKPOINT No." << i << endl)

typedef long long ll;

using namespace std;

int cnt = 0;
int prime[MAXN], mu[MAXN], phi[MAXN];
bool vis[MAXN];
ll s1[MAXN], s2[MAXN];
map <int, int> sum_mu;
map <int, ll> sum_phi;

namespace fast_IO
{
    #define gets getchar
/*	inline char gets()
    {
        static char buf[100000], *p1, *p2;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
    }*/

    inline int read_int()
    {
        register int ret = 0, f = 1; register char c = gets();
        while(c < '0' || c > '9') {if(c == '-') f = -1; c = gets();}
        while(c >= '0' && c <= '9') {ret = (ret << 1) + (ret << 3) + int(c - 48); c = gets();}
        return ret * f;
    }
    #undef gets
}using namespace fast_IO;

int get_mu(int n)
{
    if(n == 0)
        return 0;
    if(n < MAXN - 5)
        return s1[n];
    if(sum_mu.count(n))
        return sum_mu[n];
    ri ans = 1;
    for(ri l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans -= (r - l + 1) * get_mu(n / l);
    }
    return sum_mu[n] = ans;
}

ll get_phi(ll n)
{
    if(n == 0)
        return 0;
    if(n < MAXN - 5)
        return s2[n];
    if(sum_phi.count(n))
        return sum_phi[n];
    ll ans = n * (n + 1) >> 1;
    for(ri l = 2, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans -= (r - l + 1) * get_phi(n / l);
    }
    return sum_phi[n] = ans;
}

inline void init()
{
    mu[1] = phi[1] = s1[1] = s2[1] = 1;
    for(ri i = 2; i <= MAXN - 5; i++)
    {
        if(!vis[i])
            prime[++cnt] = i, mu[i] = -1, phi[i] = i - 1;
        for(ri j = 1; j <= cnt && i * prime[j] <= MAXN - 5; j++)
        {
            vis[i * prime[j]] = true;
            if(i % prime[j] != 0)
            {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                mu[i * prime[j]] = -mu[i];
            }
            else
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            }
        }
        s1[i] = mu[i] + s1[i - 1];
        s2[i] = phi[i] + s2[i - 1];
    }
}

int main()
{
    init();
    ri T = read_int();
    for(ri i = 1; i <= T; i++)
    {
        ll x = read_int();
        printf("%lld %d\n", get_phi(x), get_mu(x));
    }
    return 0;
}