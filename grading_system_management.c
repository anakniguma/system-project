#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 180

// Student structure
struct Student {
    int id;
    char name[50];
    float introToComputing;
    float pcTroubleshooting;
    float computerProgramming1;
    float understandingTheSelf;
    float nstp;
    float rizal;
    float philippineHistory;
    float pathfit1;
    float peopleAndEarthEcosystem;
    float finalGrade;
    float gpa;
    char remarks[20];
};

// Global array to store students
struct Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void addStudent();
void viewAllStudents();
void calculateGrades();
float calculateFinalGrade(float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8, float s9);
float convertToGPA(float grade);
void determineRemarks(int index);
void displayStatistics();
void displayDeansList();

int main() {
    int choice;
    
    printf("=== GRADE MANAGEMENT SYSTEM ===\n\n");
    
    do {
        printf("\n--- MENU ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Calculate Final Grades\n");
        printf("4. Display Statistics\n");
        printf("5. Display Dean's List\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewAllStudents();
                break;
            case 3:
                calculateGrades();
                break;
            case 4:
                displayStatistics();
                break;
            case 5:
                displayDeansList();
                break;
            case 0:
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}

// Add a new student
void addStudent() {
    if(studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }
    
    struct Student s;
    
    printf("\n--- ADD STUDENT ---\n");
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);
    printf("\nEnter grades for each subject (0-100):\n");
    printf("Intro to Computing: ");
    scanf("%f", &s.introToComputing);
    printf("PC Troubleshooting: ");
    scanf("%f", &s.pcTroubleshooting);
    printf("Computer Programming 1: ");
    scanf("%f", &s.computerProgramming1);
    printf("Understanding the Self: ");
    scanf("%f", &s.understandingTheSelf);
    printf("NSTP: ");
    scanf("%f", &s.nstp);
    printf("The Life and Works of Jose Rizal: ");
    scanf("%f", &s.rizal);
    printf("Readings in Philippine History with IPS: ");
    scanf("%f", &s.philippineHistory);
    printf("PATHFit 1: ");
    scanf("%f", &s.pathfit1);
    printf("People and Earth's Ecosystem: ");
    scanf("%f", &s.peopleAndEarthEcosystem);
    
    // Initialize other fields
    s.finalGrade = 0;
    s.gpa = 0;
    strcpy(s.remarks, "Not Calculated");
    
    students[studentCount] = s;
    studentCount++;
    
    printf("Student added successfully!\n");
}

// View all students
void viewAllStudents() {
    if(studentCount == 0) {
        printf("\nNo students in the system.\n");
        return;
    }
    
    printf("\n--- ALL STUDENTS ---\n");
    printf("%-5s %-25s %-10s %-6s %-15s\n", 
           "ID", "Name", "Average", "GPA", "Remarks");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < studentCount; i++) {
        printf("%-5d %-25s %-10.2f %-6.2f %-15s\n",
               students[i].id,
               students[i].name,
               students[i].finalGrade,
               students[i].gpa,
               students[i].remarks);
    }
}

// Calculate final grades for all students
void calculateGrades() {
    if(studentCount == 0) {
        printf("\nNo students to calculate grades for.\n");
        return;
    }
    
    for(int i = 0; i < studentCount; i++) {
        // Calculate average of all 9 subjects
        students[i].finalGrade = calculateFinalGrade(
            students[i].introToComputing,
            students[i].pcTroubleshooting,
            students[i].computerProgramming1,
            students[i].understandingTheSelf,
            students[i].nstp,
            students[i].rizal,
            students[i].philippineHistory,
            students[i].pathfit1,
            students[i].peopleAndEarthEcosystem
        );
        
        // Convert to GPA
        students[i].gpa = convertToGPA(students[i].finalGrade);
        
        // Determine remarks
        determineRemarks(i);
    }
    
    printf("\nGrades calculated for all students!\n");
}

// Mathematical function: Calculate average of all subjects
float calculateFinalGrade(float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8, float s9) {
    return (s1 + s2 + s3 + s4 + s5 + s6 + s7 + s8 + s9) / 9.0;
}

// Mathematical function: Convert numerical grade to GPA (Philippine scale)
float convertToGPA(float grade) {
    if(grade >= 97) return 1.0;
    else if(grade >= 94) return 1.25;
    else if(grade >= 91) return 1.5;
    else if(grade >= 88) return 1.75;
    else if(grade >= 85) return 2.0;
    else if(grade >= 82) return 2.25;
    else if(grade >= 79) return 2.5;
    else if(grade >= 76) return 2.75;
    else if(grade >= 75) return 3.0;
    else return 5.0;
}

// Logical function: Determine pass/fail remarks
void determineRemarks(int index) {
    float gpa = students[index].gpa;
    
    if(gpa >= 1.0 && gpa <= 1.75) {
        strcpy(students[index].remarks, "DEAN'S LIST");
    }
    else if(gpa >= 1.75 && gpa < 3.0) {
        strcpy(students[index].remarks, "PASSED");
    }
    else if(gpa == 3.0) {
        strcpy(students[index].remarks, "CONDITIONAL");
    }
    else {
        strcpy(students[index].remarks, "FAILED");
    }
}

// Display class statistics
void displayStatistics() {
    if(studentCount == 0) {
        printf("\nNo students to display statistics for.\n");
        return;
    }
    
    float highest = students[0].finalGrade;
    float lowest = students[0].finalGrade;
    float sum = 0;
    int passed = 0;
    int failed = 0;
    
    // Mathematical calculations
    for(int i = 0; i < studentCount; i++) {
        float grade = students[i].finalGrade;
        
        if(grade > highest) highest = grade;
        if(grade < lowest) lowest = grade;
        sum += grade;
        
        // Logical condition
        if(students[i].gpa <= 3.0) {
            passed++;
        } else {
            failed++;
        }
    }
    
    float average = sum / studentCount;
    
    printf("\n--- CLASS STATISTICS ---\n");
    printf("Total Students: %d\n", studentCount);
    printf("Highest Grade: %.2f\n", highest);
    printf("Lowest Grade: %.2f\n", lowest);
    printf("Average Grade: %.2f\n", average);
    printf("Passed: %d\n", passed);
    printf("Failed: %d\n", failed);
    printf("Pass Rate: %.2f%%\n", (float)passed/studentCount * 100);
}

// Display Dean's List students
void displayDeansList() {
    if(studentCount == 0) {
        printf("\nNo students in the system.\n");
        return;
    }
    
    printf("\n--- DEAN'S LIST (GPA 1.0 - 1.75) ---\n");
    printf("%-5s %-25s %-10s %-6s\n", "ID", "Name", "Average", "GPA");
    printf("----------------------------------------------------\n");
    
    int count = 0;
    
    // Logical condition: Check if student qualifies for Dean's List
    for(int i = 0; i < studentCount; i++) {
        if(students[i].gpa >= 1.0 && students[i].gpa <= 1.75) {
            printf("%-5d %-25s %-10.2f %-6.2f\n",
                   students[i].id,
                   students[i].name,
                   students[i].finalGrade,
                   students[i].gpa);
            count++;
        }
    }
    
    if(count == 0) {
        printf("No students in the Dean's List.\n");
    } else {
        printf("\nTotal: %d student(s)\n", count);
    }
}