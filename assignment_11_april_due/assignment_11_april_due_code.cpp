#include<iostream>
#include<vector>
using namespace std;
class Student{
    string name;
    int rno;
    float cgpa;
    vector<string> courses;
    public:
    Student(){
        name="unknown";
        rno=0;
        cgpa=0.0;
    }
    Student(string n, int r, float c){
        name=n;
        rno=r;
        cgpa=c;
    }
    Student(const Student&other){
        name=other.name;
        rno=other.rno;
        cgpa=other.cgpa;
        courses=other.courses;
    }
    void addCourse(const string &course){
        courses.push_back(course);
    }
    void updateCgpa(float c){
        cgpa=c;
    }
    void display(){
        cout<<"Name  : "<<name<<endl<<"Roll Number : "<<rno<<endl<<"CGPA : "<<cgpa<<endl<<"Enrolled Courses : ";
        for(int i=0;i<courses.size();i++){
            cout<<courses[i]<<" ";
        }
        cout<<endl<<"-----------------------------------------------"<<endl;
    }
    int searchRno(){
        return rno;
    }
};
class StudentManagementSystem{
    vector<Student> allStudents;
    public:
    void addStudent(Student &student){
        allStudents.push_back(student);
    }
    void searchByRoll(int r){
        Student foundStudent;
        int flag=0;
        for(int i=0;i<allStudents.size();i++){
            if(allStudents[i].searchRno()==r){
                foundStudent=allStudents[i];
                flag=1;
            }
        }
        if(flag==1){
            foundStudent.display();
        }
        else{
            cout<<"Roll Number NOT FOUND !"<<endl<<endl;
        }
    }
    void displayAll(){
        for(int i=0;i<allStudents.size();i++){
            allStudents[i].display();
        }
    }
};
int main(){
    StudentManagementSystem records;
    Student s1("Abhijeet",120,8.9);
    Student s2("Abhay",134,7.8);
    Student s3;
    s3.addCourse("English");
    s3.addCourse("French");
    s1.addCourse("DSA");
    s1.addCourse("Computer_Networks");
    s2.addCourse("Engineering_Mathematics");
    s1.updateCgpa(9.0);
    s3.updateCgpa(6.8);
    records.addStudent(s1);
    records.addStudent(s2);
    records.addStudent(s3);
    int roll;
    cout<<"Enter the roll number of student to display the information : ";
    cin>>roll;
    records.searchByRoll(roll);
    cout<<"-----------------------------------------------"<<endl;
    cout<<"INFORMATION OF ALL THE STUDENTS : "<<endl;
    cout<<"-----------------------------------------------"<<endl;
    records.displayAll();
    return 0;
}