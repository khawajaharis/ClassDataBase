#include <iostream>
#include <string>
#include <limits> // For input validation
using namespace std;

// Structure to store student information
struct Student {
    string name;
    string studentClass;
    int age;
    string department;
    int ID;
};

// Function declarations
void adminMenu(Student *students, int &count);
void addStudent(Student *students, int &count);
void deleteStudent(Student *students, int &count);
void viewAllStudents(Student *students, int count);
void studentMenu(Student *students, int count);
void studentLogin(Student *students, int count);
int getValidatedInt(const string &prompt);

// Constants for credentials
const string ADMIN_USER = "admin";
const string ADMIN_PASS = "admin123";

// Main function
int main() {
    const int MAX_STUDENTS = 100; // Maximum number of students
    Student students[MAX_STUDENTS]; // Array to store student records
    int studentCount = 0; // Current number of students

    while (true) {
        cout << "\n--- Welcome to Student Database System ---\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        int choice = getValidatedInt("");

        if (choice == 1) {
            // Admin login
            string username, password;
            cout << "\nAdmin Login\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (username == ADMIN_USER && password == ADMIN_PASS) {
                adminMenu(students, studentCount);
            } else {
                cout << "Incorrect username or password!\n";
            }
        } else if (choice == 2) {
            // Student login
            studentLogin(students, studentCount);
        } else if (choice == 3) {
            // Exit the program
            cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }
    return 0;
}

// Admin menu
void adminMenu(Student *students, int &count) {
    while (true) {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. View All Students\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        int choice = getValidatedInt("");

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                deleteStudent(students, count);
                break;
            case 3:
                viewAllStudents(students, count);
                break;
            case 4:
                cout << "Logging out...\n";
                return;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}

// Function to add a student
void addStudent(Student *students, int &count) {
    cout << "\n--- Add Student ---\n";
    
    // Variable to store new ID
    int newID;
    bool isDuplicate;

    // Repeat until a unique ID is entered
    do {
        isDuplicate = false; // Assume it's unique
        newID = getValidatedInt("Enter Student ID: ");

        // Check if the ID already exists
        for (int i = 0; i < count; i++) {
            if (students[i].ID == newID) {
                isDuplicate = true; // Found a duplicate
                cout << "Error: Student ID already exists. Please enter a Another ID.\n";
                break;
            }
        }
    } while (isDuplicate);

    students[count].ID = newID; // Assign the unique ID

    // Input other student details
    cout << "Enter Name: ";
    getline(cin, students[count].name);

    cout << "Enter Class: ";
    getline(cin, students[count].studentClass);

    students[count].age = getValidatedInt("Enter Age: ");
    
    cout << "Enter Department: ";
    getline(cin, students[count].department);

    count++;
    cout << "Student added successfully!\n";
}


// Function to delete a student by ID
void deleteStudent(Student *students, int &count) {
    cout << "\n--- Delete Student ---\n";
    int id = getValidatedInt("Enter Student ID to delete: ");

    for (int i = 0; i < count; i++) {
        if (students[i].ID == id) {
            // Shift all records after the deleted student
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            cout << "Student with ID " << id << " deleted successfully!\n";
            return;
        }
    }
    cout << "Student with ID " << id << " not found!\n";
}

// Function to view all students
void viewAllStudents(Student *students, int count) {
    cout << "\n--- Student Records ---\n";
    if (count == 0) {
        cout << "No student records available.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << "ID: " << students[i].ID << ", Name: " << students[i].name
             << ", Class: " << students[i].studentClass << ", Age: " << students[i].age
             << ", Department: " << students[i].department << endl;
    }
}

// Student login and menu
void studentLogin(Student *students, int count) {
    cout << "\n--- Student Login ---\n";
    int id = getValidatedInt("Enter your Student ID: ");

    for (int i = 0; i < count; i++) {
        if (students[i].ID == id) {
            cout << "\n--- Student Information ---\n";
            cout << "ID: " << students[i].ID << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Class: " << students[i].studentClass << endl;
            cout << "Age: " << students[i].age << endl;
            cout << "Department: " << students[i].department << endl;
            return;
        }
    }
    cout << "Student with ID " << id << " not found!\n";
}

// Function to validate integer input
int getValidatedInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}
