#include <iostream>
#include <limits>
#include <string>
// Add complete path to Header.h file!
#include <EMS\Header.h> 
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
void saveStateToFile(ofstream &file, map<int, Student *> &students)
{
    if (file.is_open())
    {
        for (const auto &pair : students)
        {
            auto studentPtr = pair.second;

            if (studentPtr)
            {
                file << studentPtr->getname() << "," << studentPtr->getid(); // Save name and ID

                vector<Course *> crs = studentPtr->getcs();
                for (const auto &course : crs)
                {
                    if (course)
                    {
                        file << "," << course->code() << "," << course->name() << ","
                             << course->getcredits() << "," << course->getinst(); // Save course info
                    }
                }
                file << endl; // End the entry with a newline
            }
        }
    }
    else
    {
        cout << "FAILED TO OPEN FILE" << endl;
    }
}

void loadStateFromFile(EnrollmentSystem &system)
{
    ifstream file("courses.txt");

    if (!file.is_open())
    {
        cout << "Error opening courses.txt file!" << endl;
        return;
    }

    string line;
    getline(file, line); // Skip the header line (assuming it exists)

    while (getline(file, line))
    {
        // Split the line using commas as delimiters
        vector<string> tokens;
        stringstream ss(line);
        string token;

        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        // Check if we have enough data points (7 for course object)
        if (tokens.size() != 7)
        {
            continue; // Skip to the next line
        }

        // Extract course data
        string code = tokens[0];
        string name = tokens[1];
        int credits;
        stringstream(tokens[2]) >> credits;
        string ins = tokens[3];
        string dept = tokens[4];
        int level;
        stringstream(tokens[5]) >> level;
        int capa;
        stringstream(tokens[6]) >> capa;

        // Create Course object and add it to the system
        Course c(code, name, credits, ins, dept, level, capa);
        system.addcoursetoenrollment(c);
    }

    file.close();
}
void loadstudentStateFromFile(ifstream &file, map<int, Student *> &students, EnrollmentSystem &system)
{
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string token;
            vector<string> tokens;
            while (getline(iss, token, ','))
            {
                tokens.push_back(token);
            }
            string studentName = tokens[0];
            int studentID = stoi(tokens[1]);
            Student *newStudent = new Student();
            newStudent->setid(studentID);
            newStudent->setname(studentName);
            string code = tokens[2];
            Course *c = system.searchbycode(code);
            if (c)
            {
                system.enrollStudentInCourse(*newStudent, *c);
            }
            else
            {
                cout << "Course Not Found!!!" << endl;
            }
            students[studentID] = newStudent;
        }
    }
    else
    {
        cout << "FAILED TO OPEN FILE" << endl;
    }
}

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
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 7: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice)
        {
        case 1:
        {
            string code;
            cout << "Enter Course Code: ";
            getline(cin, code);
            Course *c = system.searchbycode(code);
            if (c)
            {
                system.enrollStudentInCourse(student, *c);
                // student.enrollCourse(*c);
                cout << "Operation Finished for" << code << endl;
            }
            else
            {
                cout << "Course Not Found!!!" << endl;
            }
            break;
        }

        case 2:
        {
            string code;
            cout << "Enter Course Code: ";
            getline(cin, code);
            Course *c = system.searchbycode(code);
            if (c)
            {
                student.dropcourse(*c);
            }
            else
            {
                cout << "Course Not Found!!!" << endl;
            }
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
            getline(cin, instructor);
            system.searchbyinstructor(instructor);
            break;
        }
        case 5:
        {
            // Logic for searching course by level
            int level;
            cout << "Enter level: ";
            while (!(cin >> level))
            {
                cout << "Invalid input. Please enter an integer for level: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            system.seachbylvl(level);
            break;
        }
        case 6:
        {
            // Logic for searching course by department
            string dept;
            cout << "Enter department: ";
            getline(cin, dept);
            system.searchbydept(dept);
            break;
        }
        case 7:
            cout << "Exiting student menu.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 7.\n";
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
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 8: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice)
        {
        case 1:
        {
            cout << "Enter Course details: " << endl;
            string code, name, ins, dept;
            int credits, level, capa;

            cout << "Code: ";
            getline(cin, code);
            cout << "Name: ";
            getline(cin, name);
            cout << "Credits: ";
            while (!(cin >> credits))
            {
                cout << "Invalid input. Please enter an integer for credits: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Instructor: ";
            getline(cin, ins);
            cout << "Level: ";
            while (!(cin >> level))
            {
                cout << "Invalid input. Please enter an integer for level: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Department: ";
            getline(cin, dept);
            cout << "Capacity: ";
            while (!(cin >> capa))
            {
                cout << "Invalid input. Please enter an integer for capacity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

            Course c(code, name, credits, ins, dept, level, capa);
            system.addcoursetoenrollment(c);
            cout << "Course Added!!!" << endl;
            break;
        }
        case 2:
        {
            cout << "Enter Course details: ";
            string code, name, ins;
            int credits;

            cout << "Code: ";
            getline(cin, code);
            cout << "Name: ";
            getline(cin, name);
            cout << "Credits: ";
            while (!(cin >> credits))
            {
                cout << "Invalid input. Please enter an integer for credits: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Instructor: ";
            getline(cin, ins);

            Course c(code, name, credits, ins);
            system.removecoursefromenrollment(c);
            break;
        }
        case 3:
        {
            string instructor;
            cout << "Enter instructor's name: ";
            getline(cin, instructor);
            system.searchbyinstructor(instructor);
            break;
        }
        case 4:
        {
            int level;
            cout << "Enter level: ";
            while (!(cin >> level))
            {
                cout << "Invalid input. Please enter an integer for level: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            system.seachbylvl(level);
            break;
        }
        case 5:
        {
            string dept;
            cout << "Enter department: ";
            getline(cin, dept);
            system.searchbydept(dept);
            break;
        }
        case 6:
        {
            int i;
            cout << "Enter Student ID: ";
            while (!(cin >> i))
            {
                cout << "Invalid input. Please enter an integer for Student ID: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            string n;
            cout << "Enter Student Name: ";
            getline(cin, n);

            Student s(i, n);
            bool a = false;

            if (Enrolledstudents[s.getid()])
            {
                Enrolledstudents.erase(s.getid());
                cout << "Student Expelled!!!" << endl;
                a = true;
                break;
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
            int credits, g;

            cout << "Code: ";
            getline(cin, code);
            cout << "Name: ";
            getline(cin, name);
            cout << "Instructor: ";
            getline(cin, ins);
            cout << "Credits: ";
            while (!(cin >> credits))
            {
                cout << "Invalid input. Please enter an integer for credits: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

            Course c(code, name, credits, ins);
            cout << "Enter New Course Capacity: ";
            while (!(cin >> g))
            {
                cout << "Invalid input. Please enter an integer for the new capacity: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

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
            }
            if (o)
            {
                cout << "Course not found!" << endl;
            }

            break;
        }
        case 8:
            cout << "Exiting admin menu.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8.\n";
        }
    } while (choice != 8);
}

int main()
{
    EnrollmentSystem system;
    Admin admin;
    map<int, Student *> students; // Vector to store multiple students
    int userChoice;
    for (int i = 0; i < 5000; ++i)
    {
        Enrolledstudents[i] = nullptr;
    }
    loadStateFromFile(system);
    ifstream studentsFile("EMS.txt");
    if (!studentsFile.is_open())
    {
        cout << "Error opening EMS.txt!" << endl;
        return 1;
    }
    loadstudentStateFromFile(studentsFile, students, system);
    studentsFile.close();
    ofstream myfile;
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
            cout << "State saved to file successfully.\n";
            break;

        case 2:
        {
            int studentID;
            string studentName;

            cout << "Enter Student ID: ";
            cin >> studentID;
            auto it = students.find(studentID);
            if (it != students.end())
            {
                studentMenu(*(it->second), system);
            }
            else
            {
                cout << "Enter Name: ";
                cin >> studentName;
                Student *student = new Student();
                student->setid(studentID);
                student->setname(studentName);
                studentMenu(*student, system);
                students[studentID] = student;
            }
            break;
        }

        case 3:
            cout << "Exiting the system.\n";
            myfile.open("EMS.txt");
            saveStateToFile(myfile, students);
            myfile.close();
            break;

        default:
            cout << "Invalid choice. Please enter a valid option.\n";
            break;
        }
    } while (userChoice != 3);

    // myfile.close();
    return 0;
}
