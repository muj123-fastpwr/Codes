#include <iostream>
#include <windows.h>
using namespace std;
struct list;
struct node{
    char info;
    node *below;
    list *right;
};
struct list{
    char info;
    int weight;
    list *r;
};

class graph{
public:
    node *base, *p;
    list *q, *t;
    char chL, chN;
    int w;
    graph(){
        base=NULL;
        q=NULL;
        w=0;
    }
//================================
    void insertVertix(node *temp){
        if(base==NULL){
            temp=new node;
            temp->info=chN;
            temp->below=NULL;
            temp->right=NULL;
            base=temp;
            return;
        }
        while(temp!=NULL){
            if(temp->info==chN){
            cout<<"Vertex already Available"<<endl;
            return;
        }
            p=temp;
            temp=temp->below;
        }
        temp=p;
        temp->below=new node;
        temp->below->info=chN;
        temp->below->below=NULL;
        temp->below->right=NULL;
        return;
    }
//====================================
    void connectVerticex(node *temp){
        if(base==NULL){
            cout<<"Graph empty"<<endl;
            return;
        }
        while(temp!=NULL){
            if(temp->info==chN){
                if(temp->right==NULL){
                    temp->right=new list;
                    temp->right->info=chL;
                    temp->right->weight=w;
                    temp->right->r=NULL;
                    return;
                }
                if(temp->right!=NULL){
                    q=temp->right;
                    while(q->r!=NULL){
                        if(q->info==chL){
                            cout<<"Vertex already connected"<<endl;
                            return;
                        }
                        q=q->r;
                        }
                    q->r=new list;
                    q->r->info=chL;
                    q->r->weight=w;
                    q->r->r=NULL;
                    return;
                }
            }
            p=temp;
            temp=temp->below;
        }
    if(p->below==NULL){
        insertVertix(p);
        connectVerticex(p->below);
    }
    }
//=============================
    void print(node *temp){
        if(base==NULL){
            cout<<"Graph empty"<<endl;
            return;
        }
        while(temp!=NULL){
            cout<<"Vertex "<<temp->info<<"  is connected with  ";
            q=temp->right;
            while(q!=NULL){
                cout<<q->info<<"="<<q->weight<<" ";
                q=q->r;
            }
            cout<<endl;
            temp=temp->below;
        }
        return;
    }
//==============================
    void deleteEdge(node *temp){
        if(base==NULL){
            cout<<"Graph empty"<<endl;
            return;
        }
        while(temp!=NULL){
            if(temp->info==chN && temp->right!=NULL){
                q=temp->right;
                while(q!=NULL){
                    if(temp->right->info==chL){
                        t=temp->right;
                        temp->right=t->r;
                        delete t;
                        t=NULL;
                        return;
                    }
                    if(q->r->info==chL){
                        t=q->r;
                        q->r=t->r;
                        delete t;
                        t=NULL;
                        return;
                    }
                    q=q->r;
                }
            }
            temp=temp->below;
        }
    }
//================================
    void deleteVertex(node *temp){
        if(base==NULL){
            cout<<"Graph empty"<<endl;
            return;
        }
        if(base->info==chN){
            p=base;
            while(p->right!=NULL){
                    t=p->right;
                    p->right=t->r;
                    delete t;
                    t=NULL;
                }
                chL=base->info;
                base=base->below;
                delete p;
                deleteEdge2(base);
                return;
        }
        while(temp!=NULL){                  // problem b/w these two lines
            if(temp->below->info==chN){     // these lines
                p=temp->below;
                while(p->right!=NULL){
                    t=p->right;
                    p->right=t->r;
                    delete t;
                    t=NULL;
                }
                temp->below=p->below;
                chL=p->info;
                delete p;
                deleteEdge2(base);
                return;
            }
            temp=temp->below;
        }
    }
//===============================
    void deleteEdge2(node *temp){
        if(base==NULL){
            cout<<"Graph empty"<<endl;
            return;
        }
       while(temp!=NULL){
                q=temp->right;
                while(q!=NULL){
                    if(temp->right->info==chL){
                        t=temp->right;
                        temp->right=t->r;
                        delete t;
                        t=NULL;
                        break;
                    }
                    if(q->r->info==chL){
                        t=q->r;
                        q->r=t->r;
                        delete t;
                        t=NULL;
                        break;
                    }
                    q=q->r;
                }

            temp=temp->below;
        }
    return;
    }
};
//=============================
int main(){
    graph obj;
    int opt;
    while(1){

        cout<<"option : ";
        cin>>opt;
        if(opt==1){
            system("cls");
            cout<<"insert vertex : ";
            cin>>obj.chN;
            obj.insertVertix(obj.base);
        }
        else if(opt==2){
            system("cls");
            cout<<"search vertex : ";
            cin>>obj.chN;
            cout<<"Join with vertex : ";
            cin>>obj.chL;
            cout<<"weight : ";
            cin>>obj.w;
            obj.connectVerticex(obj.base);
        }
        else if(opt==3){
            obj.print(obj.base);
        }
        else if(opt==4){
            cout<<"delete edge b/w : ";
            cin>>obj.chN;
            cout<<"And : ";
            cin>>obj.chL;
            obj.deleteEdge(obj.base);
        }
    }
    return 0;
}
