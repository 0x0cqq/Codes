#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

struct treap{
    int key,p,size;
    treap *left = NULL,*right = NULL,*parent;
}pool[200000];

int tot = 0;
treap *root = NULL;

void insert(int num){
    srand(time(0));
    treap *newnode = &pool[tot++];
    newnode->p = rand();
    newnode->key = num; 
    treap *now = root,*last = NULL;
    while(now!=NULL){
        if(num<now->key){
            last = now;
            now = now->left;
        }
        else{
            last = now;
            now = now->right;
        }
    }
    if(last == NULL){
        root = newnode;
    }
    else{
        if(num<last->key)
            last->left = newnode;
        else
            last->right = newnode;
    }
}

treap* find(int num){
    treap *now = root;
    while(now != NULL){
        if(num < now -> key){
            now = now->left;
        }
        else if(num>)
        else{
            now = now->right;
        }
    }
    return 
}

void print(treap *now,int n = 0){
    if(now == NULL)
        return;
    printf(":%d %d\n",now->p,now->key);
    printf("%dl:\n",n);
    print(now->left,n+1);
    printf("%dr:\n",n);
    print(now->right,n+1);
    return;
}

int main(){
    int t;
    while(scanf("%d",&t)==1){
        insert(t);
        print(root);
        putchar('\n');
    }
    return 0;
}