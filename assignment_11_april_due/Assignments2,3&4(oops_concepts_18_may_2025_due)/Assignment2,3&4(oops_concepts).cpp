#include<iostream>
#include<string>
#include<map>
#include<algorithm>
#include<vector>
#include<exception>
#include<ctime>
#include<set>
#include<fstream>>
using namespace std;

class ValidationException : public std::exception {
    string message;
public:
    ValidationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Person {
protected:
    string name;
    int age;
    string ID;
    string contact;

public:
    Person(string n, int a, const string& id, const string& c) {
        setName(n);
        setAge(a);
        setID(id);
        setContact(c);
    }

    void setName(const string& n) {
        if (n.empty()) throw invalid_argument("Name cannot be empty");
        name = n;
    }

    void setAge(int a) {
        if (a <= 0 || a > 120) throw invalid_argument("Invalid age");
        age = a;
    }

    void setID(const string& id) {
        if (id.empty() || id.length() < 3)
            throw invalid_argument("Invalid ID: must be at least 3 characters.");
        ID = id;
    }

    void setContact(const string& c) {
        if (c.length() != 10 || c.find_first_not_of("0123456789") != string::npos)
            throw invalid_argument("Invalid contact: must be exactly 10 digits.");
        contact = c;
    }

    string getName() const { return name; }
    string getID() const { return ID; }
    string getContact() const { return contact; }

    virtual void displayDetails() const {
        cout << "Name: " << name
             << "\nAge: " << age
             << "\nID: " << ID
             << "\nContact: " << contact << endl;
    }

    virtual double calculatePayment() const = 0;

    virtual ~Person() {}
};

class Professor : public Person {
private:
    string department, specialization, hireDate;

public:
    Professor(string n, int a, string id, string c, string d, string s, string hd)
        : Person(n, a, id, c) {
        setDepartment(d);
        setSpecialization(s);
        setHireDate(hd);
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Department: " << department
             << "\nSpecialization: " << specialization
             << "\nHire Date: " << hireDate << endl;
    }

    string getDepartment() const {
        return department;
    }

    string getID() const {
        return ID;
    }

    void setDepartment(const string& d) {
        if (d.empty()) throw invalid_argument("Department cannot be empty.");
        department = d;
    }

    void setSpecialization(const string& s) {
        if (s.empty()) throw invalid_argument("Specialization cannot be empty.");
        specialization = s;
    }

    void setHireDate(const string& hd) {
        if (hd.empty()) throw invalid_argument("Hire date cannot be empty.");
        hireDate = hd;
    }

    double calculatePayment() const override {
        double baseSalary = 10000.00;
        if (baseSalary < 0)
            throw runtime_error("Payment calculation error: salary cannot be negative.");
        return baseSalary;
    }

    ~Professor() {}
};

class Classroom {
private:
    string roomNumber;
    int capacity;
    string location;
public:
    Classroom(string rn, int cap, string loc) : roomNumber(rn), capacity(cap), location(loc) {}

    string getRoomNumber() const { return roomNumber; }
    int getCapacity() const { return capacity; }
    string getLocation() const { return location; }

    void displayClassroom() const {
        cout << "Room: " << roomNumber << " | Capacity: " << capacity << " | Location: " << location << endl;
    }
};

class Course {
private:
    string code, title, description;
    int credits;
    Professor* instructor;
    Classroom* classroom;  
public:
    Course(string c, string t, int cd, string d, Professor* ins, Classroom* cr)
        : code(c), title(t), description(d), instructor(ins), classroom(cr) {
        setCredits(cd);
    }

    void setCredits(int cd) {
        if (cd <= 0) throw invalid_argument("Credits must be positive");
        credits = cd;
    }

    string getTitle() const { return title; }
    string getCode() const { return code; }
    Classroom* getClassroom() const { return classroom; }

