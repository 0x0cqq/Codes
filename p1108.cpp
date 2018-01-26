#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

struct ac{
    vector<int> num;
    int pos[1000];
    inline int f(){
        for(vector<int>::reverse_iterator i = num.rbegin();i!=num.rend();i++){
            if(*i!=-1)
                return *i;
        }
        return -10000;
    }
    int g(){
        for(int i = num.size()-1;i>=0;i--){
            if(num[i]!=-1&&num[i]!=0)
                return i;
        }
        return 0;
    }
};

vector<ac> k;
int w[5000],n;

void chushihua(){
    for(vector<ac>::reverse_iterator i = k.rbegin();i!=k.rend();i++){
        memset(i->pos,-1,4000);
    }
}

int cal(vector<ac>::reverse_iterator i,int now){
    int res = 0;
    if(i->pos[now]!=-1)
        return i->pos[now];
    else if(i >= k.rend()-1){
        return 1;
    }
    else{ 
        for(int j = now;j>=0;j--){
            if((i+1)->num[j]!=-1&&(i+1)->num[j] < i->num[now])
                res+=cal(i+1,j);
        }
    }
    return i->pos[now] = res;
}


int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        scanf("%d",w+i);
    }
    ac ne;
    ne.num.push_back(w[n-1]);
    k.push_back(ne);
    for(int z = n-2;z>=0;z--){
        bool flag = 1;
        for(vector<ac>::iterator i = k.begin();i!=k.end();i++){
            if(w[z]<i->f()&&flag){
                i->num.push_back(w[z]);
                flag = 0;
                //printf("<:%d,%d\n",i->f(),w[z]);
            }
            else{
                i->num.push_back(-1);
                //printf(">=:%d,%d\n",i->f(),w[z]);
            }
            if(w[z]==i->f())
                flag = 0;

        }
        //printf("\n");
        if(w[z]>k.back().f()){
            ac ne;
            for(int i = 0;i<n-z;i++)
                ne.num.push_back(-1);
            ne.num.push_back(w[z]);
            k.push_back(ne);
            continue;
        }
    }
    printf("%lu ",k.size());
    chushihua();
    long long ans = 0;
    for(int i = k.back().num.size()-1;i>=0;i--){
        if(k.back().num[i]!=-1)
            ans+=cal(k.rbegin(),i);
    }
    //printf("\n%d\n",k[0].pos[1]);
    printf("%lld\n",ans);
    //printf("%d %d\n",cal(k.rbegin(),k.back().g()),k.back().g());
    return 0;
}