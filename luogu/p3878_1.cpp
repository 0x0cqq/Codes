#include<bits/stdc++.h>
using namespace std;
typedef long long LL;//这里是一个简写 
const LL maxn=1LL<<60;
LL a[300];
LL H[300];//前缀和 
int i,j,n,m,s,T;
LL h(int l,int r)//前缀和 
{
    return(H[r]-H[l-1]);
}
//f表示最小差(即答案），x是第一堆个数，X是第一堆总价值；y是第二堆同理 
LL f(int c,int x,LL X,int y,LL Y) 
{
    //你取太多了！ 
    if(x>n/2||y>n/2) return maxn;
    //X最大仍小于Y，第一堆取太便宜了！ 
    LL XX=X+h(c,c+(n/2-x)-1); 
    if(XX<=s-XX) return(s-XX-XX);
    //X最小仍大于Y，第一堆取太贵了！ 
    XX=X+h(n-(n/2-x)+1,n);
    if(XX>=s-XX) return(XX-(s-XX));

    int p=f(c+1,x+1,X+a[c],y,Y);//放第一堆 
    int q=f(c+1,x,X,y+1,Y+a[c]);//放第二堆 
    if(p<q) return p;else return q;
}
int main()//主 
{
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(i=1;i<=n;i++) cin>>a[i];
        s=0;
        for(i=1;i<=n;i++) s+=a[i];
        if(n&1){n++;a[n]=0;}//小细节：金币个数为奇数时补一个0，使之偶数 
        sort(a+1,a+1+n,greater<int>());//从大到小 
        H[0]=0;
        for(i=1;i<=n;i++) H[i]=H[i-1]+a[i];
        cout<<f(1,0,0,0,0)<<endl;
    }
}