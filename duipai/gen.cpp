#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

const int MAXN = 3;

int n = 15,m = 3;

int main(){
  srand(time(NULL));
  for(int i = 0;i<n;i++) putchar(rand()%MAXN+'a');
  putchar('\n');
  for(int i = 0;i<m;i++) putchar(rand()%MAXN+'a');
  putchar('\n');
}