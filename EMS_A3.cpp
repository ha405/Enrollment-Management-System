#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
using namespace std;
class Student;

vector<Student *> Enrolledstudents; // Global vector to keep track of current students in record

// forward definitions

class Course; 

class EnrollmentSystem;

class Person
{
public:
    Person()
    {
        name = "";
        personID = 0;
    }
    Person(string name, int id) : name(name), personID(id) {}
    virtual int getid() = 0;
    virtual string getname() = 0;
    virtual ~Person() {}
    virtual void display() = 0;

protected:
    string name;
    int personID;
};

class Admin : public Person
{

protected:
    int adminid;
    int cap;

public:
    Admin()
    {
        adminid = 0;
        cap = 10;
    }
    Admin(int a, int b)
    {
        adminid = a;
        cap = b;
    }

    void setid(int a)
    {
        adminid = a;
    }

    int getid() override
    {
        return adminid;
    }

    string getname() override
    {
        return "";
    }
    int getcap()
    {
        return cap;
    }
    void setcap(int b)
    {
        cap = b;
    }

    void display() override
    {
        return;
    }


    Admin(Admin &other)
    {
        adminid = other.adminid;
    }
    friend class Course;

    // make the course class friend of admin so admin can directly access the course functions
};

class Course
{
private:
    int level;
    string dept;
    string courseCode;
    string courseName;
    int courseCredits;
    int courseCapacity;
    string instructor;
    queue<int> waitlist;

public:
    void qpush(int a)
    {
        waitlist.push(a);
    }

    int qpop()
    {
        int f = waitlist.front();
        waitlist.pop();
        return f;
    }

    bool isempty()
    {
        return waitlist.empty();
    }

    string name()
    {
        return courseName;
    }

    int sizewaitlist()
    {
        return waitlist.size();
    }
    int getcredits()
    {
        return courseCredits;
    }
    int getcapacity()
    {
        return courseCapacity;
    }
    void redcapacity()
    {
        courseCapacity--;
    }
    void inccapacity()
    {
        courseCapacity++;
    }
    void setcapacity(int c)
    {
        courseCapacity = c;
    }
    string code()
    {
        return courseCode;
    }

    void setdept(string d)
    {
        dept = d;
    }

    void setlvl(int l)
    {
        level = l;
    }

    int getlvl()
    {
        return level;
    }

    string getdept()
    {
        return dept;
    }

    Course()
    {
        courseCode = "";
        courseName = "";
        courseCredits = 0;
        courseCapacity = 0;
    }

    Course(string code, string name, int credits, string instruc)
    {
        courseCode = code;
        courseName = name;
        courseCredits = credits;
        instructor = instruc;
    }

    // two constructors for different purposes

    void setinst(string n)
    {
        instructor = n;
    }
    string getinst()
    {
        return instructor;
    }

    Course(const Course &other)
    {
        courseCode = other.courseCode;
        courseCapacity = other.courseCapacity;
        courseName = other.courseName;
        courseCredits = other.courseCredits;
        instructor = other.instructor;
        dept = other.dept;
        level = other.level;
        queue<int> copy = other.waitlist;
        while (!copy.empty())
        {
            this->waitlist.push(copy.front());
            copy.pop();
        }
    }

    friend ostream &operator<<(ostream &os, Course &course)
    {
        os << course.code() << " " << course.name() << " " << course.getcredits() << " " << course.getinst() << " " << course.getdept() << endl;
        return os;
    }
};

class Student : public Person
{
private:
    int studentID;
    string studentName;
    vector<Course *> enrolledCourses;

public:
    Student()
    {
        studentID = 0;
        studentName = "";
    }
    Student(int ID, string Name)
    {
        studentID = ID;
        studentName = Name;
    }

    vector<Course *> getcs() const
    {
        return enrolledCourses;
    }

    int getid() override
    {
        return studentID;
    }
    void setid(int i)
    {
        studentID = i;
    }

    void setname(string n)
    {
        studentName = n;
    }
    virtual string getname() override
    {
        return studentName;
    }
    void displayfee()
    {
        if (!enrolledCourses.empty())
        {
            double totalFee = 0.0;

            cout << setfill('*') << setw(50) << '*' << endl;
            cout << setfill(' ') << setw(24) << left << "Fee Challan" << setw(26) << '*' << endl;
            cout << setfill('*') << setw(50) << '*' << endl;

            for (Course *course : enrolledCourses)
            {
                cout << setfill(' ') << setw(30) << left << course->code();
                cout << setw(10) << right << fixed << setprecision(2) << course->getcredits() << endl;

                totalFee += course->getcredits() * 32100;
            }

            int misc = 100000;
            totalFee += misc;
            cout << setfill('*') << setw(50) << '*' << endl;
            cout << setfill(' ') << setw(30) << left << "Total Fee";
            cout << setw(10) << right << fixed << setprecision(2) << totalFee << endl;
            cout << setfill('*') << setw(50) << '*' << endl;
        }
        else
            cout << "You have no Courses, yet" << endl;
    }

