#include <iostream>
#include <omp.h>
using namespace std;

struct node{
    int info;
    node *next;
};
int main(){
    node *head,*current,*temp;
    head=new node;
    head->info=0;
    head->next=NULL;
    current=head;

    for(int i=1;i<10;i++){
        temp=new node;
        temp->info=i;
        temp->next=NULL;
        current->next=temp;
        current=current->next;
    }

    #pragma omp parallel
    #pragma omp single
    {
        cout<<"Single is : "<<omp_get_thread_num()<<endl;
        current=head;
        while(current){
            #pragma omp task
            cout<<current->info<<" by "<<omp_get_thread_num()<<endl;
            current=current->next;
        }
    }

    return 0;
}
