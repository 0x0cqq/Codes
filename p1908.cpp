#include <cstdio>
using namespace std;

int a[40000];

int mergesort(int b,int e){
    int ans = 0;
    if(e-b==1){
        return 0;
    }
    else if(e-b == 2){
        if(a[b]>a[e-1]){
            int t = a[e-1];
            a[e-1] = a[b];
            a[b] = t;
            ans++;
        }
        return ans;
    }
    else{
        ans+=mergesort(b,(b+e)/2);
        ans+=mergesort((b+e)/2,e);
        int k[e-b],w = 0;
        int i= b,j = (b+e)/2;
        while(i<(b+e)/2&&j<e){
            if(a[i]>a[j]){
                ans++;
                k[w++] = a[j++];
            }
            else{
                k[w++] = a[i++];
            }
        }
        while(i<(b+e)/2){
            k[w++] = a[i++];
            ans++;
        }
        while(j<e){
            k[w++] = a[j++];
        }
        for(int i = 0;i<e-b;i++){
            a[b+i] = k[i];
        }
    }
    return ans;
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",a+i);
    }
    printf("%d\n",mergesort(0,n));
    return 0;
}