#include <cstdio>
#include <vector>
using namespace std;

int n,m,k,x,s_max[100000],e_max[100000];

vector<pair<int,int> > w;

bool cmp(pair<int,int> a,pair<int,int> b){
    double c = double(a.second)/a.first;
    double d = double(b.second)/b.first;
    if(c!=d)
        return c>d;
    else{
        return a.first>b.first;
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    int t = 0;
    for(int i = 0;i<k;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        w.push_back(make_pair(a,b));
    }
    w.push_back(make_pair(1,1));
    scanf("%d",&x);
    sort(w.begin(),w.end(),cmp);
    for(auto i:w){
        for(int t = i.first;;t++){
            if(s_max[t-i.first]+i.second>s_max[t])
                s_max[t] = s_max[t-i.first]+i.second;
            if(s_max[t] > m)
                break;
        }
    }
    for(int t = x;;t++){
        if(e_max[t-x]+9 >e_max[t])
            e_max[t] = e_max[t-x]+9;
        if(e_max[t] > n)
            break;
    }
    for(int i = 0;i<100000;i++){
        if(s_max[i]>=m||e_max[i]>=n){
            if(s_max[i]>=m&&e_max[i]>=n)
                printf("All Dies\n");
            else if(s_max[i]>=m)
                printf("EnderPearl Wins\n%d\n",n-e_max[n]);
            else if(e_max[i]>=n){
                printf("Skeleton Wins\n%d\n",m-s_max[i]);
            }
            return 0;
        }
    }
}