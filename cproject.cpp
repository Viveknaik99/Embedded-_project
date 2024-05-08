#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_NAME_LENGTH 50

struct Student {
    char name[MAX_NAME_LENGTH];
    int grades[5];
};

void inputStudentData(struct Student students[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        printf("Enter student %d name: ", i + 1);
        scanf("%s", students[i].name);

        printf("Enter grades for %s (5 subjects):\n", students[i].name);
        for (int j = 0; j < 5; j++) {
            printf("Subject %d: ", j + 1);
            scanf("%d", &students[i].grades[j]);
        }
    }
}

void calculateAverageGrades(struct Student students[], int numStudents, float averages[]) 
{
    for (int i = 0; i < numStudents; i++) 
	{
        int total = 0;
        for (int j = 0; j < 5; j++) 
		{
            total += students[i].grades[j];
        }
        averages[i] = (float)total / 5;
    }
}

void displayStudentData(struct Student students[], int numStudents, float averages[]) 
{
    printf("\nStudent Average Grades:\n");
    for (int i = 0; i < numStudents; i++) 
	{
        printf("Name: %s\n", students[i].name);
        printf("Average Grade: %.2f\n", averages[i]);
    }
}

int main() 
{
    struct Student students[MAX_STUDENTS];
    float averages[MAX_STUDENTS];
    int numStudents;

    printf("Student Grade Tracker\n");
    printf("Enter the number of students (up to %d): ", MAX_STUDENTS);
    scanf("%d", &numStudents);

    if (numStudents > MAX_STUDENTS) 
	{
        printf("Exceeded the maximum number of students.\n");
        return 1;
    }

    inputStudentData(students, numStudents);
    calculateAverageGrades(students, numStudents, averages);
    displayStudentData(students, numStudents, averages);

    // Save student data to a file
    FILE *file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    for (int i = 0; i < numStudents; i++) 
	{
        fprintf(file, "Name: %s\n", students[i].name);
        fprintf(file, "Average Grade: %.2f\n\n", averages[i]);
    }

    fclose(file);
    printf("Student data saved to 'student_data.txt'.\n");

    return 0;
}