    void displayCourse() const {
        cout << "Code: " << code << "\nTitle: " << title << "\nCredits: " << credits
             << "\nDescription: " << description
             << "\nInstructor: " << instructor->getName();
        if (classroom)
            cout << "\nClassroom: " << classroom->getRoomNumber();
        cout << "\n-------------------------------------------\n";
    }
};

class Student : public Person {
private:
    string enrollmentDate, program;
    double GPA;
    vector<Course*> courses;
public:
    Student(string n, int a, string id, string c, string ed, string p, double gpa)
        : Person(n, a, id, c), enrollmentDate(ed), program(p) {
        setGpa(gpa);
    }

    void setGpa(double gpa) {
        if (gpa < 0.0 || gpa > 4.0) throw invalid_argument("GPA must be between 0.0 and 4.0");
        GPA = gpa;
    }

    void enroll(Course* c) {
        for (const auto& course : courses) {
            if (course == c) {
                throw runtime_error("Student is already enrolled in this course.");
            }
        }
        courses.push_back(c);
    }

    void displayDetails() const override {
        Person::displayDetails();
        cout << "Enrollment Date: " << enrollmentDate << "\nProgram: " << program << "\nGPA: " << GPA << "\nCourses: ";
        for (const auto& course : courses) cout << course->getTitle() << ", ";
        cout << endl;
    }

    double calculatePayment() const override {
        return 0.0; 
    }

    ~Student() {}
};

class Department {
private:
    string name, location;
    double budget;
    vector<Professor*> professors;
    vector<Course*> courses;
public:
    Department(string n, string l, double b) : name(n), location(l), budget(b) {}
    void addProfessor(Professor* p) { professors.push_back(p); }

    void addCourse(Course* c) { courses.push_back(c); }

    vector<Professor*> getProfessors() const { return professors; }

    vector<Course*> getCourses() const { return courses; }

    string getName() const { return name; }
    void displayDepartment() const {
        cout << "Name: " << name
             << "\nLocation: " << location
             << "\nBudget: " << budget
             << "\nProfessors: ";
        for (const auto& prof : professors)
            cout << prof->getName() << ", ";
        cout << "\nCourses: ";
        for (const auto& course : courses)
            cout << course->getTitle() << " (" << course->getCode() << "), ";
        cout << "\n-------------------------------------------" << endl;
    }
    ~Department() {}
};

class Logger {
public:
    static void logError(const string& message) {
        ofstream out("error_log.txt", ios::app);
        time_t now = time(0);
        out << ctime(&now) << ": " << message << endl;
    }
};

class UniversitySystemException : public exception {
protected:
    string message;
public:
    explicit UniversitySystemException(const string& msg) : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class CourseFullException : public UniversitySystemException {
public:
    CourseFullException() : UniversitySystemException("Cannot enroll: The course is full.") {}
};

class PrerequisiteNotMetException : public UniversitySystemException {
public:
    PrerequisiteNotMetException() : UniversitySystemException("Cannot enroll: Prerequisites not met.") {}
};

class EnrollmentDeadlineException : public UniversitySystemException {
public:
    EnrollmentDeadlineException() : UniversitySystemException("Cannot enroll: Enrollment deadline has passed.") {}
};

class InvalidGradeException : public UniversitySystemException {
public:
    InvalidGradeException() : UniversitySystemException("Invalid grade: must be between 0 and 100.") {}
};

class UnauthorizedGradeChangeException : public UniversitySystemException {
public:
    UnauthorizedGradeChangeException() : UniversitySystemException("Cannot change grade: already finalized.") {}
};

class IncompleteRequirementsException : public UniversitySystemException {
public:
    IncompleteRequirementsException() : UniversitySystemException("Cannot finalize grade: requirements not completed.") {}
};

class GradeBook {
private:
    map<string, double> grades;
    map<string, bool> finalized;  
    map<string, set<string> > completedTasks;
    map<string, set<string> > requiredTasks;

public:
    void setRequiredTasks(const set<string>& tasks) {
        for (auto& [id, _] : grades) {
            requiredTasks[id] = tasks;
        }
    }

