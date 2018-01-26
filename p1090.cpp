#include <cstdio>
#include <algorithm>
using namespace std;

int a[100000];
void merge(int begin, int end){
    if(end - 1 == begin)
        return;
    int k[end-begin],w = 0,i,j;
    int t = (begin + end+1)/2;
    merge(begin,t);
    merge(t,end);
    for(i = begin,j = t;i<t&&j<end;){
        if(a[i]>a[j])
            k[w++] = a[j++];
        else
            k[w++] = a[i++];
    }
    while(i<t)
        k[w++] = a[i++];
    while(j<end)
        k[w++] = a[j++];
    for(int i = 0;i<w;i++){
        a[begin+i] = k[i];
    }
}

int main(){
    int n,ans = 0;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",a+i);
    }
    if(n == 1){
        printf("0\n");
        return 0;
    }
    merge(0,n);
    for(int w = 0;w<n-1;w++){
        ans+=(a[1] = a[0]+a[1]);
        a[0] = 100000000;
        merge(0,n);
    }
    printf("%d\n",ans);
}