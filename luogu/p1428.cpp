#include <cstdio>
#include <algorithm>
#define lowbit(x) (x&(-x))
using namespace std;

int n,range;

int tree[10000];

struct fish{
    int id;
    int num;
}d[10000];

bool cmp1(fish a,fish b){
    return a.num<b.num;
}

bool cmp2(fish a,fish b){
    return a.id<b.id;
}

void add(int nown){
    while(nown<=range){
        tree[nown]++;
        nown+=lowbit(nown);
    }
}

int query(int need){
    int res = 0;
    while(need>0){
        res+=tree[need];
        need-=lowbit(need);
    }
    return res;
}

int main(){
    scanf("%d",&n);
    for(int i = 0;i<n;i++){
        d[i].id = i;
        scanf("%d",&(d[i].num));
    }
    sort(d,d+n,cmp1);
    int last = d[0].num,now = 1;
    for(int i = 0;i<n;i++){
        if(last!=d[i].num)
            now++;
        last = d[i].num;
        d[i].num = now;
    }
    range = now;
    sort(d,d+n,cmp2);
    for(int i = 0;i<n;i++){
        //printf(":%d\n",d[i].num);
        add(d[i].num);
        printf("%d ",query(d[i].num-1));
    }
    putchar('\n');
    return 0;
}
