#include <cstdio>
using namespace std;

struct node{
    node *left,*right;
    char name;
    node(char na = '\0',node *l = NULL,node *r = NULL){
        left = l;
        right = r;
        name = na;
    }
};

node root;

int n;

node* ch(node* now,char x){
    node* ans = NULL;
    if(now == NULL)
        return NULL;
    if(now->name == x)
        return now;
    if((ans = ch(now->left,x)))
        return ans;
    if((ans = ch(now->right,x)))
        return ans;
    return ans;
}

void print(node *now){
    if(now == NULL||now->name == '*')
        return;
    putchar(now->name);
    print(now->left);
    print(now->right);
    return;
}

int main(){
    scanf("%d",&n);
    getchar();getchar();
    for(int i = 0;i<n;i++){
        char a,b,c;
        a = getchar();b = getchar();c = getchar();
        getchar();getchar();
        if(i == 0){
            node *tmp = new node(a);
            root.left = tmp;
        }
        node *f = ch(&root,a);
        node *tem = new node(b);
        f->left = tem;
        tem = new node(c);
        f->right = tem;
    }
    print(root.left);
    putchar('\n');
    return 0;
}
