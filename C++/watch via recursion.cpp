#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;
void watch(int hr, int min, int sec, int flg){
    if(sec>59){
        sec=0;
        min++;
    }
    if(min>59){
        min=0;
        hr++;
    }
    if(hr>12){
        hr=1;
        if(flg==0)
        flg=1;
        else
        flg=0;
    }
    system("cls");

    if(hr<10)
    cout<<"0"<<hr;
    else
    cout<<hr;
    if(min<10)
    cout<<":0"<<min;
    else
    cout<<":"<<min;
    if(sec<10)
    cout<<":0"<<sec;
    else
    cout<<":"<<sec;
    if(flg==0)
    cout<<" am";
    else
    cout<<" pm";
    Sleep(1000);
    watch(hr, min, sec+1,flg);
    return;
}
int main()
{
    int hour, minute, second=0,flg;
    cout<<"set hour : ";
    cin>>hour;
    cout<<"set minute : ";
    cin>>minute;
    cout<<"0 for am, 1 for pm";
    cin>>flg;
    watch(hour, minute, second, flg);
    return 0;
}
