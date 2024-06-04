Student Management System
Introduction
This Student Management System is implemented in C++. It provides functionality for both administrators and students to manage courses, enrollments, and more.

Features:
Administrators:
Add courses to enrollment
Remove courses from enrollment
Search courses by instructor, level, or department
Expel students from the system
Increase course capacity


Students:
Enroll in a course
Drop a course
Generate fee challan
Search courses by instructor, level, or department

HEADER FILE:
Person.h
This header file defines the Person class, which serves as the base class for individuals within the system, including administrators and students. Here's an overview:

Class Definition:
Person: This class represents a person in the system.
Attributes:
name: A string representing the person's name.
personID: An integer representing the unique identifier of the person.
Member Functions:
getid(): A pure virtual function returning the person's ID.
getname(): A pure virtual function returning the person's name.
display(): A pure virtual function to display person details.
Constructor(s) and Destructor: Constructors to initialize the person's attributes and a virtual destructor.
Admin.h
This header file defines the Admin class, representing administrators in the system. Here are the details:

Class Definition:
Admin: Represents an administrator in the system, inheriting from the Person class.
Attributes:
adminid: An integer representing the administrator's ID.
cap: An integer representing the administrator's capacity (perhaps for managing courses or students).
Member Functions:
Constructors: To initialize the administrator's attributes.
setid(), getid(), setcap(), getcap(), display(): Methods to set/get the administrator's ID and capacity, and display details.
Admin(Admin &other): A copy constructor for copying administrator objects.
Course.h
This header file defines the Course class, representing courses offered in the system. Here are the details:

Class Definition:
Course: Represents a course in the system.
Attributes:
Various attributes such as courseCode, courseName, courseCredits, courseCapacity, instructor, dept, level, and a waitlist (queue for students on the waitlist).
Member Functions:
Constructors: To initialize course attributes.
Methods for setting/getting course attributes and managing the waitlist.
Overloaded stream insertion operator (<<) for displaying course details.
Student.h
This header file defines the Student class, representing students enrolled in the system. Here are the details:

Class Definition:
Student: Represents a student in the system, inheriting from the Person class.
Attributes:
studentID: An integer representing the student's ID.
studentName: A string representing the student's name.
enrolledCourses: A vector containing pointers to courses in which the student is enrolled.
Member Functions:
Constructors: To initialize student attributes.
Methods for enrolling/dropping courses, displaying fee challans, and retrieving student details.
EnrollmentSystem.h
This header file defines the EnrollmentSystem class, responsible for managing course enrollments and interactions between administrators, students, and courses. Here are the details:

Class Definition:
EnrollmentSystem: Manages course enrollments and interactions within the system.
Attributes:
AvailableCourses: A vector containing available courses in the system.
Member Functions:
Methods for enrolling students in courses, adding/removing courses from enrollment, searching courses by various criteria, and handling course waitlists.

Usage:
Compile the code using a C++ compiler.
Run the executable file.
Follow the on-screen instructions to navigate through the system menus and perform tasks.

Known Issues:
The feature to reuse the saved state of students to continue the program is still under development.

Contributing:
Contributions are welcome! Fork the repository, make changes, and submit pull requests.
