#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 180
#define MAX_NAME 180

// Structure to store student information
typedef struct {
    int id;
    char name[MAX_NAME];
    float grades[5]; // 5 subjects
    float average;
    char status[10];
} Student;

// Function prototypes
void displayMenu();
void addStudent(Student students[], int *count);
void displayAllStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void calculateAverage(Student *student);
void updateStudent(Student students[], int count);
void deleteStudent(Student students[], int *count);
void displayTopStudents(Student students[], int count);
void saveToFile(Student students[], int count);
void loadFromFile(Student students[], int *count);

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;
    
    // Load existing data from file
    loadFromFile(students, &studentCount);
    
    printf("\n========================================\n");
    printf("  STUDENT GRADE MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                searchStudent(students, studentCount);
                break;
            case 4:
                updateStudent(students, studentCount);
                break;
            case 5:
                deleteStudent(students, &studentCount);
                break;
            case 6:
                displayTopStudents(students, studentCount);
                break;
            case 7:
                saveToFile(students, studentCount);
                printf("\nData saved successfully!\n");
                break;
            case 8:
                saveToFile(students, studentCount);
                printf("\nThank you for using the system!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while(choice != 8);
    
    return 0;
}

void displayMenu() {
    printf("\n========================================\n");
    printf("            MAIN MENU\n");
    printf("========================================\n");
    printf("1. Add New Student\n");
    printf("2. Display All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Display Top Students\n");
    printf("7. Save Data\n");
    printf("8. Exit\n");
    printf("========================================\n");
}

void addStudent(Student students[], int *count) {
    if(*count >= MAX_STUDENTS) {
        printf("\nDatabase is full! Cannot add more students.\n");
        return;
    }
    
    Student newStudent;
    
    printf("\n--- Add New Student ---\n");
    printf("Enter Student ID: ");
    scanf("%d", &newStudent.id);
    
    // Check for duplicate ID
    for(int i = 0; i < *count; i++) {
        if(students[i].id == newStudent.id) {
            printf("Error: Student ID already exists!\n");
            return;
        }
    }
    
    printf("Enter Student Name: ");
    scanf(" %[^\n]", newStudent.name);
    
    printf("Enter grades for 5 subjects:\n");
    for(int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &newStudent.grades[i]);
        
        // Validate grade
        while(newStudent.grades[i] < 0 || newStudent.grades[i] > 100) {
            printf("Invalid grade! Enter again (0-100): ");
            scanf("%f", &newStudent.grades[i]);
        }
    }
    
    calculateAverage(&newStudent);
    students[*count] = newStudent;
    (*count)++;
    
    printf("\nStudent added successfully!\n");
}

void calculateAverage(Student *student) {
    float sum = 0;
    for(int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    student->average = sum / 5.0;
    
    // Determine status
    if(student->average >= 75) {
        strcpy(student->status, "PASSED");
    } else {
        strcpy(student->status, "FAILED");
    }
}

void displayAllStudents(Student students[], int count) {
    if(count == 0) {
        printf("\nNo students in the database!\n");
        return;
    }
    
    printf("\n========================================================================================================\n");
    printf("%-6s %-20s %-8s %-8s %-8s %-8s %-8s %-10s %-10s\n", 
           "ID", "Name", "ITC", "ComProg", "PCT", "NSTP", "UTS", "Average", "Status");
    printf("========================================================================================================\n");
    
    for(int i = 0; i < count; i++) {
        printf("%-6d %-20s %-8.2f %-8.2f %-8.2f %-8.2f %-8.2f %-10.2f %-10s\n",
               students[i].id,
               students[i].name,
               students[i].grades[0],
               students[i].grades[1],
               students[i].grades[2],
               students[i].grades[3],
               students[i].grades[4],
               students[i].average,
               students[i].status);
    }
    printf("========================================================================================================\n");
}

void searchStudent(Student students[], int count) {
    int searchId;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchId);
    
    for(int i = 0; i < count; i++) {
        if(students[i].id == searchId) {
            printf("\n--- Student Found ---\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Grades: %.2f, %.2f, %.2f, %.2f, %.2f\n",
                   students[i].grades[0], students[i].grades[1],
                   students[i].grades[2], students[i].grades[3],
                   students[i].grades[4]);
            printf("Average: %.2f\n", students[i].average);
            printf("Status: %s\n", students[i].status);
            return;
        }
    }
    printf("\nStudent not found!\n");
}

void updateStudent(Student students[], int count) {
    int searchId;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &searchId);
    
    for(int i = 0; i < count; i++) {
        if(students[i].id == searchId) {
            printf("\n--- Update Student ---\n");
            printf("Enter new name (current: %s): ", students[i].name);
            scanf(" %[^\n]", students[i].name);
            
            printf("Enter new grades for 5 subjects:\n");
            for(int j = 0; j < 5; j++) {
                printf("Subject %d (current: %.2f): ", j + 1, students[i].grades[j]);
                scanf("%f", &students[i].grades[j]);
            }
            
            calculateAverage(&students[i]);
            printf("\nStudent updated successfully!\n");
            return;
        }
    }
    printf("\nStudent not found!\n");
}

void deleteStudent(Student students[], int *count) {
    int searchId;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &searchId);
    
    for(int i = 0; i < *count; i++) {
        if(students[i].id == searchId) {
            // Shift all students after this one
            for(int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("\nStudent deleted successfully!\n");
            return;
        }
    }
    printf("\nStudent not found!\n");
}

void displayTopStudents(Student students[], int count) {
    if(count == 0) {
        printf("\nNo students in the database!\n");
        return;
    }
    
    // Create a copy to sort
    Student temp[MAX_STUDENTS];
    for(int i = 0; i < count; i++) {
        temp[i] = students[i];
    }
    
    // Bubble sort by average (descending)
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(temp[j].average < temp[j + 1].average) {
                Student swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    printf("\n--- Top 5 Students ---\n");
    int limit = (count < 5) ? count : 5;
    for(int i = 0; i < limit; i++) {
        printf("%d. %s (ID: %d) - Average: %.2f\n",
               i + 1, temp[i].name, temp[i].id, temp[i].average);
    }
}

void saveToFile(Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if(file == NULL) {
        printf("\nError saving file!\n");
        return;
    }
    
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
}

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if(file == NULL) {
        *count = 0;
        return;
    }
    
    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(Student), *count, file);
    fclose(file);
    
    printf("Loaded %d students from file.\n", *count);
}