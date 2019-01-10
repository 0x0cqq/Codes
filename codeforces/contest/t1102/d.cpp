#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 5;
const int mod = 1e9 + 7;
int n, cnt[3], cnt1[3];
char s[N]; 
int main() {
  scanf("%d",&n);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; ++i)
    cnt[s[i] - '0']++;
  for (int i = 1; i <= n; ++i) {
    if (cnt[s[i] - '0'] > n / 3) {
      for (int j = 0; j < 3; ++j) {
        if (cnt[j] < n / 3 && (j < s[i] - '0' || cnt1[s[i] - '0'] == n / 3)) {
          cnt[s[i] - '0']--;
          s[i] = '0' + j;
          cnt[j]++;
          break;
        }
      }
    } 
    cnt1[s[i] - '0']++;
  }
  printf("%s", s + 1);
  return 0;
}