    void completeTask(const string& studentId, const string& task) {
        completedTasks[studentId].insert(task);
    }

    void addGrade(const string& studentId, double g) {
        try {
            if (g < 0.0 || g > 100.0)
                throw InvalidGradeException();

            if (finalized[studentId])
                throw UnauthorizedGradeChangeException();

            grades[studentId] = g;
        } catch (const UniversitySystemException& e) {
            Logger::logError("Grade error for student " + studentId + ": " + e.what());
            cerr << "Error: " << e.what() << endl;
        }
    }

    void finalizeGrade(const string& studentId) {
        try {
            const set<string>& required = requiredTasks[studentId];
            const set<string>& done = completedTasks[studentId];
            for (const string& task : required) {
                if (done.find(task) == done.end()) {
                    throw IncompleteRequirementsException();
                }
            }
            finalized[studentId] = true;
        } catch (const UniversitySystemException& e) {
            Logger::logError("Finalize error for student " + studentId + ": " + e.what());
            cerr << "Error: " << e.what() << endl;
        }
    }

    double calculateAverageGrade() {
        double total = 0.0;
        for (const auto& [id, grade] : grades) total += grade;
        return grades.empty() ? 0.0 : total / grades.size();
    }

    double getHighestGrade() {
        double maxGrade = 0.0;
        for (const auto& [id, grade] : grades) maxGrade = max(maxGrade, grade);
        return maxGrade;
    }

    vector<string> getFailingStudents() {
        vector<string> failing;
        for (const auto& [id, grade] : grades) {
            if (grade < 50.0) failing.push_back(id);
        }
        return failing;
    }
};

class EnrollmentManager {
private:
    map<string, vector<string>> courseEnrollments;
    map<string, int> courseCapacity;
    map<string, vector<string>> coursePrerequisites;
    map<string, time_t> enrollmentDeadlines;

public:
    void setCourseCapacity(const string& courseCode, int capacity) {
        courseCapacity[courseCode] = capacity;
    }

    void setPrerequisites(const string& courseCode, const vector<string>& prerequisites) {
        coursePrerequisites[courseCode] = prerequisites;
    }

    void setEnrollmentDeadline(const string& courseCode, const time_t& deadline) {
        enrollmentDeadlines[courseCode] = deadline;
    }

    void enrollStudent(const string& courseCode, const string& studentID) {
        try {
            if (courseCapacity.count(courseCode) &&
                courseEnrollments[courseCode].size() >= courseCapacity[courseCode]) {
                throw CourseFullException();
            }

            if (coursePrerequisites.count(courseCode) && !coursePrerequisites[courseCode].empty()) {
                throw PrerequisiteNotMetException();
            }

            time_t now = time(0);
            if (enrollmentDeadlines.count(courseCode) && now > enrollmentDeadlines[courseCode]) {
                throw EnrollmentDeadlineException();
            }
            courseEnrollments[courseCode].push_back(studentID);
            cout << "\nStudent with ID: " << studentID << " enrolled in course " << courseCode << endl;

        } catch (const UniversitySystemException& e) {
            Logger::logError("Enrollment error for student " + studentID + " in course " + courseCode + ": " + e.what());
            cerr << "Error: " << e.what() << endl;
        }
    }

    void dropStudent(const string& courseCode, const string& studentID) {
        auto& list = courseEnrollments[courseCode];
        list.erase(remove(list.begin(), list.end(), studentID), list.end());
        cout << "\nStudent with ID: " << studentID << " dropped from course " << courseCode << endl;
    }

    int getEnrollmentCount(const string& courseCode) {
        return courseEnrollments[courseCode].size();
    }

