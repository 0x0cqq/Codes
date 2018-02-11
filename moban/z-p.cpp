#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
const int A = 4;

struct node{
    int val,size;
    node *son[2];
}pool[MAXN];

int cnt;
node *root,*null;

void update(node *r){r->size = r->son[0]->size + r->son[1]->size;}
void maintain(node *&r){

}
void newnode(node *&r,int val = 0){
    r = &pool[cnt++];
    r->val = val,r->size = 0;
    r->son[0] = r->son[1] = null;
}
void init(){
    cnt = 0;
    newnode(null);
    root = null;
}
void rotate(){

}
void insert(node *&r,int val){
    
}
void erase(node *&r,int val){

}
int kth(){

}
int rnk(){

}

int main(){

    return 0;
}