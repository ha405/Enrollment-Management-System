Student Management System
Introduction
The Student Management System is a command-line application implemented in C++. It serves as a tool for managing courses, enrollments, and students within an educational institution. The system is designed to be user-friendly and efficient, providing separate interfaces for administrators and students.

Features
Administrators
Administrators have access to a range of features to manage courses and students effectively.

Add Course to Enrollment: Administrators can add new courses to the system's enrollment list. They provide details such as the course code, name, credits, instructor, department, level, and capacity.

Remove Course from Enrollment: Courses that are no longer offered or need to be removed can be deleted from the enrollment list.

Search Course by Instructor: Administrators can search for courses based on the instructor's name. This feature helps in finding courses taught by specific faculty members.

Search Course by Level: Courses can be searched by their level, allowing administrators to filter courses based on academic difficulty or year.

Search Course by Department: Courses can be filtered by department, enabling administrators to view all courses offered within a specific academic department.

Expel Student: Administrators have the authority to expel students from the system. This action removes the student's enrollment records and disassociates them from any courses.

Increase Course Capacity: In case of high demand or special circumstances, administrators can increase the capacity of a course to accommodate more students.

Students
Students have access to features tailored to their enrollment and course management needs.

Enroll in a Course: Students can enroll in courses by providing the course code. The system checks for available capacity and adds the student to the course if space is available. Otherwise, the student is added to the course's waitlist.

Drop a Course: Students can drop courses they are currently enrolled in. This action removes the student from the course roster and increases the available capacity.

Generate Fee Challan: The system generates a fee challan for the student based on their enrolled courses. The challan includes the total fee amount, calculated based on the credits of each course and any miscellaneous charges.

Search Course by Instructor: Students can search for courses based on the instructor's name. This feature helps students find courses taught by specific instructors they prefer.

Search Course by Level: Students can search for courses based on their academic level. This feature allows students to explore courses suitable for their academic progression.

Search Course by Department: Students can search for courses offered within a specific academic department. This feature helps students find courses related to their field of study.

Usage
Compile the Code: Use a C++ compiler to compile the source code.
Run the Executable: Execute the compiled program to launch the Student Management System.
Navigate the Menus: Follow the on-screen instructions to navigate through the system menus and perform tasks.
Known Issues
The feature to reuse the saved state of students to continue the program is still under development.
Contributing
Contributions to the project are welcome! Fork the repository, make changes, and submit pull requests.
