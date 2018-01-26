// luogu-judger-enable-o2
#include <cstdio>
#include <queue>
using namespace std;

priority_queue<int,vector<int>,greater<int> > high_heap;

priority_queue<int> low_heap;

int n;

void push_to_low(int x){
    if(x<high_heap.top()){
        low_heap.push(x);
    }
    else{
        int t = high_heap.top();
        high_heap.pop();
        low_heap.push(t);
        high_heap.push(x);
    }
}

void push_to_high(int x){
    if(x>low_heap.top()){
        high_heap.push(x);
    }
    else{
        int t = low_heap.top();
        low_heap.pop();
        high_heap.push(t);
        low_heap.push(x);
    }
}

int main(){
    scanf("%d",&n);
    int t;scanf("%d",&t);
    high_heap.push(t);
    printf("%d\n",high_heap.top());
    for(int i = 1;i<(n+1)/2;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        push_to_low(a);
        push_to_high(b);
        printf("%d\n",high_heap.top());
    }
    return 0;
}