    void displayAllEnrollments(const vector<Course*>& courses) const {
        int totalEnrollments = 0;
        cout << "\nCourse Enrollments:\n";
        for (const auto& course : courses) {
            string code = course->getCode();
            auto it = courseEnrollments.find(code);
            if (it != courseEnrollments.end()) {
                const vector<string>& studentList = it->second;
                cout << "Course Code: " << code << " | Title: " << course->getTitle() << " | Enrolled Students: ";
                for (const string& studentID : studentList) {
                    cout << studentID << " ";
                }
                cout << " (" << studentList.size() << " students)\n";
                totalEnrollments += studentList.size();
            } else {
                cout << "Course Code: " << code << " | Title: " << course->getTitle() << " | No Enrollments\n";
            }
        }
        cout << "-------------------------------------------\n";
        cout << "Total Enrollments Across All Courses: " << totalEnrollments << "\n";
    }
};

class UndergraduateStudent : public Student {
private:
    string major;
    string minor;
    string expectedGraduationDate;
public:
    UndergraduateStudent(string n, int a, string id, string c, string ed, string p, double gpa, string maj, string min, string date)
        : Student(n, a, id, c, ed, p, gpa), major(maj), minor(min), expectedGraduationDate(date) {
        if (maj.empty()) throw invalid_argument("Major cannot be empty.");
        if (min.empty()) throw invalid_argument("Minor cannot be empty.");
        if (date.empty()) throw invalid_argument("Expected Graduation Date cannot be empty.");
    }

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Major: " << major << endl
             << "Minor: " << minor << endl
             << "Expected Graduation Date: " << expectedGraduationDate << endl;
    }
};

class GraduateStudent : public Student {
private:
    string topic;
    string thesisTitle;
    Professor* advisor;
    bool hasTeachingAssistantship;
    bool hasResearchAssistantship;
public:
    GraduateStudent(string n, int a, string id, string c, string ed, string p, double gpa, string top, string title, Professor* adv, bool ta = false, bool ra = false)
        : Student(n, a, id, c, ed, p, gpa), topic(top), thesisTitle(title), advisor(adv), hasTeachingAssistantship(ta), hasResearchAssistantship(ra) {
        if (top.empty()) throw invalid_argument("Topic cannot be empty.");
        if (title.empty()) throw invalid_argument("Thesis Title cannot be empty.");
        if (adv == nullptr) throw invalid_argument("Advisor cannot be null.");
    }

    void setTeachingAssistantship(bool status) {
        hasTeachingAssistantship = status;
    }

    void setResearchAssistantship(bool status) {
        hasResearchAssistantship = status;
    }

    bool isTeachingAssistant() const {
        return hasTeachingAssistantship;
    }

    bool isResearchAssistant() const {
        return hasResearchAssistantship;
    }

    void displayDetails() const override {
        Student::displayDetails();
        cout << "Topic: " << topic << endl
             << "Thesis Title: " << thesisTitle << endl
             << "Advisor: " << advisor->getName() << endl
             << "Teaching Assistantship: " << (hasTeachingAssistantship ? "Yes" : "No") << endl
             << "Research Assistantship: " << (hasResearchAssistantship ? "Yes" : "No") << endl;
    }
};

class AssistantProfessor : public Professor {
private:
    int researchGrants;
    int yearsOfService;

public:
    AssistantProfessor(string n, int a, string id, string c, string d, string s, string hd,
                       int rg, int years)
        : Professor(n, a, id, c, d, s, hd) {
        setResearchGrants(rg);
        setYearsOfService(years);
    }

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Years of Service: " << yearsOfService
             << "\nResearch Grants: " << researchGrants << endl;
    }

    void setResearchGrants(int rg) {
        if (rg < 0)
            throw invalid_argument("Research grants cannot be negative.");
        researchGrants = rg;
    }

    void setYearsOfService(int y) {
        if (y < 0)
            throw invalid_argument("Years of service cannot be negative.");
        yearsOfService = y;
    }

    double calculatePayment() const override {
        double baseSalary = 10000.00;
        double serviceBonus = yearsOfService * 1000;
        double grantBonus = researchGrants * 0.1;

        double total = baseSalary + serviceBonus + grantBonus;
        if (total < 0)
            throw runtime_error("Payment calculation error: total salary cannot be negative.");

        return total;
    }
};

