#include <cstdio>
#define lowbit(x) (x&(-x))
using namespace std;

void qr(int &x){
    int f = 1,w = 0;char ch = getchar();
    while(ch<='0'||ch>'9'){
        if(ch=='-')
            f = -1;
        ch = getchar();
    }
    while(ch>='0'&&ch<='9'){
        w = (w<<3)+(w<<1)+ch-48;
        ch = getchar();
    }
    x = f*w;
}

int n,m,l;

int num[510000],w[510000];

char res[6000000];

int main(){
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++){
        scanf("%d",&(num[i]));
        for(int j = i-lowbit(i)+1;j<=i;j++){
            w[i]+=num[j];
        }
    }
    for(int i = 1;i<=m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(a == 1)
            for(int j = b;j<=n;j+=lowbit(j))
                w[j] += c;
        else{
            int ans1 = 0,ans2 = 0;
            for(int j = b-1;j>=1;j-=lowbit(j))
                ans1 += w[j];
            for(int j = c;j>=1;j-=lowbit(j))
                ans2 += w[j];
            l+=(sprintf(res+l,"%d\n",ans2-ans1));
        }
    }
    printf("%s",res);
    return 0;
}