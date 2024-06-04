#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
#include <D:\LUMS\Fall 23-24\CS 200\Assignments\Student Management System\Header.h>
using namespace std;


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