class AssociateProfessor : public Professor {
private:
    int paperPublished;
    int yearsOfService;
    int researchGrants;

public:
    AssociateProfessor(string n, int a, string id, string c, string d, string s, string hd,
                       int paper, int rg, int years)
        : Professor(n, a, id, c, d, s, hd) {
        setPapersPublished(paper);
        setResearchGrants(rg);
        setYearsOfService(years);
    }

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Papers Published: " << paperPublished
             << "\nResearch Grants: " << researchGrants
             << "\nYears of Service: " << yearsOfService << endl;
    }

    void setPapersPublished(int papers) {
        if (papers < 0)
            throw invalid_argument("Number of papers published cannot be negative.");
        paperPublished = papers;
    }

    void setResearchGrants(int rg) {
        if (rg < 0)
            throw invalid_argument("Research grants cannot be negative.");
        researchGrants = rg;
    }

    void setYearsOfService(int y) {
        if (y < 0)
            throw invalid_argument("Years of service cannot be negative.");
        yearsOfService = y;
    }

    double calculatePayment() const override {
        double baseSalary = 10000;
        double grantBonus = researchGrants * 0.1;
        double serviceBonus = yearsOfService * 1000;
        double paperBonus = paperPublished * 2500;

        double total = baseSalary + grantBonus + serviceBonus + paperBonus;
        if (total < 0)
            throw runtime_error("Payment calculation error: total salary cannot be negative.");

        return total;
    }
};

class FullProfessor : public Professor {
private:
    int yearsOfService;
    int citations;
    bool tenured;

public:
    FullProfessor(string n, int a, string id, string c, string d, string s, string hd,
                  int cit, bool ten, int years)
        : Professor(n, a, id, c, d, s, hd) {
        setCitations(cit);
        setYearsOfService(years);
        tenured = ten;
    }

    void displayDetails() const override {
        Professor::displayDetails();
        cout << "Number of Citations: " << citations
             << "\nTenured: " << (tenured ? "Yes" : "No")
             << "\nYears of Service: " << yearsOfService << endl;
    }

    void setCitations(int cit) {
        if (cit < 0)
            throw invalid_argument("Citations cannot be negative.");
        citations = cit;
    }

    void setYearsOfService(int y) {
        if (y < 0)
            throw invalid_argument("Years of service cannot be negative.");
        yearsOfService = y;
    }

    double calculatePayment() const override {
        double baseSalary = 10000;
        double serviceBonus = yearsOfService * 1000;
        double citationBonus = citations * 2500;
        double tenureBonus = tenured ? 1000 : 0;

        double total = baseSalary + serviceBonus + citationBonus + tenureBonus;
        if (total < 0)
            throw runtime_error("Payment calculation error: total salary cannot be negative.");

        return total;
    }
};

class University {
private:
    string name;
    vector<Department*> departments; 
public:
    University(string n) : name(n) {}

    void addDepartment(Department* dept) {
        departments.push_back(dept);
    }

    void displayUniversity() const {
        cout << "\n--- " << name << " Departments ---\n";
        for (const auto& dept : departments)
            dept->displayDepartment();
    }

    vector<Professor*> getAllProfessors() const {
        vector<Professor*> all;
        for (const auto& dept : departments) {
            vector<Professor*> profs = dept->getProfessors();
            all.insert(all.end(), profs.begin(), profs.end());
        }
        return all;
    }

    vector<Course*> getAllCourses() const {
        vector<Course*> all;
        for (const auto& dept : departments) {
            vector<Course*> courses = dept->getCourses();
            all.insert(all.end(), courses.begin(), courses.end());
        }
        return all;
    }

    ~University() {
        for (auto d : departments)
            delete d;
    }
};

class Schedule {
private:
    struct TimeSlot {
        string day;
        string time;
        Classroom* classroom;
    };

