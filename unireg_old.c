#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_COURSES 10
#define MAX_STUDENTS 100

// Structure
struct Course {
    char code[10];
    char title[50];
    int seats;
};
struct Course courses[MAX_COURSES];

int numCourses = 0;

// Function to display course and seat availability
void displayCourses() {
    FILE *fp;
    int i, j;
//    int new_line = 0;
    char ch, str[1000];

    fp = fopen("E:\\University_seats.txt","r");
    if(fp==NULL){
        printf("\nThe file could not be opened\n");
        exit(1);
    }
    else{
        printf("Available Courses:\n");
        ch = fgetc(fp);
        for (i = 0; ch != EOF; i++) {
            fflush(stdin);
//            if(ch=='\n'||i==0)
//            {
//                str[i] = new_line;
//                new_line+=1;
//            }
            str[i] = ch;
            ch = fgetc(fp);
        }
        str[i]='\0';
        for(j = 0; j < i; j++){
            printf("%c", str[j]);
        }
    }
    fclose(fp);
    printf("\n");
}

// Function to add a new course
void addCourse() {
    FILE *fp, *fp1;
    int i;
    fp = fopen("E:\\University_seats.txt","a");
    if(fp==NULL) {
        fclose(fp);
        fp1 = fopen("E:\\University_seats.txt", "w");
        printf("Enter course code: ");
        scanf("%s", courses[numCourses].code);
        printf("Enter course title: ");
        scanf(" %[^\n]", courses[numCourses].title);
        printf("Enter number of seats: ");
        scanf("%d", &courses[numCourses].seats);

        fwrite(courses, sizeof(struct Course), 1, fp1);
        fwrite("\n", 1, 2, fp1);
        numCourses++;
        fclose(fp1);
    }
    else{
        printf("Enter course code: ");
        scanf("%s", courses[numCourses].code);
        printf("Enter course title: ");
        scanf(" %[^\n]", courses[numCourses].title);
        printf("Enter number of seats: ");
        scanf("%d", &courses[numCourses].seats);
        fwrite(courses, sizeof(struct Course), 1, fp);
        fwrite("\n", 1, 2, fp);
        numCourses++;
        }
        fclose(fp);
    printf("Course added successfully\n");
}

// Function to delete a course or delete the complete file
void deleteCourse()
{
    int courseIndex;
    char delete_choice;
//    printf("Deletion operations:\n1. Delete a course\n2. Delete all the contents\n3. Delete the file\n")

    printf("Do you wish to delete the entire database?(y/n) ");
    scanf("%c", &delete_choice);

    if(delete_choice == 'y'||delete_choice == 'Y'){
        int rem;
        rem = remove("E:\\University_seats.txt");
        if(rem == 0)
            printf("The file has been deleted successfully\n");
        else
            printf("File not deleted\n");
    }
    else{
        printf("Enter course index to delete: ");
        scanf("%d", &courseIndex);
        // Open the file in read mode
        FILE *fp = fopen("E:\\University_seats.txt", "r");
        if (fp == NULL) {
            printf("The database file does not exist.\n");
            return;
        }

        // Read the existing courses from the file
        struct Course existingCourses[MAX_COURSES];
        int count = 0;
        while (fread(&existingCourses[count], sizeof(struct Course), 1, fp) == 1) {
            count++;
        }
        fclose(fp);

        // Remove the course at the specified index from the array
        for (int i = courseIndex; i < count - 1; i++) {
            strcpy(existingCourses[i].code, existingCourses[i + 1].code);
            strcpy(existingCourses[i].title, existingCourses[i + 1].title);
            existingCourses[i].seats = existingCourses[i + 1].seats;

            // Open the file again in write mode to overwrite its contents
            fp = fopen("E:\\University_seats.txt", "w");

            // Write the modified courses back into the file
            for (int i = 0; i < count - 1; i++) {
                fwrite(&existingCourses[i], sizeof(struct Course), 1, fp);
            }
            fclose(fp);
            printf("Course deleted successfully.\n");

        }
    }
}

// Main function
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
                deleteCourse();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}
