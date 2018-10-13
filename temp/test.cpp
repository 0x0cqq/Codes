#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+7;
const double eps=1e-4;

int n,m,R,x[maxn],y[maxn],r[maxn];
int p[maxn],q[maxn];
double Temp,c=0.997,x_ans,y_ans;
double xa[10]={0,0,1,-1,1,-1,1,-1};
double ya[10]={1,-1,0,0,1,-1,-1,1};

int f(double xx,double yy){
    //if(Temp>0.5*R)printf("%0.7f %0.7f\n",xx,yy);
    int ans=0;double dis=0,rr=R;
    for(int i=1;i<=n;i++){
        dis=sqrt((xx-x[i])*(xx-x[i])+(yy-y[i])*(yy-y[i]));
        rr=min(rr,dis-r[i]);
    }
    if(rr<eps)return -1e9;
    for(int i=1;i<=m;i++){
        dis=sqrt((xx-p[i])*(xx-p[i])+(yy-q[i])*(yy-q[i]));
        if(dis+eps<rr)ans++;
    }
    return ans;
}
int main(){
    //srand(time(0));
    scanf("%d%d%d",&n,&m,&R);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&x[i],&y[i],&r[i]);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&p[i],&q[i]);
    for(int i=1;i<=m;i++)
        x_ans+=p[i],y_ans+=q[i];
    x_ans/=m; y_ans/=m;
    
    Temp=R*20;
    double xx,yy;int del = 0,la = -1e9,nw = -1e9;
    while(Temp>eps){
        for(int k=0;k<8;k++){
            double xxx=x_ans+xa[k]*Temp*(rand()*1.0/RAND_MAX);
            double yyy=y_ans+ya[k]*Temp*(rand()*1.0/RAND_MAX);
            int tmp = f(xxx,yyy);
            if(tmp > nw) nw = tmp,xx = xxx,yy = yyy;
        }
        del=nw-la;
        if(del>=0 || exp(double(del)/Temp*100)*RAND_MAX>rand())
            x_ans=xx,y_ans=yy,la = nw;
        Temp*=c;
    }
    int ans=-1;
    ans=max(ans,f(x_ans,y_ans));
    printf("%d\n",ans);
    return 0;
}