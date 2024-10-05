#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
#include <map>
using namespace std;
class Student;

map<int, Student *> Enrolledstudents;

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

    Course(string code, string name, int credits, string instruc, string dep, int lvl, int capa)
    {
        courseCode = code;
        courseName = name;
        courseCredits = credits;
        instructor = instruc;
        level = lvl;
        dept = dep;
        courseCapacity = capa;
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
            // cout << "Enrollment successfull in " << c.code() << endl;
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
                throw "The Capacity is full and waitlist has no free spots";
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
        if (Enrolledstudents[s.getid()] && Enrolledstudents[s.getid()]->testcourse(c))
        {
            flag = false;
        }
        if (flag)
        {

            // s.enrollCourse(c);
            Student *new_student = new Student(s);
            // new_student->printcourses();
            new_student->enrollCourse(c);
            s.enrollCourse(c);
            Enrolledstudents[s.getid()] = new_student;
        }
    }

    void addFromWaitlist(Course &c)
    {
        for (int i = c.getcapacity(); !c.isempty() || c.getcapacity() > 0; i++)
        {
            int p = c.qpop();
            if (Enrolledstudents[p])
                Enrolledstudents[p]->enrollCourse(c);
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

    Course *searchbycode(string a)
    {
        for (size_t o = 0; o < AvailableCourses.size(); o++)
        {
            if (a == AvailableCourses[o].code())
            {
                return &AvailableCourses[o];
            }
        }
        return nullptr;
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
            if (l >= AvailableCourses[k].getlvl() && AvailableCourses[k].getlvl() < l + 100)
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