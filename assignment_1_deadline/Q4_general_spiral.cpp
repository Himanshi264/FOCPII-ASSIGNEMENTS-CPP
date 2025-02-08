#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"Enter the number of rows : ";
    cin>>n;
    int arr[n][n];
    int count=0,tn=n*n;
    cout<<"Enter the elements of the array : ";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }
    int minr=0,minc=0,maxr=n-1,maxc=n-1;
    while(count<tn){
        for(int j=minc;j<=maxc;j++){
            cout<<arr[minr][j]<<" ";
            count++;
        }
        minr++;
        if(count>=tn){
            break;
        }
        for(int i=minr;i<=maxr;i++){
            cout<<arr[i][maxc]<<" ";
            count++;
        }
        maxc--;
        if(count>=tn){
            break;
        }
        for(int j=maxc;j>=minc;j--){
            cout<<arr[maxr][j]<<" ";
            count++;
        }
        maxr--;
        if(count>=tn){
            break;
        }
        for(int i=maxr;i>=minr;i--){
            cout<<arr[i][minc]<<" ";
            count++;
        }
        minc++;
        if(count>=tn){
            break;
        }
}
return 0;
}