    void enrollCourse(Course &c)
    {
        if (c.getcapacity() > 0)
        {
            c.redcapacity();
            Course *n = new Course(c);
            enrolledCourses.push_back(&c);
            cout << "Enrollment successfull in " << c.code() << endl;
        }
        else if (c.getcapacity() <= 0 && c.sizewaitlist() < 4)
        {
            c.qpush(studentID);
            cout << "Cap Full. You have been added to the waitlist" << endl;
        }
        else
        {
            try
            {
                throw "The is full and waitlist has no free spots";
                ;
            }
            catch (string &str)
            {
                cout << str;
            }
        }
    }

    bool testcourse(Course &c)
    {
        bool q = false;
        for (size_t i = 0; i < enrolledCourses.size(); i++)
        {
            if (c.code() == enrolledCourses[i]->code())
            {
                q = true;
                return true;
                break;
            }
        }
        return q;
    }

    void dropcourse(Course &c)
    {
        bool q = false;
        for (size_t i = 0; i < enrolledCourses.size(); i++)
        {
            if (c.code() == enrolledCourses[i]->code())
            {
                enrolledCourses.erase(enrolledCourses.begin() + i);
                cout << "Course dropped successfully...." << endl;
                c.inccapacity();
                q = true;
                break;
            }
        }
        if (!q)
        {
            cout << "You are not enrolled in this course...." << endl;
        }
    }

    void printcourses()
    {
        for (size_t i = 0; i < enrolledCourses.size(); i++)
        {
            cout << enrolledCourses[i]->code() << " " << enrolledCourses[i]->name() << " " << enrolledCourses[i]->getcredits();
        }
    }

    void display() override
    {
        cout << "Student ID: " << getid() << endl;
        cout << "Student Name: " << getname() << endl;
        printcourses();
    }

    Student(const Student &other)
    {
        studentID = other.studentID;
        studentName = other.studentName;
        for (Course *course : other.enrolledCourses)
        {
            Course *copycourse = new Course(*course);
            this->enrolledCourses.push_back(copycourse);
            delete copycourse;
        }
    }

    ~Student()
    {
    }
};

class EnrollmentSystem
{
private:
    vector<Course> AvailableCourses;

    // this serves as an intermediate service between admin, course management, and students. Only admin can modfiy this. Students can access as per their use but no modfifications allowed!!!

public:
    void enrollStudentInCourse(Student &s, Course &c)
    {
        bool flag = true;
        if (s.testcourse(c))
        {
            for (size_t i = 0; i < Enrolledstudents.size(); i++)
            {
                if (s.getid() == Enrolledstudents[i]->getid())
                {
                    flag = false;
                    break;
                }
            }
        }
        else if (!s.testcourse(c))
        {
            for (size_t i = 0; i < Enrolledstudents.size(); i++)
            {
                if (s.getid() == Enrolledstudents[i]->getid())
                {
                    flag = false;
                    break;
                }
            }
        }
        if (flag)
        {
            Student *g = new Student(s);
            Enrolledstudents.push_back(g);
        }
    }
    void displayEnrollmentStatus()
    {
        for (size_t i = 0; i < Enrolledstudents.size(); i++)
        {
            Enrolledstudents[i]->display();
            cout << endl;
        }
    }
    void addFromWaitlist(Course &c)
    {
        for (int i = c.getcapacity(); !c.isempty() || c.getcapacity() > 0; i++)
        {
            int p = c.qpop();
            for (size_t j = 0; j < Enrolledstudents.size(); j++)
            {
                if (Enrolledstudents[j]->getid() == p)
                {
                    Enrolledstudents[j]->enrollCourse(c);
                }
            }
        }
    }

    vector<Course> availcourses() const
    {
        return AvailableCourses;
    }

    void setavail(vector<Course> a)
    {
        AvailableCourses = a;
    }

    Course searchbycode(string a)
    {
        for (size_t o = 0; o < AvailableCourses.size(); o++)
        {
            if (a == AvailableCourses[o].code())
            {
                return AvailableCourses[o];
            }
        }
    }

