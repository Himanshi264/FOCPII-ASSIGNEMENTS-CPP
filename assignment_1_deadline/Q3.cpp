#include<iostream>
#include<cctype>
#include<cstring>
using namespace std;
int main(){
    char str1[100];
    cout<<endl<<"Enter the string : ";
    cin.getline(str1,100);
    cout<<endl;
    while(1){
        int ch;
        cout<<"-------------------------------------------------------\n";
        cout<<"Enter 1 to check for pallindrome\n";
        cout<<"Enter 2 to display the frequency of each character\n";
        cout<<"Enter 3 to replace all the vowels with a specific character\n";
        cout<<"Enter 4 to exit\n";
        cout<<"-------------------------------------------------------\n";
        cout<<endl<<"Enter your choice 1/2/3/4 : ";
        cin>>ch;
        int size=strlen(str1);
        char str2[size+1];
        char str3[size+1];
        if(ch==1){
            int j=0;
            for(int i=0;i<size;i++){
                if(isspace(str1[i])==0){
                    str2[j]=str1[i];
                    j++;
                }
            }
            str2[j]='\0';
            for(int i=0;i<strlen(str2);i++){
                if(isalpha(str2[i])){
                    if(str2[i]>=97 && str2[i]<=122){
                        str2[i]=str2[i]-32;
                    }
                }
            }
            int i=0,a=1;
            int k=strlen(str2)-1;
            while(i<k){
                if(str2[i]!=str2[k]){
                    a=0;
                    break;
                }
                i++;
                k--;
            }
            cout<<endl;
            if(a==1){
                cout<<"The given string is a palindrome\n\n";
            }
            else{
                cout<<"The given string is not a pallindrome\n\n";
            }
        }
        else if(ch==2){
            int spaces=0,alpha=0,num=0,sp_ch=0;
            for(int i=0;i<strlen(str1);i++){
                if(isspace(str1[i])){
                    spaces++;

                }
                else if(isalpha(str1[i])){
                    alpha++;
                }
                else if(isdigit(str1[i])){
                    num++;
                }
                else{
                    sp_ch++;
                }
            }
            cout<<endl<<endl;;
            cout<<"Number of spaces = "<<spaces;
            cout<<endl<<"Number of alphabets = "<<alpha;
            cout<<endl<<"Number of digits = "<<num;
            cout<<endl<<"Number of special characters = "<<sp_ch;
            cout<<endl<<endl;
        }
        else if(ch==3){
            char character;
            cout<<"\nEnter the character you want to replace vowels with : ";
            cin>>character;
            for(int i=0;i<strlen(str1);i++){
                char ch = toupper(str1[i]);
                if(ch == 'A' || ch=='E' || ch=='I' || ch=='O' || ch=='U'){
                    str3[i]=character;
                }
                else{
                    str3[i]=str1[i];
                }
            }
            cout<<endl<<"String after replacing with the character "<<character<<" : "<<str3<<endl<<endl;
        }
        else if(ch==4){
            cout<<"\nThanks for your visit";
            break;
        }
        else{
            cout<<endl<<"Invalid choice entered"<<endl<<endl;
        }
    }
    return 0;
}