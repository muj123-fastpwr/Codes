#include <iostream>
#include <windows.h>
using namespace std;
void intro();
struct node{
    double info;
    char ch;
    bool flg;
    node *left, *right;
};
struct stack{
    node *data;
    stack *next;
};
class expressionTree{
public:
    stack *top, *p, *top2;
    node *root, *ptr, *qtr, *r;
    int num, flag, count, count2;
    char optr;
        expressionTree(){
            p=top=top2=NULL;
            root=NULL;
            count=count2=0;
            r=new node;
            r->info=0;
            r->left=r->right=NULL;
        }
        void push(node *temp){
            if(top==NULL){
                top=new stack;
                top->data=temp;
                top->next=NULL;
                count++;
                return;
            }
            p=new stack;
            p->data=temp;
            p->next=top;
            top=p;
            count++;
            return;
        }
        void pop(){
            if(top==NULL){
                cout<<"stack underflow"<<endl;
                return;
            }
            top=top->next;
            count--;
            return;
        }
        node *stackTop(){
            return top->data;
        }

        void insert(){
            if(flag==0){
                if(count<2){
                cout<<"few operands"<<endl;
                return;
                }
                else{
                root=new node;
                root->ch=optr;
                root->flg=false;
                root->right=stackTop();
                pop();
                root->left=stackTop();
                pop();
                push(root);
                return;
                }
            }
            if(flag==1){
                root=new node;
                root->info=num;
                root->flg=true;
                push(root);
                root->right=NULL;
                root->left=NULL;
                return;
            }
            return;
        }

        void inOrder(node *temp){
            if(root==NULL){
            cout<<"tree empty"<<endl;
            return;
            }
            if(temp->left!=NULL)
            inOrder(temp->left);
            if(temp->flg==false)
            cout<<temp->ch<<" ";
            if(temp->flg==true)
            cout<<temp->info<<" ";
            if(temp->right!=NULL)
            inOrder(temp->right);
            return;
        }

        void postOrder(node *temp){
            if(root==NULL){
            cout<<"tree empty"<<endl;
            return;
            }
            if(temp->left!=NULL)
            postOrder(temp->left);
            if(temp->right!=NULL)
            postOrder(temp->right);

            if(temp->flg==false)
            cout<<temp->ch<<" ";
            if(temp->flg==true)
            cout<<temp->info<<" ";
            return;
        }
        void print(){
        p=top;
        while(p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
        }
        }
//  Proto types for calculating expresssion tree
        void result();
        void push2(node *);
        void pop2();
        node *stackTop2();
        void calculate(node *);
};
//  Start of calculating an expression tree
void expressionTree::push2(node *temp){
    if(top2==NULL){
        top2=new stack;
        top2->data=temp;
        top2->next=NULL;
        count2++;
        return;
    }
    p=new stack;
    p->data=temp;
    p->next=top2;
    top2=p;
    count2++;
    return;
}
void expressionTree::pop2(){
    if(top2==NULL){
        cout<<"stack underflow"<<endl;
        return;
    }
    top2=top2->next;
    count2--;
    return;
}
node *expressionTree::stackTop2(){
    return top2->data;
}
void expressionTree::calculate(node *temp){
    if(root==NULL){
        cout<<"Tree empty"<<endl;
        return;
    }
    if(temp->left!=NULL)
        calculate(temp->left);
    if(temp->right!=NULL)
        calculate(temp->right);

    if(temp->left==NULL && temp->right==NULL){
        push2(temp);
        return;
    }

    if(temp->flg==false && count2>=2){
        if(temp->ch=='+'){
            qtr=stackTop2();
            pop2();
            ptr=stackTop2();
            pop2();
            temp->flg=true;
            temp->info=ptr->info + qtr->info;
            delete temp->left;
            delete temp->right;
            temp->left=temp->right=NULL;
            push2(temp);
            return;
        }
        else if(temp->ch=='-'){
            qtr=stackTop2();
            pop2();
            ptr=stackTop2();
            pop2();
            temp->flg=true;
            temp->info=ptr->info - qtr->info;
            delete temp->left;
            delete temp->right;
            temp->left=temp->right=NULL;
            push2(temp);
            return;
        }
        else if(temp->ch=='*'){
            qtr=stackTop2();
            pop2();
            ptr=stackTop2();
            pop2();
           temp->flg=true;
            temp->info=ptr->info * qtr->info;
            delete temp->left;
            delete temp->right;
            temp->left=temp->right=NULL;
            push2(temp);
            return;
        }
        else if(temp->ch=='/'){
            qtr=stackTop2();
            pop2();
            ptr=stackTop2();
            pop2();
            temp->flg=true;
            temp->info=ptr->info / qtr->info;
            delete temp->left;
            delete temp->right;
            temp->left=temp->right=NULL;
            push2(temp);
            return;
        }

    }

    return;
}
void expressionTree::result(){
           // r=stackTop2();
           // cout<<r->info;
           cout<<stackTop2()->info;
            return;
}
// End of calculating an expression Tree
int main()
{   intro();
    expressionTree obj;
    int opt;
    while(1){

        cout<<"Option : ";
        cin>>opt;
        if(opt==1){
            system("cls");
            intro();
            cout<<"number or operator : ";
            cin>>opt;
            if(opt==1){
            cout<<"number : ";
            cin>>obj.num;
            obj.flag=1;
            obj.insert();
            }
            else if(opt==2){
            cout<<"operator : ";
            cin>>obj.optr;
            obj.flag=0;
            obj.insert();
            }
        }
        else if(opt==2){
            system("cls");
            intro();
           obj.inOrder(obj.root);
            cout<<endl;
        }
        else if(opt==3){
            system("cls");
            intro();
        obj.postOrder(obj.root);
        cout<<endl;
        }
        else if(opt==4){
        obj.print();
        cout<<endl;
        }
        else if(opt==5){
        obj.calculate(obj.root);
        cout<<"Result : ";
        obj.result();
        }
        cout<<endl;
    }
    return 0;
}
void intro(){
    cout<<" Options \t Functions\n"<<endl;
    cout<<"   1 \t\t Insert\n\t\t 1: operand, 2: operator"<<endl;
    cout<<"   2 \t\t In Order"<<endl;
    cout<<"   3 \t\t Post Order"<<endl;
    cout<<"   4 \t\t Print whole Stack"<<endl;
    cout<<"   5 \t\t Calculate Expression Tree"<<endl<<endl;
}