    template <typename T>
    void searchbyinstructor(T inst)
    {
        bool a = false;
        for (size_t k = 0; k < AvailableCourses.size(); k++)
        {
            if (inst == AvailableCourses[k].getinst())
            {
                cout << "Code: " << AvailableCourses[k].code() << " Name: " << AvailableCourses[k].name() << " Credits: " << AvailableCourses[k].getcredits() << endl;
                a = true;
            }
        }
        if (!a)
        {
            cout << "No Results!" << endl;
        }
    }
    template <typename T>
    void searchbydept(T depart)
    {
        bool a = false;
        for (size_t k = 0; k < AvailableCourses.size(); k++)
        {
            if (depart == AvailableCourses[k].getdept())
            {
                cout << "Code: " << AvailableCourses[k].code() << " Name: " << AvailableCourses[k].name() << " Credits: " << AvailableCourses[k].getcredits() << endl;
                a = true;
            }
        }
        if (!a)
        {
            cout << "No Results!" << endl;
        }
    }

    void seachbylvl(int l)
    {
        bool a = false;
        for (size_t k = 0; k < AvailableCourses.size(); k++)
        {
            if (l == AvailableCourses[k].getlvl())
            {
                cout << "Code: " << AvailableCourses[k].code() << " Name: " << AvailableCourses[k].name() << " Credits: " << AvailableCourses[k].getcredits() << endl;
                a = true;
            }
        }
        if (!a)
        {
            cout << "No results!" << endl;
        }
    }

    void addcoursetoenrollment(Course &c)
    {
        bool a = false;
        for (size_t i = 0; i < AvailableCourses.size(); i++)
        {
            if (c.code() == AvailableCourses[i].code())
            {
                a = true;
                break;
            }
        }
        if (!a)
        {
            AvailableCourses.push_back(c);
            cout << "Course Added!" << endl;
        }
    }

    void removecoursefromenrollment(Course &c)
    {
        for (size_t i = 0; i < AvailableCourses.size(); i++)
        {
            if (c.code() == AvailableCourses[i].code() && c.getinst() == AvailableCourses[i].getinst())
            {
                AvailableCourses.erase(AvailableCourses.begin() + i);
                break;
            }
        }
        cout << "Course removed!!!" << endl;
    }
};
// File Read/Write
void saveStateToFile(ofstream &file, Admin &a)
{
    if (file.is_open())
    {

        for (int i = 0; i < Enrolledstudents.size(); i++)
        {
            file << Enrolledstudents[i]->getname() << " " << Enrolledstudents[i]->getid();
            vector<Course *> crs = Enrolledstudents[i]->getcs();
            for (int j = 0; j < crs.size(); j++)
            {
                file<<" " << crs[i]->code() << " " << crs[i]->name() <<" " << crs[i]->getcredits()<<" "<<crs[i]->getinst();
            }
            file << endl;
        }
    } else cout<<"FAILED TO OPEN FILE"<<endl;
}
void loadStateFromFile(string &filename, Student &s){};

void studentMenu(Student &student, EnrollmentSystem &system)
{
    int choice = 0;
    do
    {
        choice = 0;
        cout << "Student Menu:\n";
        cout << "1. Enroll in a course\n";
        cout << "2. Drop a course\n";
        cout << "3. Generate Fee Challan\n";
        cout << "4. Search Course by Instructor\n";
        cout << "5. Search Course by Level\n";
        cout << "6. Search Course by Dept\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string code;
            cout << "Enter Course Code: ";
            cin >> code;
            Course c;
            c = system.searchbycode(code);
            // cout << c.code();
            student.enrollCourse(c);
            system.enrollStudentInCourse(student, c);
            break;
        }

        case 2:
        {
            string code;
            cout << "Enter Course Code: ";
            cin >> code;
            // Course c = system.searchbycode(code);
            // student.dropcourse(c);
            break;
        }
        case 3:
            // Logic for generating fee challan
            student.displayfee();
            break;
        case 4:
        {
            // Logic for searching course by instructor
            string instructor;
            cout << "Enter instructor's name: ";
            cin >> instructor;
            system.searchbyinstructor(instructor);
            break;
        }
        case 5:
        {
            // Logic for searching course by level
            int level;
            cout << "Enter level: ";
            cin >> level;
            system.seachbylvl(level);
            break;
        }
        case 6:
        {
            // Logic for searching course by department
            string dept;
            cout << "Enter department: ";
            cin >> dept;
            system.searchbydept(dept);
            break;
        }
        case 7:
            cout << "Exiting student menu.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);
}

