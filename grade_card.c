#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define SUBJECTS 5

/* Simple program that reads a student's name, roll number and 5 subject marks,
   computes total, percentage, assigns a grade, displays result and appends it
   to a file "grades.txt" so multiple students can be stored. */

char get_grade(float percent) {
    if (percent >= 90) return 'A';
    if (percent >= 75) return 'B';
    if (percent >= 60) return 'C';
    if (percent >= 40) return 'D';
    return 'F';
}

int main() {
    char name[MAX_NAME];
    char roll[20];
    float marks[SUBJECTS];
    float total = 0.0f;
    float percent;
    char grade;
    FILE *fp;

    printf("Enter student name: ");
    /* fgets is safer than gets; it keeps the newline if present */
    if (fgets(name, MAX_NAME, stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }
    /* remove trailing newline from fgets */
    name[strcspn(name, "\n")] = '\0';

    printf("Enter roll number: ");
    if (fgets(roll, sizeof(roll), stdin) == NULL) {
        printf("Input error.\n");
        return 1;
    }
    roll[strcspn(roll, "\n")] = '\0';

    for (int i = 0; i < SUBJECTS; i++) {
        printf("Enter marks for subject %d (out of 100): ", i+1);
        if (scanf("%f", &marks[i]) != 1) {
            printf("Invalid input. Exiting.\n");
            return 1;
        }
        if (marks[i] < 0) marks[i] = 0;       // sanitize negative
        if (marks[i] > 100) marks[i] = 100;   // sanitize >100
        total += marks[i];
    }

    percent = (total / (SUBJECTS * 100.0f)) * 100.0f;
    grade = get_grade(percent);

    printf("\n--- Result ---\n");
    printf("Name   : %s\n", name);
    printf("Roll   : %s\n", roll);
    printf("Total  : %.2f / %.0f\n", total, SUBJECTS * 100.0f);
    printf("Percent: %.2f%%\n", percent);
    printf("Grade  : %c\n", grade);

    /* append to file */
    fp = fopen("grades.txt", "a");
    if (fp == NULL) {
        printf("Could not open grades.txt for writing.\n");
        return 1;
    }
    fprintf(fp, "%s,%s,%.2f,%.2f,%c\n", name, roll, total, percent, grade);
    fclose(fp);

    printf("\nSaved record to grades.txt\n");
    return 0;
}
