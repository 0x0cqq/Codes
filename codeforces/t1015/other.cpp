#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 9;

long long n, k, s, a[N];

int main() {
  cin >> n >> k >> s;
  if ((n - 1) * k < s || k > s) {
    cout << "NO";
    return 0;
  }
  cout << "YES\n";
  for (int i = 1; i <= k; i++) {
    a[i] = 1;
  }
  s -= k;
  for (int i = 1; i <= k; i++) {
    if (s >= (n - 2)) {
      a[i] += n - 2;
      s -= (n - 2);
    } else {
      a[i] += s;
      s = 0;
      break;
    }
  }  
  long long st = 1;
  for (int i = 1; i <= k; i++) {
    if (st + a[i] <= n) {
      st += a[i];
    } else {
      st -= a[i];
    }
    printf("%lld ", st);
  }
  return 0;
}