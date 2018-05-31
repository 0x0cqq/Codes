#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <cctype>
#define re register 
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

const int MAXN = 2000000;

int n,len,m[MAXN],num[1100][1100],id[MAXN];

namespace suffix_array{
#define L_type 1
#define S_type 0
    int pool[MAXN*10];
    int str[MAXN],ht[MAXN],rk[MAXN],*SA;
    inline int *ns(size_t size){
        static int cnt = 0;cnt += size;
        return pool + cnt - size;
    }
    inline bool is_lms(int *t,int x){
        return x > 0 && !t[x] && t[x-1];
    }
    inline bool is_equal(int *S,int x,int y,int *t){
        do{
            if(S[x] != S[y]) return false;
            x++,y++;
        }while(!is_lms(t,x) && !is_lms(t,y));
        return S[x] == S[y];
    }
    void induce_sort(int *S,int *SA,int *t,int *b,int *lb,int *sb,int n,int SI){
        for(re int i = 0;i<=n;i++)
            if(SA[i] > 0 && t[SA[i]-1])
                SA[lb[S[SA[i]-1]]++] = SA[i]-1;
        for(re int i = 1;i<=SI;i++)
            sb[i] = b[i]-1;
        for(re int i = n;i>=0;--i)
            if(SA[i] > 0 && !t[SA[i]-1])
                SA[sb[S[SA[i]-1]]--] = SA[i]-1;
    }
    int *SA_IS(int *S,int len,int SI){
        int n = len-1,cnt = 0;
        int *t = ns(n+1),*pos = ns(n+1);
        int *name = ns(n+1),*SA = ns(n+1);
        int *b = ns(SI+1),*lb = ns(SI+1),*sb = ns(SI+1);

        fill(b,b+SI+1,0);
        for(re int i = 0;i<=n;i++)
            b[S[i]]++;
        for(re int i = 0;i<=SI;i++)
            b[i]+=b[i-1],lb[i]=b[i-1],sb[i]=b[i]-1;

        t[n] = 0;
        for(re int i = n-1;i>=0;--i)
            t[i] = S[i+1]==S[i]?t[i+1]:S[i]>S[i+1];
        for(re int i = 1;i<=n;i++)
            if(is_lms(t,i))
                pos[cnt++] = i;

        fill(SA,SA+n+1,-1);
        for(re int i = 0;i<cnt;i++)
            SA[sb[S[pos[i]]]--] = pos[i];
        induce_sort(S,SA,t,b,lb,sb,n,SI);

        fill(name,name+n+1,-1);
        int last = -1,namecnt = 1,flag = 0;
        for(re int i = 1;i<=n;i++){
            int x = SA[i];
            if(is_lms(t,x)){
                if(last>=0 && !is_equal(S,x,last,t))
                    namecnt++;
                if(last>=0 && namecnt == name[last])
                    flag = 1;
                name[x] = namecnt;
                last = x;
            }
        }

        name[n] = 0;

        int *S1 = ns(cnt+1),p = 0;
        for(re int i = 0;i<=n;i++)
            if(name[i] > 0)
                S1[p++] = name[i];
        int *SA1;
        if(!flag){
            SA1 = ns(cnt+1);
            for(re int i = 0;i<cnt;i++)
                SA1[S1[i]] = i;
        }else SA1 = SA_IS(S1,cnt,namecnt);

        lb[0] = sb[0] = 0;
        for(re int i = 1;i<=SI;i++)
            lb[i] = b[i-1],sb[i] = b[i]-1;

        fill(SA,SA+n+1,-1);
        for(re int i = cnt-1;i>=0;--i)
            SA[sb[S[pos[SA1[i]]]]--] = pos[SA1[i]]; 
        induce_sort(S,SA,t,b,lb,sb,n,SI);
        return SA;
    } 
    void getheight(){
        for(re int i = 0;i<=len;i++)
            rk[SA[i]] = i;
        for(re int i = 0,k = 0;i<=len;i++){
            if(rk[i] == 0) k = 0;
            else{
                if(k) --k;
                int j = SA[rk[i]-1];
                while(i+k<=len && j+k<=len && str[i+k]==str[j+k]) ++k;
            }
            ht[rk[i]] = k;
        }
       /* for(int i = 0;i<=len;i++)
            printf("%d ",rk[i]);
        printf("\n");       
        for(int i = 0;i<=len;i++)
            printf("%d:%d %d %d\n",i,id[i],SA[i],ht[i]);
        printf("\n");*/
    }
    void build(){
        /*for(int i = 0;i<=len;i++)
            printf("%d ",str[i]);
        printf("\n");*/
        SA = SA_IS(str,len+1,200+n);
    }
    bool check(int x){
        if(x == 0) return true;
        static int vis[MAXN],s[MAXN],top = 0;
        while(top) vis[s[--top]] = 0;
        for(re int i = 0;i<=len;i++){
            if(ht[i] < x)
                while(top) vis[s[--top]] = 0;  
            if(!vis[id[SA[i]]]){
                vis[id[SA[i]]] = 1;
                s[top++] = id[SA[i]];
                if(top == n) return 1;
            }
        }
        return 0;
    }
}

void init(){
    read(n);
    for(re int i = 1;i<=n;i++){
        read(m[i]);
        read(num[i][1]);
        id[len] = i,suffix_array::str[len++] = 200+i;
        for(re int j = 2;j<=m[i];j++){
            read(num[i][j]);
            id[len] = i,suffix_array::str[len++] = num[i][j]-num[i][j-1]+100;
        }
    }
    //printf("len:%d\n",len);
}

void solve(){
    int b = 0,e = 1001;
    while(b!=e){
        int mid = (b+e+1)>>1;
        //usleep(100000);
        int flag = suffix_array::check(mid);
        //printf("l:%d r:%d,mid:%d F:%d\n",b,e,mid,flag);
        if(flag)
            b = mid;
        else
            e = mid-1;
    }
    printf("%d\n",b+1);
}

int main(){
    init();
    suffix_array::build();
    suffix_array::getheight();
    solve();
    return 0;
}