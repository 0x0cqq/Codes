#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

namespace fast_io {
    inline char read(){static const int IN_LEN=1000000;static char buf[IN_LEN],*s,*t;return s==t?(((t=(s=buf)+fread(buf,1,IN_LEN,stdin))==s)?-1:*s++) : *s++;}
    inline void read(int &x){static bool iosig;static char c;for (iosig=false,c=read();!isdigit(c);c=read()){if(c=='-')iosig=true;if(c==-1)return;}for(x=0;isdigit(c);c=read())x=((x+(x<<2))<<1)+(c^'0');if(iosig)x=-x;}
    inline void read(char *a){static char c = read();while(c!=-1&&(c==' '||c=='\n'||c=='\r'))c=read();while(c!=-1&&c!='\r'&&c!=' '&&c!='\n') *a++=c,c=read();*a=0;}
    const int OUT_LEN=1000000;char obuf[OUT_LEN],*ooh=obuf;
    inline void print(char c){if(ooh==obuf+OUT_LEN) fwrite(obuf,1,OUT_LEN,stdout),ooh=obuf;*ooh++ = c;}
    inline void print(int x){static int buf[30],cnt;if(x==0)print('0');else{if(x<0)print('-'),x=-x;for(cnt=0;x;x/=10)buf[++cnt]=x%10+48;while (cnt) print((char)buf[cnt--]);}}
    inline void print(char *a){while(*a) print(*a++);}
    inline void flush(){fwrite(obuf,1,ooh-obuf,stdout);}
}using namespace fast_io;

const int MAXN = 1100000;

