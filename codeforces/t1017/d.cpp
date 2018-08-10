#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 4000000;

int n,m,q;
int w[200],sum[200];
int c[MAXN][2],siz[MAXN],is_end[MAXN];

int root = 1,cnt = 1;

char s[200];

void insert(char *str){
    int n = strlen(str),nown = root;
    siz[root]++;
    for(int i = 0;i<n;i++){
        if(!c[nown][str[i]-'0'])
            c[nown][str[i]-'0'] = ++cnt;
        nown = c[nown][str[i]-'0'];
        siz[nown]++;
    }
    is_end[nown]++;
}

//query(1,limit,s,1)
int query(int nown,int limit,char *str,int i){
    // printf("nown:%d limit:%d i:%d\n",nown,limit,i);
    // printf("str:%s\n",str);
    if(!nown) 
        return 0;
    else if(limit < 0)
        return 0;
    else if(sum[i+1] <= limit || i == n){
        return siz[nown];
    }
    else{
        // printf("str[i]:%d\n",str[i]);
        return query(c[nown][0],limit - (str[i] == '0'?w[i+1]:0),str,i+1)+ query(c[nown][1],limit - (str[i] == '1'?w[i+1]:0),str,i+1);
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&q);
    for(int i = 1;i<=n;i++){
        scanf("%d",&w[i]);
    }
    for(int i = n;i>=1;i--){
        sum[i] += sum[n-i-1] + w[i];
    }
    for(int i = 1;i<=m;i++){
        scanf("%s",s);
        reverse(s,s+n);
        insert(s);
    }
    int k;
    for(int i = 1;i<=q;i++){
        scanf("%s",s);
        reverse(s,s+n);
        scanf("%d",&k);
        printf("%d\n",query(1,k,s,0));
    }
    return 0;
}