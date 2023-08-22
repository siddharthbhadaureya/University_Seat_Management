#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COURSES 10
#define MAX_STUDENTS 100

// Structures
struct Course {
    char code[10];
    char title[50];
    int seats;
};

struct Student {
    int id;
    char name[50];
    int enrolledCourses[MAX_COURSES];
    int numCourses;
};

// Global arrays for courses and students
struct Course courses[MAX_COURSES];
struct Student students[MAX_STUDENTS];
int numCourses = 0;
int numStudents = 0;

// Function to display course and seat availability
void displayCourses() {
    FILE *fp;
    int i;
    char ch, str[100];
    fp = fopen("E:\\University_seats.txt","r");
    if(fp==NULL){
        printf("\nThe file could not be opened\n");
        exit(1);
    }
    else{
        printf("Available Courses:\n");
        ch = fgetc(fp);
        for (i = 0; feof(fp)==0; i++) {
            fflush(stdin);
            str[i] = ch;
            ch = fgetc(fp);
        }
        str[i]='\0';
        for(i = 0; i < feof(fp); i++){
            printf("%c", str[i]);
        }
    }
    fclose(fp);
    printf("\n");
//        printf("%d. %s - %s (Seats: %d)\n", i + 1, courses[i].code, courses[i].title, courses[i].seats);
}

// Function to add a new course
void addCourse() {
    FILE *fp, *fp1;
    int number_of_modifications, i;
    fp = fopen("E:\\University_seats.txt","a");
    printf("Enter the number of new courses");
    scanf("%d", &number_of_modifications);

    if(fp==NULL){
        fclose(fp);
        fp1 = fopen("E:\\University_seats.txt","w");

        if (numCourses >= MAX_COURSES) {
            printf("Maximum course limit reached.\n");
            return;
        }
        for(i = 0; i < number_of_modifications; i++){

            printf("Enter course code: ");
            scanf("%s", courses[numCourses].code);
            printf("Enter course title: ");
            scanf(" %[^\n]", courses[numCourses].title);
            printf("Enter number of seats: ");
            scanf("%d", &courses[numCourses].seats);

            fwrite(courses, sizeof(struct Course), 1, fp1);
            i++;
            numCourses++;
        }
        exit(1);
        fclose(fp1);
    }
    else{
        if (numCourses >= MAX_COURSES) {
            printf("Maximum course limit reached.\n");
            return;
        }
        for(i = 0; i < number_of_modifications; i++) {

            printf("Enter course code: ");
            scanf("%s", courses[numCourses].code);
            printf("Enter course title: ");
            scanf(" %[^\n]", courses[numCourses].title);
            printf("Enter number of seats: ");
            scanf("%d", &courses[numCourses].seats);
            fwrite(courses, sizeof(struct Course), 1, fp);
            numCourses++;
            i++;
        }
        fclose(fp);
        exit(1);
    }
    printf("Course added successfully\n");
}
// Function to delete a course
//void deleteCourse(int courseIndex) {
//    if (courseIndex < 0 || courseIndex >= numCourses) {
//        printf("Invalid course index.\n");
//        return;
//    }
//
//    for (int i = courseIndex; i < numCourses - 1; i++) {
//        courses[i] = courses[i + 1];
//    }
//
//    numCourses--;
//    printf("Course deleted successfully.\n");
//}
void main() {
    int choice;
    printf("\nUniversity Course Registration and Management System\n");

    do {
        printf("1. Display Available Courses\n");
        printf("2. Add Course\n");
        printf("3. Delete Course\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCourses();
                break;
            case 2:
                addCourse();
                break;
            case 3:
                int courseIndex;
                printf("Enter course index to delete: ");
                scanf("%d", &courseIndex);
//                deleteCourse(courseIndex - 1);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}