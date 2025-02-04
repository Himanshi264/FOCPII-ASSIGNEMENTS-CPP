#include<iostream>
#include<limits.h>
using namespace std;
int main(){
    int max=INT_MIN;
    int min=INT_MAX;
    int smax=INT_MIN,smin=INT_MAX;
    int size;
    cout<<"Enter the size of array : ";
    cin>>size;
    int arr[size];
    cout<<"\nEnter the elements of array : \n\n";
    for(int i=0;i<size;i++){
        cout<<"Enter value "<<i+1<<" : ";
        cin>>arr[i];
        cout<<"\n";
    }
    cout<<"Array in reverse order : ";
    for(int i=size-1;i>=0;i--){
        cout<<arr[i]<<" ";
    }
    for(int j=0;j<size;j++){
        if(arr[j]>max){
            smax=max;
            max=arr[j];
        }
        else if(max!=arr[j] && arr[j]>smax){
            smax=arr[j];
        }
    }
    for(int i=0;i<size;i++){
        if(arr[i]<min){
            smin=min;
            min=arr[i];
        }
        else if(arr[i]<smin && min!=arr[i]){
            smin=arr[i];
        }
    }
    cout<<endl<<"The second minimum element is : "<<smin<<endl;
    cout<<"The second maximum element : "<<smax;
    return 0;
}