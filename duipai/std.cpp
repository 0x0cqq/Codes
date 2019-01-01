#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define maxn 100005
using namespace std;
int n,a[maxn];//整个序列
int dp[maxn];//dp[i]代表当前长度为i的上升子序列末尾元素的最小值
int len=0;//整个序列LIS的长度
int sign[maxn];//序列元素所属类别
vector<int>layer[maxn];//分层数组，一共有len层。layer[i]中的点表示这些元素：以这些元素结尾的最长上升子序列长度为i
inline int bins(int i,int val){
    int l=0,r=layer[i].size()-1;
    while(l<r){
        int m=(l+r)>>1;
        if(a[layer[i][m]]>=val)l=m+1;
        else r=m;
    }
    return l;
}
int main(){
    scanf("%d",&n);
    memset(dp,0x3f,sizeof(dp));
    dp[0]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        int length=lower_bound(dp,dp+n+1,a[i])-dp;//O(nlogn)求LIS
        dp[length]=min(dp[length],a[i]);
        //length表示以该元素结尾的最长上升子序列的长度
        layer[length].push_back(i);//加入到分层数组
        len=max(len,length);//更新整个序列的LIS长度
    }
    for(int i=1;i<=n;i++)sign[i]=1;//初始化全都为第1类，即任何LIS都不经过它们
    if(layer[len].size()==1)sign[layer[len][0]]=3;
    else for(int i=0;i<layer[len].size();i++)sign[layer[len][i]]=2;
    for(int i=len;i>=2;i--){//倒序处理分层数组，一层一层往前推
        for(int j=0;j<layer[i].size();j++){//枚举当前层的所有点
            int bh=layer[i][j];//点的编号
            if(sign[bh]>1){//如果当前节点可以向前扩展（存在LIS经过当前点）
                int l=bins(i-1,a[bh]);//二分查找，扩展的节点在序列中的值必须小于当前节点，才能保证LIS严格递增
                int r=lower_bound(layer[i-1].begin(),layer[i-1].end(),bh)-layer[i-1].begin()-1;//二分查找，扩展的点编号必须小于当前点编号，才能是“序列”
                //当前点可扩展到的前一层的点的范围是区间[l,r]
                for(int k=l;k<=r;k++)sign[layer[i-1][k]]=2;//打上标记，该节点能够被扩展到说明一定在整个序列中有某个LIS包含该点
            }
        }
        //当前层能够扩展到的前一层的点是当前层所有点能扩展到的前一层的节点的并集
        int cnt=0,pos=0;
        for(int j=0;j<layer[i-1].size();j++)if(sign[layer[i-1][j]]==2){
            cnt++;
            pos=j;
        }
        if(cnt==1)sign[layer[i-1][pos]]=3;//如果该层所有可扩展的点只能在前一层中扩展出一个节点，说明这个节点是所有LIS的必经节点。
    }
    for(int i=1;i<=n;i++)printf("%d\n",sign[i]);//不留空格打印
    printf("\n");
    return 0;
}