void adminMenu(Admin &admin, EnrollmentSystem &system)
{
    int choice;
    do
    {
        cout << "Admin Menu:\n";
        cout << "1. Add Course to enrollment\n";
        cout << "2. Remove Course from enrollment\n";
        cout << "3. Search Course by Instructor\n";
        cout << "4. Search Course by Level\n";
        cout << "5. Search Course by Dept\n";
        cout << "6. Expel Student\n";
        cout << "7. Increase Course Capacity\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Course details: ";
            string code, name, ins;
            int credits;
            cout << endl
                 << "Code: ";
            cin >> code;
            cout << endl
                 << "name: ";
            cin >> name;
            cout << endl
                 << "credits: ";
            cin >> credits;
            cout << endl
                 << "Instructor: ";
            cin >> ins;
            int level;
            cout << "level: ";
            cin >> level;
            string dept;
            cout << "Department: ";
            cin >> dept;
            Course c(code, name, credits, ins);
            c.setlvl(level);
            c.setdept(dept);
            system.addcoursetoenrollment(c);
            break;
        }
        case 2:
        {
            cout << "Enter Course details: ";
            string code, name, ins;
            int credits;
            cout << endl
                 << "Code: ";
            cin >> code;
            cout << endl
                 << "name: ";
            cin >> name;
            cout << endl
                 << "credits: ";
            cin >> credits;
            cout << endl
                 << "Instructor: ";
            cin >> ins;
            Course c(code, name, credits, ins);
            system.removecoursefromenrollment(c);
            break;
        }
        case 3:
        {
            string instructor;
            cout << "Enter instructor's name: ";
            cin >> instructor;
            system.searchbyinstructor(instructor);
            break;
        }
        case 4:
        {
            int level;
            cout << "Enter level: ";
            cin >> level;
            system.seachbylvl(level);
            break;
        }
        case 5:
        {
            string dept;
            cout << "Enter department: ";
            cin >> dept;
            system.searchbydept(dept);
            break;
        }
        case 6:
        {
            int i;
            cout << "Enter Student ID: ";
            cin >> i;
            string n;
            cout << endl
                 << "Enter Student Name: ";
            cin >> n;
            Student s(i, n);
            bool a = false;
            for (size_t i = 0; i < Enrolledstudents.size(); i++)
            {
                if (s.getid() == Enrolledstudents[i]->getid())
                {
                    Enrolledstudents.erase(Enrolledstudents.begin() + i);
                    cout << "Student Expelled!!!" << endl;
                    a = true;
                    break;
                }
            }
            if (!a)
            {
                cout << "Student Not Found!!!" << endl;
            }
            break;
        }
        case 7:
        {
            cout << "Enter Course details: ";
            string code, name, ins;
            int credits;
            cout << endl
                 << "Code: ";
            cin >> code;
            cout << endl
                 << "name: ";
            cin >> name;
            cout << endl
                 << "Instructor: ";
            cin >> ins;
            Course c(code, name, credits, ins);
            cout << "Enter New Course Capacity: ";
            int g;
            cin >> g;
            vector<Course> cs = system.availcourses();
            bool o = true;
            for (size_t i = 0; i < cs.size(); i++)
            {
                if (cs[i].code() == c.code())
                {
                    cs[i].setcapacity(g);
                    system.setavail(cs);
                    o = false;
                    cout << "Cap Increased!!!" << endl;
                }
            } if (o){
                cout<<"Course not found!"<<endl;
            }

            break;
        }
        case 8:
            cout << "Exiting admin menu.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 8);
}
int main()
{
    EnrollmentSystem system;
    Admin admin;
    vector<Student> students; // Vector to store multiple students
    int userChoice;

    ofstream myfile("EMS.txt");
    if (!myfile)
    {
        cout << "Error opening file!";
        return 1;
    }

    do
    {
        cout << "Welcome to the Enrollment System\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            cout << "Enter Admin ID: ";
            int adminID;
            cin >> adminID;
            admin.setid(adminID);
            adminMenu(admin, system);
            // Save state to file if admin chooses to do so
            saveStateToFile(myfile, admin);
            cout << "State saved to file successfully.\n";
            break;

        case 2:
            {
                Student student;
                int studentID;
                string studentName;

                cout << "Enter Student ID: ";
                cin >> studentID;
                cout << "Enter Name: ";
                cin >> studentName;
                student.setid(studentID);
                student.setname(studentName);
                students.push_back(student); 
                studentMenu(students.back(), system); 
                break;
            }

        case 3:
            cout << "Exiting the system.\n";
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (userChoice != 3);

    myfile.close(); // Close the file
    return 0;
}