#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;
const int MAXN = 1100000;
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

int n;
int TT[MAXN];

namespace suffix_array{
#define L_type 1
#define S_type 0
    int pool[MAXN*16],cnt = 0;
    int *ns(const size_t size){
        int tmp = cnt;cnt += size;
        return pool+tmp;
    }
    bool is_LMS(int *t,int x){
        return x > 0&&!t[x]&&t[x-1];
    }
    bool is_equal(int *S,int x,int y,int *t){
        do{
            if(S[x]!=S[y]) return false;
            x++,y++;
        }while(!is_LMS(t,x) && !is_LMS(t,y));
        return S[x] == S[y];
    }
    void induced_sort(int *S,int *SA,int *t,int *b,int *lb,int *sb,int n,int SI){
        for(int i = 0;i<=n;i++)
            if(SA[i]>0 && t[SA[i]-1])
                SA[lb[S[SA[i]-1]]++] = SA[i]-1;
        for(int i = 1;i<=SI;i++)
            sb[i] = b[i]-1;
        for(int i = n;i>=0;i--)
            if(SA[i]>0 && !t[SA[i]-1])
                SA[sb[S[SA[i]-1]]--] = SA[i]-1;
    }
    int* SAIS(int *S,int len,int SI){
        int n = len-1;
        int *t = ns(n+1),*pos = ns(n+1);
        int *name = ns(n+1),*SA = ns(n+1);
        int *b = ns(SI+1);
        int *lb = ns(SI+1),*sb = ns(SI+1);

        memset(b,0,sizeof(int)*(SI+1));
        for(int i = 0;i<=n;i++)
            b[S[i]]++;
        for(int i = 1;i<=SI;i++)
            b[i] += b[i-1],lb[i] = b[i-1],sb[i] = b[i]-1;

        t[n] = S_type;
        for(int i = n-1;i>=0;i--)
            t[i] = S[i]==S[i+1]?t[i+1]:S[i] > S[i+1];
        /*/
        printf("t: ");
        for(int i = 0;i<=n;i++){
            printf("%d ",t[i]);
        }
        printf("\n");
        /*/
        int cnt = 0;
        for(int i = 1;i<=n;i++)
            if(!t[i] && t[i-1])
                pos[cnt++] = i;
        
        /*/
        printf("pos: ");
        for(int i = 0;i<cnt;i++){
            printf("%d ",pos[i]);
        }
        printf("\n");
        /*/

        fill(SA,SA+n+1,-1);
        for(int i = 0;i<cnt;i++)
            SA[sb[S[pos[i]]]--] = pos[i];
        induced_sort(S,SA,t,b,lb,sb,n,SI);
        
        /*/
        printf("SA1: ");
        for(int i = 0;i<=n;i++){
            printf("%d ",SA[i]);
        }
        printf("\n");
        /*/
        fill(name,name+n+1,-1);
        int last=-1,namecnt = 1;
        bool flag = 0;
        for(int i = 1;i<=n;i++){
            int x = SA[i];
            if(is_LMS(t,x)){
                if(last>=0&&!is_equal(S,x,last,t))
                    namecnt++;
                if(last>=0&&namecnt==name[last])
                    flag = 1;
                name[x] = namecnt;
                last = x;
            }
        }
        name[n] = 0;

        int *S1 = ns(cnt);
        int p = 0;
        for(int i = 0;i<=n;i++)
            if(name[i]>=0)
                S1[p++] = name[i];
        
        int *SA1;
        if(!flag){
            SA1 = ns(cnt+1);
            for(int i = 0;i<cnt;i++)
                SA1[S1[i]] = i;
        }else SA1 = SAIS(S1,cnt,namecnt);

        lb[0] = sb[0] = 0;
        for(int i = 1;i<=SI;i++)
            lb[i] = b[i-1],sb[i] = b[i]-1;

        fill(SA,SA+n+1,-1);
        for(int i = cnt-1;i>=0;i--)
            SA[sb[S[pos[SA1[i]]]]--] = pos[SA1[i]];
        /*/
        printf("SA2: ");
        for(int i = 0;i<=n;i++){
            printf("%d ",SA[i]);
        }
        printf("\n");
        /*/        
        induced_sort(S,SA,t,b,lb,sb,n,SI);
        return SA;
    }
}

void init(){
    char c = read();
    while(c!=-1 && c!= '\n')
        TT[n++] = c,c = read();
    TT[n] = 0;
    //printf("%d\n",n);
    //read(T);n = strlen(T);
}

void solve(){
    int *t = suffix_array::SAIS(TT,n+1,128);
    //printf("ans: ");
    for(int i = 1;i<=n;i++)
        print(t[i]+1),print(' ');
    print('\n');
}

int main(){
    init();
    solve();
    flush();
    return 0;
}