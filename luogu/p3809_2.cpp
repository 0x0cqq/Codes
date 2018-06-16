#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

const int SIZE = 1024*1024;
char ibuf[SIZE],*s,*t;
inline char read(){
    if(s==t) t=(s=ibuf)+fread(ibuf,1,SIZE,stdin);
    return s==t?-1:*s++;
}
const int MAXN = 1100000;

namespace SA{
int sa[MAXN],rk[MAXN],ht[MAXN],s[MAXN<<1],t[MAXN<<1];
int p[MAXN],b[MAXN],cur[MAXN];
//将这个东西push到其所属于的桶 
#define pushL(x) sa[cur[s[x]]--] = x
#define pushS(x) sa[cur[s[x]]++] = x
#define inducedSort(v)                                              \
    /*sa放置诱导排序后的结果,cnt确定每个桶的位置*/                  \
    fill_n(b,m,0),fill_n(sa,n,-1);/*这里把cnt置作0，sa置作-1*/      \
    for(int i = 0;i<n;i++) b[s[i]]++;/*统计每个字符出现的次数*/     \
    for(int i = 1;i<m;i++) b[i]+=b[i-1];/*确定每个桶的右端点*/      \
    for(int i = 0;i<m;i++) cur[i] = b[i] - 1;/*把起点设为S型*/      \
    for(int i=n1-1;~i;--i) pushS(i); /*逆序将S型push进桶*/          \
    for(int i = 0;i<m;i++) cur[i] = b[i-1]; /*把起点设为L型*/       \
    for(int i = 0;i<n;i++) if(sa[i]>0 && t[sa[i]-1]) pushL(sa[i]-1);\
    /*如果这个sa[i]存在数而且sa[i]-1是L型后缀，就放到对应的L桶中*/\
    for(int i = 0;i<m;i++) cur[i] = b[i]-1;/*把起点设为S型*/\
    for(int i =m-1;~i;--i) if(sa[i]>0 && !t[sa[i]-1]) pushS(sa[i]-1);\
    /*如果这个sa[i]存在数而且sa[i]-1是S型后缀，就放到对应的S桶中*/

void sais(int n,int m,int *s,int *t,int *p){
    int n1 = t[n-1] = 0,ch = rk[0] = -1,*s1 = s+n;
    // 字符串被转换为整数放置到s中，位置为[0,n-1]
    // n1 ch s1
    for(int i = n-2;~i;--i) t[i] = s[i]==s[i+1]?t[i+1]:s[i]>s[i+1];
    // 计算每个位置的后缀的类型(0->S_type,1->L_type)
    for(int i = 1;i<n;i++) rk[i] = (t[i-1]&&!t[i])?(p[n1] = i,n1++):-1; 
    // 计算LMS后缀位置，即LLL[S]SS的位置 
    // 若第i个位置为LMS串，则为在p数组里面的位置是n1；若第i个位置不为LMS串，则为-1 
    // 按出现的顺序加到rk数组里面 
    inducedSort(p);
    // 对LMS后缀进行诱导排序 
    
    for(int i = 0,x,y;;);
}

}

void init(){
    char c = read();
}

int main(){
    return 0;
}