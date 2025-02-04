#include<iostream>
using namespace std;
int main(){
    int n,m;
    cout<<"Enter number of rows :";
    cin>>n;
    cout<<"Enter number of columns : ";
    cin>>m;
    int arr[n][m];
    int transpose[m][n];
    cout<<endl<<"Enter the elements of "<<n<<"X"<<m<<" matrix\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            transpose[j][i]=arr[i][j];
        }
    }
    for(int i=0;i<m;i++){
        int j=0;
        int k=(n-1);
        while(j<k){
            int temp=transpose[i][k];
            transpose[i][k]=transpose[i][j];
            transpose[i][j]=temp;
            j++;
            k--;
        }
    }
    cout<<endl<<"THE 90 DEGREE CLOCKWISE ROTATION OF THE GIVEN MATRIX IS : "<<endl<<endl;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<transpose[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}