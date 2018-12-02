#include <bits/stdc++.h>
typedef long long LL;

LL f[100];
int t;



void Work() {
  int n;
  LL k;
  scanf("%d %lld", &n, &k);
  if (k == 0) {
    printf("YES\n");
    return;
  }
  if (n > t) {
    printf("YES\n");
    return;
  }
  LL l = 0, r = 0;
  for (int i = 0; i <= n && l <= k; ++i) {
    if (r >= k) {
      printf("YES\n");
      return;
    }
    if (i < n) {
      r += (1LL << (i + 1)) - 1;
      if (r > k) r = k;
      // r += 2^(i+1)-1+(2^(i+1)-3)*f[n-i-1]
      // l += 2^(i+1)-1
      LL a = (1LL << (i + 2)) - 3, b = f[n - i - 1];
      if ((k - r) / a < b) r = k;
      else r += a * b;
      l += (1LL << (i + 1)) - 1;
    }
  }
  puts("NO");
}

int main(){
  f[0] = 0;
  for (t = 0; f[t] <= 1000000000000000000LL; ++t)
    f[t + 1] = f[t] * 4 + 1;
  int q;
  scanf("%d", &q);
  while (q--) Work();
  return 0;
}