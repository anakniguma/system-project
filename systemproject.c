#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 180

typedef struct {
    int stud_id;
    char fullname[50];
    float intro_computing;
    float pc_troubleshoot;
    float comp_prog1;
    float understanding_self;
    float nstp_grade;
    float rizal_grade;
    float phil_history;
    float pathfit;
    float earth_ecosystem;
    float final_avg;
    float student_gpa;
    char status[20];
} StudentRecord;

StudentRecord records[MAX];
int total = 0;

void menu();
void add();
void show_all();
void find();
void edit();
void remove_record();
void compute();
void stats();
void honors();
void write_file();
void read_file();
void wait_enter();
float get_average(float g1, float g2, float g3, float g4, float g5, float g6, float g7, float g8, float g9);
float grade_to_gpa(float avg);
void set_status(int idx);

int main() {
    menu();
    return 0;
}

void menu() {
    int opt;
    
    printf("\n========================================\n");
    printf("   STUDENT GRADE MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    
    while(1) {
        printf("\n[1] Add New Student\n");
        printf("[2] Show All Records\n");
        printf("[3] Find Student\n");
        printf("[4] Edit Grades\n");
        printf("[5] Remove Student\n");
        printf("[6] Compute All Grades\n");
        printf("[7] Class Statistics\n");
        printf("[8] Dean's List\n");
        printf("[9] Save Data\n");
        printf("[10] Load Data\n");
        printf("[0] Exit Program\n");
        printf("\nChoice: ");
        scanf("%d", &opt);
        
        if(opt == 1) { add(); wait_enter(); }
        else if(opt == 2) { show_all(); wait_enter(); }
        else if(opt == 3) { find(); wait_enter(); }
        else if(opt == 4) { edit(); wait_enter(); }
        else if(opt == 5) { remove_record(); wait_enter(); }
        else if(opt == 6) { compute(); wait_enter(); }
        else if(opt == 7) { stats(); wait_enter(); }
        else if(opt == 8) { honors(); wait_enter(); }
        else if(opt == 9) { write_file(); wait_enter(); }
        else if(opt == 10) { read_file(); wait_enter(); }
        else if(opt == 0) { 
            printf("\nExiting... Thank you!\n"); 
            break; 
        }
        else { printf("\nInvalid input!\n"); }
    }
}

void wait_enter() {
    printf("\n>> Press ENTER to continue <<");
    getchar();
    getchar();
}

void add() {
    if(total >= MAX) {
        printf("\nDatabase full! Cannot add more.\n");
        return;
    }
    
    StudentRecord temp;
    
    printf("\n=== ADD STUDENT ===\n");
    printf("Student ID: ");
    scanf("%d", &temp.stud_id);
    printf("Full Name: ");
    scanf(" %[^\n]", temp.fullname);
    
    printf("\n>> Enter subject grades (0-100) or -1 if incomplete <<\n");
    printf("Intro to Computing: ");
    scanf("%f", &temp.intro_computing);
    printf("PC Troubleshooting: ");
    scanf("%f", &temp.pc_troubleshoot);
    printf("Computer Programming 1: ");
    scanf("%f", &temp.comp_prog1);
    printf("Understanding the Self: ");
    scanf("%f", &temp.understanding_self);
    printf("NSTP: ");
    scanf("%f", &temp.nstp_grade);
    printf("Life and Works of Jose Rizal: ");
    scanf("%f", &temp.rizal_grade);
    printf("Philippine History with IPS: ");
    scanf("%f", &temp.phil_history);
    printf("PATHFit 1: ");
    scanf("%f", &temp.pathfit);
    printf("People and Earth's Ecosystem: ");
    scanf("%f", &temp.earth_ecosystem);
    
    temp.final_avg = 0;
    temp.student_gpa = 0;
    strcpy(temp.status, "Pending");
    
    records[total] = temp;
    total++;
    
    printf("\n>> Student added! <<\n");
}

void show_all() {
    if(total == 0) {
        printf("\nNo records found.\n");
        return;
    }
    
    printf("\n=== ALL STUDENT RECORDS ===\n");
    printf("%-8s %-30s %-12s %-8s %-18s\n", "ID", "Name", "Average", "GPA", "Status");
    printf("--------------------------------------------------------------------------------\n");
    
    int i;
    for(i = 0; i < total; i++) {
        printf("%-8d %-30s %-12.2f %-8.2f %-18s\n",
               records[i].stud_id,
               records[i].fullname,
               records[i].final_avg,
               records[i].student_gpa,
               records[i].status);
    }
}

void find() {
    if(total == 0) {
        printf("\nNo records available.\n");
        return;
    }
    
    int id, i, loc = -1;
    printf("\n=== SEARCH STUDENT ===\n");
    printf("Enter Student ID: ");
    scanf("%d", &id);
    
    for(i = 0; i < total; i++) {
        if(records[i].stud_id == id) {
            loc = i;
            break;
        }
    }
    
    if(loc == -1) {
        printf("\nStudent ID not found!\n");
        return;
    }
    
    printf("\n=== STUDENT INFORMATION ===\n");
    printf("ID: %d\n", records[loc].stud_id);
    printf("Name: %s\n", records[loc].fullname);
    printf("\nSubject Grades:\n");
    printf("  Intro to Computing: %.2f\n", records[loc].intro_computing);
    printf("  PC Troubleshooting: %.2f\n", records[loc].pc_troubleshoot);
    printf("  Computer Programming 1: %.2f\n", records[loc].comp_prog1);
    printf("  Understanding the Self: %.2f\n", records[loc].understanding_self);
    printf("  NSTP: %.2f\n", records[loc].nstp_grade);
    printf("  Life and Works of Jose Rizal: %.2f\n", records[loc].rizal_grade);
    printf("  Philippine History with IPS: %.2f\n", records[loc].phil_history);
    printf("  PATHFit 1: %.2f\n", records[loc].pathfit);
    printf("  People and Earth's Ecosystem: %.2f\n", records[loc].earth_ecosystem);
    printf("\nFinal Average: %.2f\n", records[loc].final_avg);
    printf("GPA: %.2f\n", records[loc].student_gpa);
    printf("Status: %s\n", records[loc].status);
}

void edit() {
    if(total == 0) {
        printf("\nNo records to edit.\n");
        return;
    }
    
    int id, i, loc = -1;
    printf("\n=== UPDATE GRADES ===\n");
    printf("Enter Student ID: ");
    scanf("%d", &id);
    
    for(i = 0; i < total; i++) {
        if(records[i].stud_id == id) {
            loc = i;
            break;
        }
    }
    
    if(loc == -1) {
        printf("\nStudent not found!\n");
        return;
    }
    
    printf("Editing: %s\n", records[loc].fullname);
    printf("\n>> Enter new grades (0-100 or -1 for incomplete) <<\n");
    printf("Intro to Computing: ");
    scanf("%f", &records[loc].intro_computing);
    printf("PC Troubleshooting: ");
    scanf("%f", &records[loc].pc_troubleshoot);
    printf("Computer Programming 1: ");
    scanf("%f", &records[loc].comp_prog1);
    printf("Understanding the Self: ");
    scanf("%f", &records[loc].understanding_self);
    printf("NSTP: ");
    scanf("%f", &records[loc].nstp_grade);
    printf("Life and Works of Jose Rizal: ");
    scanf("%f", &records[loc].rizal_grade);
    printf("Philippine History with IPS: ");
    scanf("%f", &records[loc].phil_history);
    printf("PATHFit 1: ");
    scanf("%f", &records[loc].pathfit);
    printf("People and Earth's Ecosystem: ");
    scanf("%f", &records[loc].earth_ecosystem);
    
    printf("\n>> Grades updated! Don't forget to recompute (Option 6) <<\n");
}

void remove_record() {
    if(total == 0) {
        printf("\nNo records to delete.\n");
        return;
    }
    
    int id, i, loc = -1, confirm;
    printf("\n=== DELETE STUDENT ===\n");
    printf("Enter Student ID: ");
    scanf("%d", &id);
    
    for(i = 0; i < total; i++) {
        if(records[i].stud_id == id) {
            loc = i;
            break;
        }
    }
    
    if(loc == -1) {
        printf("\nStudent not found!\n");
        return;
    }
    
    printf("Delete %s? (1=Yes / 0=No): ", records[loc].fullname);
    scanf("%d", &confirm);
    
    if(confirm == 1) {
        for(i = loc; i < total - 1; i++) {
            records[i] = records[i + 1];
        }
        total--;
        printf("\n>> Student deleted! <<\n");
    } else {
        printf("\n>> Deletion cancelled! <<\n");
    }
}

void compute() {
    if(total == 0) {
        printf("\nNo students to compute.\n");
        return;
    }
    
    int i, j;
    for(i = 0; i < total; i++) {
        int incomplete = 0, absent = 0;
        
        float all_grades[9] = {
            records[i].intro_computing,
            records[i].pc_troubleshoot,
            records[i].comp_prog1,
            records[i].understanding_self,
            records[i].nstp_grade,
            records[i].rizal_grade,
            records[i].phil_history,
            records[i].pathfit,
            records[i].earth_ecosystem
        };
        
        for(j = 0; j < 9; j++) {
            if(all_grades[j] < 0) incomplete = 1;
            else if(all_grades[j] == 0) absent = 1;
        }
        
        if(incomplete) {
            strcpy(records[i].status, "INC");
            records[i].final_avg = 0;
            records[i].student_gpa = 0;
        } 
        else if(absent) {
            strcpy(records[i].status, "FDA");
            records[i].final_avg = 0;
            records[i].student_gpa = 0;
        } 
        else {
            records[i].final_avg = get_average(
                records[i].intro_computing,
                records[i].pc_troubleshoot,
                records[i].comp_prog1,
                records[i].understanding_self,
                records[i].nstp_grade,
                records[i].rizal_grade,
                records[i].phil_history,
                records[i].pathfit,
                records[i].earth_ecosystem
            );
            
            records[i].student_gpa = grade_to_gpa(records[i].final_avg);
            set_status(i);
        }
    }
    
    printf("\n>> Computation complete! <<\n");
}

float get_average(float g1, float g2, float g3, float g4, float g5, float g6, float g7, float g8, float g9) {
    float sum = g1 + g2 + g3 + g4 + g5 + g6 + g7 + g8 + g9;
    float avg = sum / 9.0;
    return (int)(avg * 100 + 0.5) / 100.0;
}

float grade_to_gpa(float avg) {
    if(avg >= 97) return 1.0;
    if(avg >= 94) return 1.25;
    if(avg >= 91) return 1.5;
    if(avg >= 88) return 1.75;
    if(avg >= 85) return 2.0;
    if(avg >= 82) return 2.25;
    if(avg >= 79) return 2.5;
    if(avg >= 76) return 2.75;
    if(avg >= 75) return 3.0;
    return 5.0;
}

void set_status(int idx) {
    float gpa = records[idx].student_gpa;
    
    if(gpa >= 1.0 && gpa <= 1.75) 
        strcpy(records[idx].status, "DEAN'S LIST");
    else if(gpa > 1.75 && gpa < 3.0) 
        strcpy(records[idx].status, "PASSED");
    else if(gpa == 3.0) 
        strcpy(records[idx].status, "CONDITIONAL");
    else 
        strcpy(records[idx].status, "F");
}

void stats() {
    if(total == 0) {
        printf("\nNo data for statistics.\n");
        return;
    }
    
    float max = 0, min = 100, sum = 0;
    int pass = 0, fail = 0, valid = 0, i;
    
    for(i = 0; i < total; i++) {
        if(strcmp(records[i].status, "INC") != 0 && strcmp(records[i].status, "FDA") != 0) {
            float grade = records[i].final_avg;
            
            if(grade > max) max = grade;
            if(grade < min) min = grade;
            sum += grade;
            valid++;
            
            if(records[i].student_gpa <= 3.0) pass++;
            else fail++;
        }
    }
    
    if(valid == 0) {
        printf("\nNo valid grades for statistics.\n");
        return;
    }
    
    printf("\n=== CLASS STATISTICS ===\n");
    printf("Total Enrolled: %d\n", total);
    printf("With Valid Grades: %d\n", valid);
    printf("Highest: %.2f\n", max);
    printf("Lowest: %.2f\n", min);
    printf("Average: %.2f\n", sum / valid);
    printf("Passed: %d\n", pass);
    printf("Failed: %d\n", fail);
    printf("Pass Rate: %.2f%%\n", (float)pass / valid * 100);
}

void honors() {
    if(total == 0) {
        printf("\nNo students in system.\n");
        return;
    }
    
    printf("\n=== DEAN'S LIST ===\n");
    printf("%-8s %-30s %-12s %-8s\n", "ID", "Name", "Average", "GPA");
    printf("------------------------------------------------------------\n");
    
    int count = 0, i;
    for(i = 0; i < total; i++) {
        if(records[i].student_gpa >= 1.0 && records[i].student_gpa <= 1.75) {
            printf("%-8d %-30s %-12.2f %-8.2f\n",
                   records[i].stud_id,
                   records[i].fullname,
                   records[i].final_avg,
                   records[i].student_gpa);
            count++;
        }
    }
    
    if(count == 0) printf("No students qualified.\n");
    else printf("\nTotal: %d student(s)\n", count);
}

void write_file() {
    FILE *fp = fopen("student_data.txt", "w");
    
    if(fp == NULL) {
        printf("\nError: Cannot save file!\n");
        return;
    }
    
    fprintf(fp, "%d\n", total);
    
    int i;
    for(i = 0; i < total; i++) {
        fprintf(fp, "%d\n%s\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%.2f\n%s\n",
                records[i].stud_id,
                records[i].fullname,
                records[i].intro_computing,
                records[i].pc_troubleshoot,
                records[i].comp_prog1,
                records[i].understanding_self,
                records[i].nstp_grade,
                records[i].rizal_grade,
                records[i].phil_history,
                records[i].pathfit,
                records[i].earth_ecosystem,
                records[i].final_avg,
                records[i].student_gpa,
                records[i].status);
    }
    
    fclose(fp);
    printf("\n>> Data saved successfully! <<\n");
}

void read_file() {
    FILE *fp = fopen("student_data.txt", "r");
    
    if(fp == NULL) {
        printf("\nError: File not found!\n");
        return;
    }
    
    fscanf(fp, "%d\n", &total);
    
    int i;
    for(i = 0; i < total; i++) {
        fscanf(fp, "%d\n", &records[i].stud_id);
        fgets(records[i].fullname, 50, fp);
        records[i].fullname[strcspn(records[i].fullname, "\n")] = 0;
        fscanf(fp, "%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n",
               &records[i].intro_computing,
               &records[i].pc_troubleshoot,
               &records[i].comp_prog1,
               &records[i].understanding_self,
               &records[i].nstp_grade,
               &records[i].rizal_grade,
               &records[i].phil_history,
               &records[i].pathfit,
               &records[i].earth_ecosystem,
               &records[i].final_avg,
               &records[i].student_gpa);
        fgets(records[i].status, 20, fp);
        records[i].status[strcspn(records[i].status, "\n")] = 0;
    }
    
    fclose(fp);
    printf("\n>> Data loaded! Total: %d students <<\n", total);
}