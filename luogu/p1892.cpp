#include <cstdio>
using namespace std;

int f[1100],n,m;
bool r[1100],t[1100];
//f为父节点编号，r为与父节点的关系（1为敌人，0为朋友）
//t为集合是否纯净的记号，0纯净，1混合

int find_r(int x){//与根的关系
    if(f[x] == x) 
        return 0;
    else 
        return r[x]^find_r(f[x]);
}

int find(int x){
    if(f[x] == x)
        return x;
    else{
        int w = find(f[x]);
        r[x] ^= r[f[x]];//r[f[x]]即为父节点与根的关系
        return f[x] = w;
    }
}
int ans;

void un(int x,int y,bool re){
    int x1 = find(x),y1 = find(y);
    re ^= find_r(x) ^ find_r(y);//确定根结点的关系
    if(x1!=y1){
        //printf("x:%d y:%d x1:%d y1:%d re:%d\n",x,y,x1,y1,re);
        if(t[x1] == 1 && t[y1] == 1)//两个都是混合集合
            ans -= 2;
        else if(!(t[x1] == 0 && t[y1] == 0 &&re == 1))//除了两个都是纯净集合而且不互为敌人
            ans -= 1;
        f[y1] = x1;
        t[x1] = ((t[x1]) || (t[y1]) || re);//只要这些条件满足一个，x1代表的集合就是一个混合集合
        t[y1] = 0;
        r[y1] = re,r[x1] = 0;//关系更新
    }
}



int main(){
    //freopen("1.out","r",stdin);
    //freopen("4.out","w",stdout);
    scanf("%d %d",&n,&m);
    for(int i = 1;i<=n;i++)
        f[i] = i;
    ans = n;
    for(int i = 0;i<m;i++){
        char s[20];int a,b;
        scanf("%s",s);
        scanf("%d %d",&a,&b);
        un(a,b,s[0] == 'E');
        printf("!!!\n");
    }
    printf("%d\n",ans);
    return 0;
}