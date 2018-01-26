#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

inline void qr(int &x){
    int f = 1,w = 0;char ch =getchar();
    while(ch<='0'||ch>'9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        w = (w<<3)+(w<<1)+ch-48;
        ch = getchar();
    }
    x = f*w;
}

int dui[100010];

int n;
int a[100010],b[100010];

void m_heap(int i){
    if((i<<1)>n){
        return;
    }
    else if((i<<1)+1>n){
        if(dui[i<<1]>dui[i]){
            int temp = dui[i];
            dui[i] = dui[i<<1];
            dui[i<<1] = temp;
        }
        return;
    }
    else{
        int maxn;
        maxn = dui[i]>=dui[i<<1]&&dui[i]>=dui[(i<<1)+1]?i: dui[i<<1]>=dui[(i<<1)+1]?i<<1:(i<<1)+1;
        int tmp = dui[maxn];
        dui[maxn] = dui[i];
        dui[i] = tmp; 
        if(maxn!=i)
            m_heap(maxn);
    }
}

int main(){
    qr(n);
    for(int i = 0;i<n;i++)
        qr(a[i]);
    for(int i = 0;i<n;i++)
        qr(b[i]);
    for(int i = 1;i<=n;i++){
        dui[i] = 2000000100;
    }
    for(int i = 0;i<n;i++){
        if(a[i]+b[0]>=dui[1])
            break;
        for(int j = 0;j<n;j++){
            if(a[i]+b[j]<=dui[1]){
                dui[1] = a[i]+b[j];
                m_heap(1);
            }
            else{
                //printf("i,j:%d %d!!!\n",i,j);
                break;
            }
        }
    }


    sort(dui+1,dui+n+1);
    for(int i = 1;i<=n;i++)
        printf("%d ",dui[i]);
    putchar('\n');
    return 0;
}