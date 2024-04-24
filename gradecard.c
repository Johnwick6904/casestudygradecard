#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gradecard.h"

float calculateCGPA(float ag) {
    if (ag >= 90.0) {
        return 4.0;  
    } else if (ag >= 80.0) {
        return 3.5;  
    } else if (ag >= 70.0) {
        return 3.0;  
    } else if (ag >= 60.0) {
        return 2.5;  
    } else if (ag >= 50.0) {
        return 2.0;  
    } else if (ag >= 40.0) {
        return 1.5;  
    } else {
        return 0.0;  
    }
}


const char *getRemarks(float cgp) {
    if (cgp >= 4.0) {
        return "Excellent";
    } else if (cgp >= 3.5) {
        return "Very Good";
    } else if (cgp >= 3.0) {
        return "Good";
    } else if (cgp >= 2.0) {
        return "Average";
    } else {
        return "Below Average";
    }
}

void fillGradeCard(GradeCard *gradeCard) {
    
    gradeCard->numStudents = 1;
    gradeCard->students = (Student *)malloc(gradeCard->numStudents * sizeof(Student));
    if (gradeCard->students == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    Student *student = &gradeCard->students[0];

    // Input student name
    printf("Enter student name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = '\0';  // Remove newline character

    // Input number of exams
    printf("Enter number of exams: ");
    scanf("%d", &student->numExams);

    // Input number of subjects per exam
    printf("Enter number of subjects per exam: ");
    scanf("%d", &student->subjectsPerExam);

    // Allocate memory for marks array based on number of exams
    student->marks = (float *)malloc(student->numExams * student->subjectsPerExam * sizeof(float));
    if (student->marks == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Input marks for each exam and subject
    for (int i = 0; i < student->numExams; i++) {
        printf("Enter marks for Exam %d subjects:\n", i + 1);
        for (int j = 0; j < student->subjectsPerExam; j++) {
            printf("Enter marks for Subject %d: ", j + 1);
            scanf("%f", &student->marks[i * student->subjectsPerExam + j]);
        }
    }
}

void printGradeCard(const GradeCard *gradeCard) {
    const Student *student = &gradeCard->students[0];

    printf("\nGrade Card for %s - PES University\n", student->name);
    printf("-------------------------------------\n");
    printf("Teacher: Mr. Biwas\n");
    printf("Principal: Dr. Subhash Kulkarni\n");
    printf("University: PES University\n\n");
    
    printf("Number of Exams: %d\n", student->numExams);
    printf("Subjects per Exam: %d\n\n", student->subjectsPerExam);

    printf("*****Exam-wise*****\n\n");
    for (int i = 0; i < student->numExams; i++) {
        printf("Exam %d:\n", i + 1);
        printf("-----------\n");
        
        float totalMarks = 0.0;
        for (int j = 0; j < student->subjectsPerExam; j++) {
            float marks = student->marks[i * student->subjectsPerExam + j];
            printf("Subject %d: %.2f\n", j + 1, marks);
            totalMarks += marks;
        }
        
        // Calculate average marks for the exam
        float ag = totalMarks / student->subjectsPerExam;
        printf("Average Marks: %.2f\n", ag);

        // Calculate CGPA based on average marks
        float cgp = calculateCGPA(ag);
        printf("CGPA: %.2f\n", cgp);

        // Get remarks based on CGPA
        const char *remarks = getRemarks(cgp);
        printf("Remarks: %s\n\n", remarks);
    }
}

void freeGradeCard(GradeCard *gradeCard) {
    if (gradeCard->students != NULL) {
        for (int i = 0; i < gradeCard->numStudents; i++) {
            if (gradeCard->students[i].marks != NULL) {
                free(gradeCard->students[i].marks);
                gradeCard->students[i].marks = NULL;
            }
        }
        free(gradeCard->students);
        gradeCard->students = NULL;
    }
    gradeCard->numStudents = 0;
}