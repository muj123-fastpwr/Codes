#include <iostream>
#include <windows.h>
using namespace std;
int limit, m=0, n=0;
int i=3,j=1;
void prime(){
    if(j>i){
        if(m==2){
            cout<<i<<" ";
            n++;
        }
        i++;
        j=1;
        m=0;
    }
    if(n==limit-1){
        return;
    }
    if(i%2!=0 && i%j==0)
        m++;
    j++;
    prime();
    return;
}

int main(){
    while(1){
        //system("cls");
        top:
    cout<<"nth prime numbers : ";
    cin>>limit;
    if(limit<1){
    cout<<"Input should be natural number Z"<<endl;
    goto top;
    }
    system("cls");
    cout<<2<<" ";
    prime();
    limit=m=n=0,i=3,j=1;
    cout<<endl;
    }
    return 0;
}
