struct Node {
  int val,size;
  Node *ls,*rs;
  Node():val(0),size(0),ls(NULL),rs(NULL){}
  Node(int v,int s,Node *l,Node*r){
    val = v,size = s,ls = l,rs = r;
  }
  bool isleaf(){
    return ls == NULL;
  }
  void pushup(){
    size = ls->size+rs->size;

  }
}pool[MAXN];

Node *newnode(int val,int size,Node *ls,Node *rs){
  static int cnt = 0;
  pool[cnt] = Node(val,size,ls,rs);
  return &pool[cnt++];
}





void insert(Node *&cur,int x){
  if(cyr == NULL) cur = newnode(x,1,NULL,NULL);
  if(cur->isleaf()){
    cur->ls = newnode(min(x,cur->val),1,NULL,NULL);
    cur->rs = newnode(max(x,cur->val),1,NULL,NULL);
  } else {
    if()
  }
}



void erase(Node *cur, Node *fa, int x){
  if(cur->isleaf()){
    if(fa->ls == cur) *fa = *fa
  }
}


int rank(Node * cur,int x){
  if(cur->isleaf()){
    if(x > cur->val) {
      return 2;
    }
    else{
      return 1;
    }
  }
  else{
    if(x >cur->ls->val) {
      return rnk(cur->rs,x)+cur->ls->size;
    }
    else {
      return rnk(cur->ls,x);
    }
  }
}


int kth(Node *cur,int k){
  if(cur->isleaf()) {
    return cur -> val;
  }
  else {
    if(k > cur->ls->size) {
      return kth(cur->rs,k-cur->ls->size);
    }
    else {
      return kth(cur->ls,k);
    }
  }
}
