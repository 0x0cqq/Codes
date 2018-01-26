#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#define MAXN 100
using namespace std;

struct bigint{
    int a[100];
    bigint(){
        memset(a,-1,sizeof(a));
    }
    void operator = (const string w){
        memset(a,-1,sizeof(a));
        for(int i = w.size()-1,t = 0;i>=0;i--,t++){
            a[t] = w[i]-48;
        }
    }
    void operator = (const int w){
        memset(a,-1,sizeof(a));
        int t = w;
        for(int i = 0;t!=0;i++){
            a[i] = t%10;
            t/=10;
        }
        if(w == 0)
            a[0] = '0';
    }
    bigint operator + (const bigint w)const{
        bigint c;bigint d = *this;bigint e = w;
        int plus = 0,i = 0;
        for(i = 0;d.a[i]!=-1||e.a[i]!=-1;i++){
            if(d.a[i] == -1) d.a[i] = 0;
            if(e.a[i] == -1) e.a[i] = 0;
            c.a[i] = plus + d.a[i]+e.a[i];
            plus = c.a[i]/10;c.a[i]%=10;
            //printf("i:%d\n",i);
        }
        while(plus!=0){
            if(c.a[i] == -1) c.a[i] = 0;
            c.a[i] += plus;
            plus = c.a[i]/10;c.a[i]%=10;
            i++;
        }
        return c;
    }
    bigint operator *(const int w)const{
        bigint c;int t = w;
        if(w == 0||(a[1] == -1 && a[0] == 0)){
            c.a[0] = 0;
            return c;
        }
        for(int i = 0;t!=0;i++){
            int p = t%10,plus = 0,j;
            for(j = 0;a[j]!=0;j++){
                if(c.a[i+j] == -1) c.a[i+j] = 0;
                int tmp = a[j]*p+c.a[i+j]+plus;
                //printf("j:%d,plus:%d\n",j,plus);
                plus = tmp/10;tmp%=10;
            }
            //printf("plus!\n");
            while(plus!=0){
                if(c.a[i+j] == -1)c.a[i+j] = 0;
                c.a[i+j] += plus;
                plus = c.a[i+j]/10;c.a[i+j]%=10;
                j++;
            }
            t/=10;
        }
        return c;
    }
    bigint operator *(const bigint w)const{
        bigint c;bigint t = w;
        if((t.a[1] == -1 &&t.a[0] == 0)||(a[1] == -1 &&a[0] == 0)){
            c.a[0] = 0;
            return c;
        }
        for(int i = 0;t.a[i]!=-1;i++){
            int p = t.a[i],plus = 0,j;
            for(j = 0;a[j]!=-1;j++){
                if(c.a[i+j] == -1) c.a[i+j] = 0;
                int tmp = a[j]*p+c.a[i+j]+plus;
                //printf("j:%d,plus:%d\n",j,plus);
                plus = tmp/10;tmp%=10;
            }
            //printf("plus!\n");
            while(plus!=0){
                if(c.a[i+j] == -1)c.a[i+j] = 0;
                c.a[i+j] += plus;
                plus = c.a[i+j]/10;c.a[i+j]%=10;
                j++;
            }
        }
        return c;
    }
    bool operator > (const bigint w)const{
        int a_len = 0,b_len = 0;
        for(int i = 0;i<MAXN;i++){
            if(a[i]==-1)
                a_len = i;
            if(w.a[i] == -1)
                b_len = i;
            if(a_len!=0&&b_len!=0)
                break;   
        }
        if(a_len!=b_len)
            return a_len>b_len;
        else{
            for(int i = a_len;i>=0;i--){
                if(a[i]!=w.a[i])
                    return a[i]>w.a[i];
            }
        }
        return false;
    }
    bool operator < (const bigint w)const{
        int a_len = 0,b_len = 0;
        for(int i = 0;i<MAXN;i++){
            if(a[i]==-1)
                a_len = i;
            if(w.a[i] == -1)
                b_len = i;
            if(a_len!=0&&b_len!=0)
                break;   
        }
        if(a_len!=b_len)
            return a_len<b_len;
        else{
            for(int i = a_len;i>=0;i--){
                if(a[i]!=w.a[i])
                    return a[i]<w.a[i];
            }
        }
        return false;
    }
    void print(bool h = 1){
        int len = 0;
        for(int i = 0;i<MAXN;i++){
            if(a[i]==-1){
                len = i;
                break;
            }   
        }
        for(int i = len-1;i>=0;i--)
            printf("%d",a[i]);
        if(h)
            putchar('\n');
        return;
    }
};

int n,m,num[200][200];

bigint n_2[1000][1000],dd[1000][1000];

inline bigint n2(int t,int k){
    if(n_2[t][k].a[0]!=0)
        return n_2[t][k];
    else{
        return n_2[t][k] = n_2[t][1]*k;
    }
}

bigint dp(int row,int l,int r,int t){
    bigint res;res = 0;
    memset(dd,0,sizeof(dd));
    if(l>r)
        return res;
    else if(l == r)
        res = n2(t,num[row][l]);
    else if(dd[l][r].a[0]!=0)
        res = dd[l][r];
    else{
        bigint x,y;
        x = n2(t,num[row][l])+dp(row,l+1,r,t+1);
        y = n2(t,num[row][r])+dp(row,l,r-1,t+1);
        if(x>y)
            res = x;
        else
            res = y;
    }
    printf("t:%d l:%d r:%d res:",t,l,r);
    res.print(); 
    return dd[l][r] = res;
}

int main(){
    scanf("%d %d",&n,&m);
    {
        bigint a,b;
        a = n;b = m;
        (a*b).print();
    }
    printf("!\n\n");
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            int tmp;
            scanf("%d",&tmp);
            num[i][j] = tmp;
        }
    }
    printf("!!!!!!!!!\n");
    /*for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            num[i][j].print(0);
            putchar(' ');
        }
        putchar('\n');
    }*/
    bigint a;
    a = 1;
    for(int i = 1;i<=m;i++){
        a = a*2;
        n_2[i][1] = a;
    }
    bigint ans;ans = 0;
    for(int i = 0;i<n;i++){
        printf("i:%d\n",i);
        bigint tmp;tmp = dp(i,0,m-1,1);
        //tmp.print();
        ans = tmp+ans;
        //ans.print();
    }
    ans.print();
    return 0;
}