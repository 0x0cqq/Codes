#include <cstdio>
#include <algorithm>
using namespace std;

inline int lowbit(int x){
    return x&(-x);
}

int n,m,num[51000],ans[201000],last[1001000];

int tree[201000];

struct que{
    int id,l,r,res;
}qq[1000000];

bool cmp(que a,que b){
    if(a.r!=b.r)
        return a.r<b.r;
    return a.l<b.l;
}

inline void insert(int nown,int val){
    for(int i = nown;i<=n;i+=lowbit(i))
        tree[i]+=val;	
}

inline int query(int nown){
    int res = 0;
    for(int i = nown;i>0;i-=lowbit(i))
        res += tree[i];
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        scanf("%d",&num[i]);
    scanf("%d",&m);
    for(int i = 0;i<m;i++){
        scanf("%d %d",&qq[i].l,&qq[i].r);
        qq[i].id = i;
    }
    sort(qq,qq+m,cmp);
    int end = 0;
    for(int i = 0;i<m;i++){
        while(end<qq[i].r){//更新last&树状数组
            end++;
            if(last[num[end]]!=0)//原来出现过就抹去last位置的数
                insert(last[num[end]],-1);
            insert(end,1);//树状数组加入新标记
            last[num[end]] = end;//更新last值
        }
        ans[qq[i].id] = query(qq[i].r) - query(qq[i].l-1);
    }
    for(int i = 1;i<=m;i++)
        printf("%d\n",ans[i]);
    return 0;
}