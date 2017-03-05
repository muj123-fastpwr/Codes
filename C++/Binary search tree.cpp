#include <iostream>
using namespace std;
void binSearch(int arr[], int beg, int end, int key){
    if(beg<=end){
    int mid=(beg+end)/2;
    if(key<arr[mid])
    binSearch(arr, beg, mid, key);
    if(key>arr[mid])
    binSearch(arr, mid+1, end, key);
    if(key==arr[mid])
    cout<<"found "<<arr[mid]<<" at location : "<<mid<<endl;
    }
    else
    cout<<"not found"<<endl;
    return;
}
int main(){
     int arr[10]={1,2,3,4,5,6,7,8,9,10};
     binSearch(arr, 0, 9, 7);
    return 0;
}
