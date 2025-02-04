#include<iostream>
using namespace std;
int main(){
    int n;
    int flag=1;
    cout<<"\nEnter a positive number to check for prime : ";
    cin>>n;
    if((n<0) || (n==0)){
        cout<<"\nPlease enter a positive number";
    }
    else{
        if(n==1){
            cout<<"\n1 is neither prime nor composite ";
        }
        else if(n==2){
            cout<<"\n2 is a prime number ";
        }
        else{
            for(int i=2;i<n;i++){
                if(n%i==0){
                    flag=0;
                }
            }
            if(flag==0){
                cout<<"\nFactors of "<<n<<" are : ";
                for(int i=1;i<=n;i++){
                    if(n%i==0){
                        cout<<i<<" ";
                    }
                }
            }
            else{
                cout<<"\n"<<n<<" is a prime number";
                int prime=n+1;
                while(1){
                    int a=1;
                    for(int i=2;i<prime;i++){
                        if(prime%i==0){
                            a=0;
                        }
                    }
                    if(a==1){
                        cout<<"\n\nThe next prime number greater than "<<n<<" is : "<<prime;
                        break;
                    }
                    else{
                        prime++;
                    }
                }
            }
        }
    }
    return 0;
}