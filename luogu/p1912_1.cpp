#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const int maxn = 100010;
int T, n, L, P, S[maxn], nxt[maxn];
int head, tail, q[maxn], id[maxn], l[maxn], r[maxn];
ld f[maxn];
char s[maxn][35];

ld qp(ld x) {
    ld ans = 1;
    for (int p = P; p; x *= x, p >>= 1) {
        if (p & 1) {
            ans *= x;
        }
    }
    return ans;
}

ld calc(int j, int i) {
    return f[j] + qp(abs(S[i] - S[j] - L - 1));
}

void get(int x) {
    int lb = l[q[tail]], rb = n;
    while (lb < rb) {
        int mid = (lb + rb) >> 1;
        if (calc(x, mid) < calc(q[tail], mid)) {
            rb = mid;
        } else {
            lb = mid + 1;
        }
    }
    r[q[tail]] = lb - 1;
    q[++tail] = x, l[x] = lb, r[x] = n;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &L, &P);
        for (int i = 1; i <= n; i++) {
            scanf("%s", s[i]);
            S[i] = S[i - 1] + strlen(s[i]) + 1;
        }
        head = 0, tail = -1;
        q[++tail] = 0, l[0] = 1, r[0] = n;
        for (int i = 1; i <= n; i++) {
            while (r[q[head]] < i) head++;
            f[i] = calc(q[head], i), id[i] = q[head];
            if (calc(q[tail], n) < calc(i, n)) continue;
            while (calc(q[tail], l[q[tail]]) > calc(i, l[q[tail]])) tail--;
            get(i);
        }
        if (f[n] > 1e18) {
            printf("Too hard to arrange\n");
        } else {
            printf("%lld\n", (long long)(f[n] + 0.5));
            for (int i = n; i; i = id[i]) {
                nxt[id[i]] = i;
            }
            for (int i = 1, cur = 0; i <= n; i = cur + 1) {
                cur = nxt[cur];
                for (int j = i; j < cur; j++) {
                    printf("%s ", s[j]);
                }
                printf("%s\n", s[cur]);
            }
        }
        printf("--------------------\n");
    }
    return 0;
}