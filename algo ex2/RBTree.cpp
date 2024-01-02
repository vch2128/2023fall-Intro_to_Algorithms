#include<iostream>
#include<vector>
using namespace std;

struct Node {
    int key;
    Node *p;
    Node *left;
    Node *right;
    int color;  // red=0, black=1
}typedef node;

typedef node *nodeptr;

class RBTree{
public:
    nodeptr root;
    nodeptr tnil;
    RBTree(){
        tnil=new node;
        tnil->color=1;
        tnil->left=nullptr;
        tnil->right=nullptr;
        root=tnil;
    }
    void leftrotate(nodeptr x);
    void rightrotate(nodeptr x);
    void insertfixup(nodeptr z);
    void rbinsert(int n);
    nodeptr find(int a);
    nodeptr treeminimum(nodeptr x);
    void transplant(nodeptr u,nodeptr v);
    void deletefixup(nodeptr x);
    void rbdelete(int n);
    void inorderprint(nodeptr x);
};

void RBTree::leftrotate(nodeptr x){
    nodeptr y=x->right;
    x->right=y->left;
    if(y->left!=tnil){
        y->left->p=x;
    }
    y->p=x->p;
    if(x->p==tnil){
        root=y;
    }
    else if(x==x->p->left){
        x->p->left=y;
    }
    else{
        x->p->right=y;
    }
    y->left=x;
    x->p=y;
}

void RBTree::rightrotate(nodeptr x){
    nodeptr y=x->left;
    x->left=y->right;
    if(y->right!=tnil){
        y->right->p=x;
    }
    y->p=x->p;
    if(x->p==tnil){
        root=y;
    }
    else if(x==x->p->left){
        x->p->left=y;
    }
    else{
        x->p->right=y;
    }
    y->right=x;
    x->p=y;
}

void RBTree::rbinsert(int n){
    nodeptr z = new node;
    z->key=n;
    z->color=0;
    z->left=tnil;
    z->right=tnil;
    
    nodeptr y=tnil;
    nodeptr x=root;
    while(x!=tnil){
        y=x;
        if(z->key<x->key){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    z->p=y;
    if(y==tnil){
        root=z;
    }
    else if(z->key<y->key){
        y->left=z;
    }
    else{
        y->right=z;
    }
    insertfixup(z);
}

void RBTree::insertfixup(nodeptr z){
    while(z->p->color==0){
        if(z->p==z->p->p->left){    //z.p is left child
            nodeptr y=z->p->p->right;         //uncle
            //case 1: uncle is red
            if(y->color==0){
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            }
            else{ //uncle is black
                //case 2: z is right child
                if(z==z->p->right){
                    z=z->p;
                    leftrotate(z);
                }
                //case 3: z is left child
                z->p->color=1;
                z->p->p->color=0;
                rightrotate(z->p->p);
            }
        }
        else{                     //z.p is right child
            nodeptr y=z->p->p->left;         //uncle
            //case 1: uncle is red
            if(y->color==0){
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            }
            else{ //uncle is black
                //case 2: z is left child
                if(z==z->p->left){
                    z=z->p;
                    rightrotate(z);
                }
                //case 3: z is right child
                z->p->color=1;
                z->p->p->color=0;
                leftrotate(z->p->p);
            }
        }
    }
    root->color=1;
}

void RBTree::transplant(nodeptr u,nodeptr v){
    if(u->p==tnil){
        root=v;
    }
    else if(u==u->p->left){
        u->p->left=v;
    }
    else{
        u->p->right=v;
    }
    v->p=u->p;
}

nodeptr RBTree::find(int a){
    nodeptr y=root;
    while(y!=tnil && y->key!=a){
        if(a<y->key){
            y=y->left;
        }
        else{
            y=y->right;
        }
    }
    return y;
}

nodeptr RBTree::treeminimum(nodeptr x){
    while(x->left!=tnil){
        x=x->left;
    }
    return x;
}

void RBTree::deletefixup(nodeptr x){
    nodeptr w;
    while(x!=root &&x->color==1){
        if(x==x->p->left){
            w=x->p->right;
            //case 1: sibling is red
            if(w->color==0){
                w->color=1;
                x->p->color=0;
                leftrotate(x->p);
                w=x->p->right;
            }
            //case 2: sibling is black and sibling's children are black
            if(w->left->color==1 &&w->right->color==1){
                w->color=0;
                x=x->p;
            }
            else {
                //case 3: sibling is black and sibling's right black left red
                if(w->right->color==1){
                    w->left->color=1;
                    w->color=0;
                    rightrotate(w);
                    w=x->p->right;
                }
                //case 4: sibling is black and sibling's left black right red
                w->color=x->p->color;
                x->p->color=1;
                w->right->color=1;
                leftrotate(x->p);
                x=root;
            }
        }
        else{
            w=x->p->left;
            //case 1: sibling is red
            if(w->color==0){
                w->color=1;
                x->p->color=0;
                rightrotate(x->p);
                w=x->p->left;
            }
            //case 2: sibling is black and sibling's children are black
            if(w->left->color==1 &&w->right->color==1){
                w->color=0;
                x=x->p;
            }
            
            else {
                //case 3: sibling is black and sibling's left black right red
                if(w->left->color==1){
                    w->right->color=1;
                    w->color=0;
                    leftrotate(w);
                    w=x->p->left;
                }
                //case 4: sibling is black and sibling's left red right black
                w->color=x->p->color;
                x->p->color=1;
                w->left->color=1;
                rightrotate(x->p);
                x=root;
            }
        }
    }
    x->color=1;
}

void RBTree::rbdelete(int n){
    nodeptr z = find(n);
    nodeptr y=z;
    nodeptr x;
    int yc=y->color;

    if(z->left==tnil){
        x=z->right;
        transplant(z,x);
    }
    else if(z->right==tnil){
        x=z->left;
        transplant(z,x);
    }
    else{
        y=treeminimum(z->right);
        yc=y->color;
        x=y->right;
        if(y->p==z){
            x->p=y;
        }
        else{
            transplant(y,y->right);
            y->right=z->right;
            y->right->p=y;
        }
        transplant(z,y);
        y->left=z->left;
        y->left->p=y;
        y->color=z->color;
    }
    if(yc==1){
        deletefixup(x);
    }
}

void RBTree::inorderprint(nodeptr x){
    if(x!=tnil){
        inorderprint(x->left);
        cout<<"key: "<<x->key<<" parent: ";
        if(x->p!=tnil){
            cout<<x->p->key;
        }
        else{
            cout<<" ";
        }
        cout<<" color: ";
        if(x->color==0){
            cout<<"red"<<endl;
        }
        else{
            cout<<"black"<<endl;
        }
        inorderprint(x->right);
    }
}

int main(){
    int testcase,op,n,a;
    RBTree rbt;
    cin>>testcase;

    while(testcase--){
        cin>>op>>n;
        vector<int> temp;
        int k=n;
        if(op==1){
            while(k--){
                cin>>a;
                rbt.rbinsert(a);
                temp.push_back(a);
            }
            cout<<"Insert: ";
        }
        else if(op==2){
            while(k--){
                cin>>a;
                rbt.rbdelete(a);
                temp.push_back(a);
            }
            cout<<"Delete: ";
        }
        for(int i=0;i<n;i++){
            cout<<temp[i];
            if(i==n-1){
                    cout<<endl;
                }
            else{
                cout<<", ";
            }
        }
        rbt.inorderprint(rbt.root);
    }   

    return 0;
}