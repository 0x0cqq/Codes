#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1000;

int n;
int b1[MAXN],b2[MAXN];
char s[MAXN],t[MAXN];
vector<int> mov;

int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    scanf("%s",t+1);
    for(int i = 1;i<=n;i++){
        b1[s[i]]++,b2[t[i]]++;
    }
    for(int j = 1;j<=127;j++){
        if(b1[j]!=b2[j]){
            printf("-1\n");
            return 0;
        }
    }
    for(int i = 1;i<=n;i++){
        if(s[i] == t[i]) continue;
        for(int j = i+1;j<=n;j++){
            if(s[j] == t[i]){
                for(int k = j-1;k>=i;--k){
                    mov.push_back(k);
                    swap(s[k],s[k+1]);
                }
            }
        }
    }
    printf("%d\n",int(mov.size()));
    for(int i = 0;i<mov.size();i++){
        printf("%d ",mov[i]);
    }
    return 0;
}