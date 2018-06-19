#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int a[12];
ll l, r, dp[11][11][10][2][2][2][2];

ll f(int n, int limit, int last, bool equal, bool flag, bool four, bool eight) {
    ll &ans = dp[n][limit][last][equal][flag][four][eight];
    if (ans != -1) return ans;
    ans = 0;
    if (n == 1) {
        for (int i = 0; i <= min(9, limit); i++) {
            if ((i == 4 && eight) || (i == 8 && four)) continue;
            ans += (flag || (equal && i == last));
        }
    } else {
        for (int i = 0; i <= min(9, limit); i++) {
            if ((i == 4 && eight) || (i == 8 && four)) continue;
            ans += f(n - 1, (i < limit || limit > 9) ? 10 : a[13 - n], i, i == last, flag || (equal && i == last), four || (i == 4), eight || (i == 8));
        }
    }
    return ans;
}

ll calc(ll x) {
    if (x < 1e10) return 0;
    memset(dp, -1, sizeof(dp));
    for (int cur = 11; x; x /= 10) {
        a[cur--] = x % 10;
    }
    ll ans = 0;
    for (int i = 1; i <= a[1]; i++) {
        ans += f(10, i < a[1] ? 10 : a[2], i, 0, 0, i == 4, i == 8);
    }
    return ans;
}

int main() {
    scanf("%lld %lld", &l, &r);
    printf("%lld\n", calc(r) - calc(l - 1));
    return 0;
}