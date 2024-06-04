Enrollment Management System (EMS)

Introduction:

This C++ program implements an Enrollment Management System (EMS) for a student administration system. It allows users (admins and students) to interact with course enrollment, student management, and data persistence.

Features:

Admin Functionality:
Add courses to the enrollment system.
Remove courses from the enrollment system.
Search for courses by instructor, level, or department.
Expel students.
Increase the capacity of existing courses.
Student Functionality:
Enroll in courses.
Drop courses.
Generate fee challans (placeholder for future implementation).
Search for courses by instructor, level, or department.
Data Persistence:
Saves enrollment state, including enrolled students and courses, to a file (EMS.txt) upon admin's choice.
Loads enrollment state from the file (EMS.txt) upon program startup (Note: This functionality is not currently implemented but included for future reference).


Usage:

Start the program.
Choose your role: Admin (1) or Student (2).
If you choose Admin:
Enter your Admin ID.
The Admin Menu will be presented.
Select the desired action.
If you choose Student:
Enter your Student ID and name.
The Student Menu will be presented.
Select the desired action.

Additional Notes:

The loadStateFromFile function in main.cpp is currently not implemented.
Error handling and input validation could be further improved.
Consider adding comments throughout the code for better readability and maintainability.
