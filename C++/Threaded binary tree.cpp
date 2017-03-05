#include <iostream>
using namespace std;
struct node{
    int info;
    node *left, *right;

    bool lth, rth;
};
class threadedBST{
public:
    node *root, *p, *q, *dummy;
    int num;
    threadedBST(){
        p=q=root=NULL;
        dummy= new node;
        dummy->left=dummy;
        dummy->right=dummy;
        dummy->lth=dummy->rth=true;
        return;
    }
    void insert(node *temp){
        if(root==NULL){
            temp=new node;
            temp->info=num;
            temp->left=dummy;
            temp->right=dummy;
            temp->lth=temp->rth=false;
            root=temp;
            dummy->left=root;
            return;
        }
        if(num==temp->info){
            cout<<"number already exists"<<endl;
            return;
        }
        if(num < temp->info){
            if(temp->lth!=false)
                insert(temp->left);
            if(temp->lth==false){
                p=temp->left;
               temp->left=new node;
               temp->lth=true;
               temp->left->info=num;
               temp->left->left=p;
               temp->left->lth=false;
               temp->left->right=temp;
               temp->left->rth=false;
               return;
            }
        }
        if(num > temp->info){
            if(temp->rth!=false)
                insert(temp->right);
            if(temp->rth==false){
                q=temp->right;
                temp->right=new node;
                temp->rth=true;
                temp->right->info=num;
                temp->right->left=temp;
                temp->right->lth=false;
                temp->right->right=q;
                temp->right->rth=false;
                return;
            }
        }
        return;
    }
    node *immediateGreater(node *temp){
        if(temp->rth==false)
            return temp->right;
        if(temp->rth!=false){
            temp=temp->right;
            while(temp->lth!=false)
            temp=temp->left;
            return temp;
        }
    }
    void inOrder(node *temp){
        while((temp=(immediateGreater(temp)))!=dummy)
            cout<<temp->info<<" ";
        return;
        return;
    }
};
int main()
{   threadedBST obj;
    int opt;
    while(1){
        cout<<"Option : ";
        cin>>opt;
        if(opt==1){
            cout<<"insert number : ";
            cin>>obj.num;
            obj.insert(obj.root);
        }
        if(opt==2){
        obj.inOrder(obj.dummy);
        cout<<endl;
        }
    }
    return 0;
}