    map<string, TimeSlot> courseSchedule; 

public:
    void assignTimeSlot(Course* course, const string& day, const string& time, Classroom* classroom) {
        TimeSlot slot;
        slot.day = day;
        slot.time = time;
        slot.classroom = classroom;
        courseSchedule[course->getCode()] = slot;

        cout << "Assigned " << course->getCode() << " to " << classroom->getRoomNumber()
             << " on " << day << " at " << time << endl;
    }

    void displaySchedule() const {
        cout << "\nCourse Schedule:\n";
        for (const auto& entry : courseSchedule) {
            cout << "Course: " << entry.first
                 << " | Day: " << entry.second.day
                 << " | Time: " << entry.second.time
                 << " | Room: " << entry.second.classroom->getRoomNumber() << "\n";
        }
        cout << "-------------------------------------------\n";
    }
};

void displayMenu() {
    cout << "\n---- University Management System ----\n";
    cout << "1. Add Student\n";
    cout << "2. Add Professor\n";
    cout << "3. Add Course\n";
    cout << "4. Add Department\n";
    cout << "5. Manage Course Schedule\n";
    cout << "6. Enroll Student in Course\n";
    cout << "7. Add Grade for Student\n";
    cout << "8. View All Students\n";
    cout << "9. View All Professors\n";
    cout << "10. View All Courses\n";
    cout << "11. View All Enrollments\n";
    cout << "12. Calculate Average Grade\n";
    cout << "13. Calculate Highest Grade\n";
    cout << "14. Display University Details\n";
    cout << "15. View All Classrooms\n";
    cout << "16. Drop Student from Course\n";
    cout << "17. View Failing Students\n";
    cout << "18. Exit\n";
}