//---------
namespace SA{
int sa[MAXN],rk[MAXN],ht[MAXN],s[MAXN<<1],t[MAXN<<1];
int p[MAXN],b[MAXN],cur[MAXN];
//将这个东西push到其所属于的桶 
#define pushS(x) sa[cur[s[x]]--] = x
#define pushL(x) sa[cur[s[x]]++] = x
#define inducedSort(v)                                              \
    /* v是诱导的源头 sa放置诱导排序后的结果,cur确定每个桶的位置*/           \
    fill_n(b,m,0),fill_n(sa,n,-1);/*这里把cnt置作0，sa置作-1*/         \
    for(int i = 0;i<n;i++) b[s[i]]++;/*统计每个字符出现的次数*/         \
    for(int i = 1;i<m;i++) b[i] += b[i-1];/*确定每个桶的右端点*/        \
    for(int i = 0;i<m;i++) cur[i] = b[i] - 1;/*把起点设为S型*/        \
    for(int i=n1-1;~i;--i) pushS(v[i]); /*逆序将LMS子串push进桶*/      \
    for(int i = 1;i<m;i++) cur[i] = b[i-1]; /*把起点设为L型*/         \
    for(int i = 0;i<n;i++) if(sa[i]>0 && t[sa[i]-1]) pushL(sa[i]-1); \
    /*如果这个sa[i]存在数而且sa[i]-1是L型后缀，就放到对应的L桶中*/          \
    for(int i = 0;i<m;i++) cur[i] = b[i]-1;/*把起点设为S型*/          \
    for(int i =n-1;~i;--i) if(sa[i]>0 && !t[sa[i]-1]) pushS(sa[i]-1);\
    /*如果这个sa[i]存在数而且sa[i]-1是S型后缀，就放到对应的S桶中*/

void sais(int n,int m,int *s,int *t,int *p){
    int n1 = t[n-1] = 0,ch = rk[0] = -1,*s1 = s+n;
    // 字符串被转换为整数放置到s中，位置为[0,n-1]
    for(int i = n-2;~i;--i) t[i] = s[i]==s[i+1]?t[i+1]:s[i]>s[i+1];
    // 计算每个位置的后缀的类型(0->S_type,1->L_type)
    for(int i = 1;i<n;i++) rk[i] = (t[i-1]&&!t[i])?(p[n1] = i,n1++):-1; 
    // 计算LMS后缀位置，即LLL[S]SS的位置 
    // 若第i个位置为LMS串，则为在p数组里面的位置是n1，n1即为出现顺序
    // 若 suf(i) 为LMS，则 rk[i] = n1 ,否则rk[i] = -1
    inducedSort(p); // 对 LMS 后缀进行诱导排序 
    // 给 LMS 子串命名
    for(int i = 0,x,y;i < n;i++)if(~(x = rk[sa[i]])){
        // x 是目前考虑的LMS子串 y是上一个LMS子串 ch即为名字
        // 已知x的字典序不小于y，现在要判断x与y是否相同
        // case1:长度不同必然子串不同
        if(ch < 1 || p[x+1] - p[x] != p[y+1] - p[y]) ch++;
        else for(int j = p[x],k = p[y];j<=p[x+1];j++,k++)
            if((s[j]<<1|t[j]) != (s[k]<<1|t[k])){ch++;break;}
        // case2:长度相同，所有字符都相同，两个LMS才相同 
        // 如果两个LMS子串不同，那么往后命名
        s1[y=x] = ch;//给LMS子串按照字典序命名为1->ch
    }
    //此时ch是名字的总数-1 若存在重复子串，需要递归求解
    //注意到我们不会在求解第一个sais的inducedSort的时候
    //再调用第二个sais的inducedSort，因此sa数组可以重复使用
    if(ch + 1 < n1) sais(n1,ch+1,s1,t+n,p+n1);//这里字符集的大小是ch+1!
    else for(int i = 0;i<n1;i++) sa[s1[i]] = i;
    //因为没有重复的LMS子串，可以用第一个字符的大小代表整个LMS子串的字典序
    //现在在sa中的就是彻底排好序的LMS子串（的后缀数组）了？
    for(int i = 0;i<n1;i++) s1[i] = p[sa[i]];
    //把第i个LMS子串的位置按字典序放在s1中
    inducedSort(s1);//诱导排序后即为最终结果
}
template<typename T>
int mapCharToInt(int n,const T *str){
    //一个离散化的过程
    int m = *max_element(str,str+n);// 寻找到其最大的字符
    fill_n(rk,m+1,0);// 把rk数组的字符集的大小均置为0
    for(int i = 0;i<n;i++) rk[str[i]] = 1;//标记出现过的字符
    for(int i = 0;i<m;i++) rk[i+1] += rk[i];//做前缀和
    for(int i = 0;i<n;i++) s[i] = rk[str[i]]-1;//转换成整数放入s数组
    return rk[m];//返回最大字符
}
void getHeight(int n){
    for(int i = 0;i<n;i++) rk[sa[i]] = i;//获得rank数组
    // ht[i]->suf(sa[i])与suf(sa[i-1])的LCP
    // h(i) = ht[rk[i]] 有如下结论 h(i) >= h(i-1) - 1
    for(int i = 0,h = ht[0] = 0;i<n-1;i++){
        //我们递推获得ht[rk[i]]，h是ht[rk[i-1]]-1
        int j = sa[rk[i]-1];//上一个后缀开始的地方
        while(i+h<n && j+h<n && s[i+h]==s[j+h]) h++;//寻找LCP长度
        if(ht[rk[i]] = h) --h;//赋值并对h--
    }
}
//需要保证这里的str[n]严格字典序最小
template<typename T>
void suffixArray(int n,const T *str){
    int m = mapCharToInt(++n,str);//离散化后的字符集大小
    sais(n,m,s,t,p);//获得str的后缀数组
}
}

//---------

int n;
char s[MAXN];

void solve(){
    read(s);
    n = strlen(s);
    s[n] = '0'-1;
    SA::suffixArray(n,s);
    for(int i = 1;i<=n;i++)
        print(SA::sa[i]+1),print(' ');
    print('\n');
}

int main(){
    solve();
    flush();
    return 0;
}