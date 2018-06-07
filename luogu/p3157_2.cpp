#include<bits/stdc++.h>
using namespace std;
int n,m,endq[100010],pls[100010];//pls[i]记录的是i的位置
long long ans=0;
struct Zxt{
    #define Nmax 6000001
    #define mid ((ln+rn)>>1)
    #define out_it (ln>rd || rn<ld)
    #define in_it (ln>=ld && rn<=rd)
    long long sum[Nmax],tailn;
    int ls[Nmax],rs[Nmax],root[Nmax];
    void add(int &num,int ln,int rn,int pos){
        if(!num){
            num=++tailn;
        }
        ++sum[num];
        if(ln==rn)
            return;
        if(pos<=mid)
            add(ls[num],ln,mid,pos);
        else
            add(rs[num],mid+1,rn,pos);
    }
    long long query(int num1,int ln,int rn,int ld,int rd){//last jian old
        if(out_it)
            return 0;
        if(in_it)
            return sum[num1];
        return query(ls[num1],ln,mid,ld,rd)+
            query(rs[num1],mid+1,rn,ld,rd);
    }
    long long find(int pos1,int pos2,int lowest,int uppest){
        if(lowest>uppest)
            return 0;
        long long asp=0;
        for(;pos2;pos2-=(pos2)&(-pos2))
            asp+=query(root[pos2],1,n,lowest,uppest);
        for(;pos1;pos1-=(pos1)&(-pos1))
            asp-=query(root[pos1],1,n,lowest,uppest);
        return asp;
    }
}Zxt;
struct BITs{
    long long val[100001];
    int lowbit(int x){
        return x&(-x);
    }
    void addb(int pos,int num){
        for(;pos<=100000;pos+=lowbit(pos))
            val[pos]+=num;
    }
    long long queryb(int pos){
        long long ans=0;
        for(;pos;pos-=lowbit(pos))
            ans+=val[pos];
        return ans;
    }
}BIT;
long long as1[100001],as2[100001],p1,p2;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        scanf("%d",&endq[i]);
        pls[endq[i]]=i;
        as1[i]=BIT.queryb(n)-BIT.queryb(endq[i]);
        ans+=as1[i];
        BIT.addb(endq[i],1);
    }
    for(int i=1;i<=100000;++i)  BIT.val[i]=0;//防止第二遍统计出问题 
    for(int i=n;i>=1;--i){
        as2[i]=BIT.queryb(endq[i]-1);
        BIT.addb(endq[i],1);
    }//原来的BIT已经用完了，没用了，剩下的就是树状数组思想了 
    for(int i=1;i<=m;++i){
        printf("%lld\n",ans);//注意是先输出,因为是删除前.
        scanf("%lld",&p1);
        p2=pls[p1];
        ans-=(as1[p2]+as2[p2])-(Zxt.find(0,p2,p1+1,n)+Zxt.find(p2,n,1,p1-1));
        for(int qqq=p2;qqq<=n;qqq+=qqq&(-qqq))
            Zxt.add(Zxt.root[qqq],1,n,p1);
    }
    return 0;
}