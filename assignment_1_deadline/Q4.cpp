#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"Enter the value of n : ";
    cin>>n;
    int minr=0,minc=0,maxr=n-1,maxc=n-1;
    int tn=n*n;
    int count=0;
    int arr[n][n];
    int spiral[n][n];
    cout<<endl<<"Enter values of the matrix for generating spiral : "<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }
    cout<<endl<<"The spiral pattern of the above matrix : "<<endl;
    while(count<tn){
        for(int i=minc;i<=maxc;i++){
            spiral[minr][i]=arr[count/n][count%n]; 
            count++;  
        }
        minr++;
        
        if(count>=tn){
            break;
        }
        for(int i=minr;i<=maxr;i++){
            spiral[i][maxc]=arr[count/n][count%n];
            count++;
        }
        maxc--;
        
        if(count>=tn){
            break;
        }
        for(int i=maxc;i>=minc;i--){
            spiral[maxr][i]=arr[count/n][count%n];
            count++;
        }
        maxr--;
        
        if(count>=tn){
            break;
        }
        for(int i=maxr;i>=minr;i--){
            spiral[i][minc]=arr[count/n][count%n];
            count++;
        }
        minc++;
        
        if(count>=tn){
            break;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<spiral[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
