#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

char s[MAXN];

int main(){
    scanf("%s",s);
    int n = strlen(s);
    int last = 0,appear2 = s[0] == '2',appear0 = s[0] == '0';
    for(int i = 1;i<n;i++){
        if(s[i] == '0') appear0 = 1;
        if(s[i] == '2') appear2 = 1;
        if(appear2 && appear0){
            sort(s+last,s+i);
            last = lower_bound(s+last,s+i,'1')-s;
            appear0 = 0;
            if(s[i] == '0') appear0 = 1;
            if(s[i] == '2') appear2 = 1;
        }
        //printf("%d %d %s\n",i,last,s);
    }
    if(!(appear2 && appear0))
        sort(s+last,s+n);
    printf("%s",s);
    return 0;
}
