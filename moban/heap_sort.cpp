#include <cstdio>
using namespace std;

int l[100100],n;

void make_heap(int *li,int node_n,int len){
    int l = node_n<<1, r = (node_n<<1)+1,large = node_n;
    if(l<=len&&r<=len)
        large = li[l]>li[r]?l:r;
    else if(l<=len)
        large = l;
    if(li[large]>li[node_n]){
        int tem = li[node_n];
        li[node_n] = li[large];
        li[large] = tem;
        make_heap(li,large,len);
    }
}

void max_heap(int *li,int end){
    for(int i = end/2;i>=1;i--){
        make_heap(li,i,end);
    }
}

void heap_sort(int *li,int end){//包含1, 包含end
    max_heap(li,end);
    while(--end>=1){
        int temp = li[1];
        li[1] = li[end+1];
        li[end+1] = temp;
        make_heap(li,1,end);
    }
}

int main(){
    scanf("%d",&n);
    for(int i = 1;i<=n;i++)
        scanf("%d",&(l[i]));
    heap_sort(l,n);
    for(int i = 1;i<=n;i++)
        printf("%d ",l[i]);
    putchar('\n');
    return 0;
}