int main() {
    vector<Student*> students;
    vector<Professor*> professors;
    vector<Course*> courses;
    vector<Classroom*> classrooms;
    EnrollmentManager em;
    GradeBook gradebook;
    University university("Tech University");
    Schedule schedule;

    int choice;
    string name,roomNumber, id, contact, program, courseCode,deptName, courseTitle,day,time,location;
    int age, credits;
    double gpa, grade;
    Professor* instructor;
    Course* course;
    Department* findDepartmentByName(University& university, const string& deptName);

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

                switch (choice) {
            case 1: {
                cout << "\nEnter Student Details:\n";
                string name, id, contact, program, enrollmentDate;
                int age;
                double gpa;
                cout << "Name: ";
                cin >> name;
                cout << "Age: ";
                cin >> age;
                cout << "ID: ";
                cin >> id;
                cout << "Contact: ";
                cin >> contact;
                cout << "Program: ";
                cin >> program;
                cout << "Enrollment Date: ";
                cin >> enrollmentDate;
                cout << "GPA: ";
                cin >> gpa;
                
                cout << "Student Type (1 - Undergraduate, 2 - Graduate): ";
                int type;
                cin >> type;

                if (type == 1) {
                    string major, minor, graduationDate;
                    cout << "Major: ";
                    cin >> major;
                    cout << "Minor: ";
                    cin >> minor;
                    cout << "Expected Graduation Date: ";
                    cin >> graduationDate;
                    students.push_back(new UndergraduateStudent(name, age, id, contact, enrollmentDate, program, gpa, major, minor, graduationDate));
                } else if (type == 2) {
                    string topic, thesisTitle;
                    Professor* advisor = nullptr;
                    bool hasTA, hasRA;
                    cout << "Research Topic: ";
                    cin >> topic;
                    cout << "Thesis Title: ";
                    cin >> thesisTitle;
                    cout << "Has Teaching Assistantship (1 for Yes, 0 for No): ";
                    cin >> hasTA;
                    cout << "Has Research Assistantship (1 for Yes, 0 for No): ";
                    cin >> hasRA;
                    students.push_back(new GraduateStudent(name, age, id, contact, enrollmentDate, program, gpa, topic, thesisTitle, advisor, hasTA, hasRA));
                }
                break;
            }
            
            case 2: {
                cout << "\nEnter Professor Details:\n";
                string name, id, contact, department, specialization, hireDate;
                int age, type;
                cout << "Name: ";
                cin >> name;
                cout << "Age: ";
                cin >> age;
                cout << "ID: ";
                cin >> id;
                cout << "Contact: ";
                cin >> contact;
                cout << "Department: ";
                cin >> department;
                cout << "Specialization: ";
                cin >> specialization;
                cout << "Hire Date: ";
                cin >> hireDate;
                
                cout << "Professor Type (1 - Assistant, 2 - Associate, 3 - Full): ";
                cin >> type;

                Professor* prof = nullptr;

                if (type == 1) {
                    int researchGrants, yearsOfService;
                    cout << "Research Grants: ";
                    cin >> researchGrants;
                    cout << "Years of Service: ";
                    cin >> yearsOfService;
                    prof = new AssistantProfessor(name, age, id, contact, department, specialization, hireDate, researchGrants, yearsOfService);
                } else if (type == 2) {
                    int papersPublished, researchGrants, yearsOfService;
                    cout << "Papers Published: ";
                    cin >> papersPublished;
                    cout << "Research Grants: ";
                    cin >> researchGrants;
                    cout << "Years of Service: ";
                    cin >> yearsOfService;
                    prof = new AssociateProfessor(name, age, id, contact, department, specialization, hireDate, papersPublished, researchGrants, yearsOfService);
                } else if (type == 3) {
                    int citations, yearsOfService;
                    bool tenured;
                    cout << "Citations: ";
                    cin >> citations;
                    cout << "Years of Service: ";
                    cin >> yearsOfService;
                    cout << "Tenured (1 for Yes, 0 for No): ";
                    cin >> tenured;
                    prof = new FullProfessor(name, age, id, contact, department, specialization, hireDate, citations, tenured, yearsOfService);
                }

                if (prof) {
                    professors.push_back(prof);
                    cout << "\nProfessor added successfully.\n";
                    cout << "Details:\n";
                    prof->displayDetails();
                    cout << "Calculated Payment: ₹" << prof->calculatePayment() << "\n";
                } else {
                    cout << "Invalid professor type selected.\n";
                }

                break;
            }

            case 3: {
                    cout << "\nEnter Course Details:\n";
                    cout << "Course Code: ";
                    cin >> courseCode;
                    cout << "Title: ";
                    cin >> name;
                    cout << "Credits: ";
                    cin >> credits;
                    cout << "Instructor ID: ";
                    cin >> id;

                    instructor = nullptr;
                    for (Professor* p : professors) {
                        if (p->getID() == id) {
                            instructor = p;
                            break;
                        }
                    }

                    if (!instructor) {
                        cout << "Instructor not found. Course not created.\n";
                        break;
                    }

                    cout << "Enter Classroom Room Number: ";
                    cin >> roomNumber;
                    cout << "Enter Classroom Capacity: ";
                    cin >> age; 
                    cout << "Enter location: ";
                    cin >> location;
                    Classroom* room = new Classroom(roomNumber, age,location);
                    classrooms.push_back(room); 

                   
                    Course* newCourse = new Course(courseCode, name, credits, "Course Description", instructor, room);
                    courses.push_back(newCourse);
                    cout << "Course added successfully.\n";
                    break;
                }
            
            case 4: {
                cout << "Enter Department Details:\n";
                string deptName, location;
                double budget;
                cout << "Name: ";
                cin >> deptName;
                cout << "Location: ";
                cin >> location;
                cout << "Budget: ";
                cin >> budget;

                Department* newDept = new Department(deptName, location, budget);

                char addProf;
                cout << "Do you want to add professors to this department? (y/n): ";
                cin >> addProf;
                if (addProf == 'y' || addProf == 'Y') {
                    string profID;
                    while (true) {
                        cout << "Enter Professor ID to add (or type 'done' to finish): ";
                        cin >> profID;
                        if (profID == "done") break;

                        bool found = false;
                        for (Professor* p : professors) {
                            if (p->getID() == profID) {
                                newDept->addProfessor(p);
                                found = true;
                                cout << "Professor added.\n";
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Professor not found.\n";
                        }
                    }
                }

                char addCourse;
                cout << "Do you want to add courses to this department? (y/n): ";
                cin >> addCourse;
                if (addCourse == 'y' || addCourse == 'Y') {
                    string courseCode;
                    while (true) {
                        cout << "Enter Course Code to add (or type 'done' to finish): ";
                        cin >> courseCode;
                        if (courseCode == "done") break;

                        bool found = false;
                        for (Course* c : courses) {
                            if (c->getCode() == courseCode) {
                                newDept->addCourse(c);
                                found = true;
                                cout << "Course added.\n";
                                break;
                            }
                        }
                        if (!found) {
                            cout << "Course not found.\n";
                        }
                    }
                }

                university.addDepartment(newDept);
                cout << "Department added successfully.\n";
                break;
            }

            case 5: {
                cout << "\n--- Schedule a Course ---\n";
                cout << "Enter Course Code: ";
                cin >> courseCode;

                Course* selectedCourse = nullptr;
                for (Course* c : courses) {
                    if (c->getCode() == courseCode) {
                        selectedCourse = c;
                        break;
                    }
                }

                if (!selectedCourse) {
                    cout << "Course not found.\n";
                    break;
                }

                cout << "Enter Day (e.g., Monday): ";
                cin >> day;
                cout << "Enter Time (e.g., 10:00AM-11:00AM): ";
                cin >> time;

                cout << "Enter Classroom Room Number: ";
                cin >> roomNumber;

                Classroom* assignedRoom = nullptr;
                for (Classroom* room : classrooms) {
                    if (room->getRoomNumber() == roomNumber) {
                        assignedRoom = room;
                        break;
                    }
                }

                if (!assignedRoom) {
                    cout << "Classroom not found.\n";
                    break;
                }

                schedule.assignTimeSlot(selectedCourse, day, time, assignedRoom);
                cout << "Schedule assigned successfully.\n";

                char show;
                cout << "Do you want to view the full schedule? (y/n): ";
                cin >> show;
                if (show == 'y' || show == 'Y') {
                    schedule.displaySchedule();
                }
                break;
            }
            
            case 6: 
                cout << "Enter Student ID and Course Code to Enroll: ";
                cin >> id >> courseCode;
                em.enrollStudent(courseCode, id);
                break;

            case 7:
                cout << "Enter Student ID and Grade: ";
                cin >> id >> grade;
                gradebook.addGrade(id, grade);
                break;

            case 8: 
                for (auto& student : students) student->displayDetails();
                break;

            case 9: 
                for (auto& professor : professors) {
                    professor->displayDetails();
                    cout<<endl;
                }
                break;

            case 10: 
                for (auto& course : courses) course->displayCourse();
                break;

            case 11:
                em.displayAllEnrollments(courses);
                break;

            case 12: 
                cout << "Average Grade: " << gradebook.calculateAverageGrade() << endl;
                break;

            case 13: 
                cout << "Highest Grade: " << gradebook.getHighestGrade() << endl;
                break;
            
            case 14: 
                university.displayUniversity();
                break;
            
            case 15: {
                cout << "\n--- All Classrooms ---\n";
                for (auto& room : classrooms) {
                    room->displayClassroom();
                }
                break;
            }

            case 16: {
                cout << "Enter Student ID and Course Code to Drop: ";
                cin >> id >> courseCode;
                em.dropStudent(courseCode, id);
                break;
            }

            case 17: {
                cout << "\nFailing Students (Grade < 50):\n";
                vector<string> failing = gradebook.getFailingStudents();
                if (failing.empty()) {
                    cout << "No failing students.\n";
                } else {
                    for (const auto& sid : failing) {
                        cout << "Student ID: " << sid << endl;
                    }
                }
                break;
            }
            
            case 18: 
                cout << "Exiting Program\n";
                return 0;


            default:
                cout << "Invalid choice, please try again.\n";
      }
    }
    return 0;
}