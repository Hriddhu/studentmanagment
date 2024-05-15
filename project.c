#include <stdio.h>
#include <string.h>

struct student {
    char name[50];
    char address[50];
    int roll;
    int class;
    float percent;
};

void addstu();
void searchstu();
void updatestu();

int main() {
    int num;

    printf("\t\t\t\t\t\t ---STUDENT RECORDER---\n");
    printf("\t HI, I CAN DO THE FOLLOWING TASKS: PLEASE SELECT ONE\n");
    printf("\t1. Add student\n\t2. Search student\n\t3. Update student\n\t4. Exit\n");
    printf("\tEnter task number: ");

    scanf("%d", &num);

    switch (num) {
        case 1:
            addstu();
            break;
        case 2:
            searchstu();
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        case 3:
            updatestu();
            break;
        default:
            printf("Invalid choice. Exiting the program.\n");
            break;
    }

    return 0;
}

void addstu() {
    char decision;
    struct student info;
    FILE *fp = fopen("student.txt", "a");

    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    do {
        while (getchar() != '\n');

        printf("\nEnter name of student: ");
        fgets(info.name, sizeof(info.name), stdin);
        info.name[strcspn(info.name, "\n")] = '\0';

        printf("Enter student roll number: ");
        scanf("%d", &info.roll);

        while (getchar() != '\n');

        printf("Enter address of student: ");
        fgets(info.address, sizeof(info.address), stdin);
        info.address[strcspn(info.address, "\n")] = '\0';

        printf("Enter student class: ");
        scanf("%d", &info.class);

        printf("Enter student percentage: ");
        scanf("%f", &info.percent);

        while (getchar() != '\n');

        fprintf(fp, "Name: %s\nRoll: %d\nAddress: %s\nClass: %d\nPercentage: %.2f\n\n",
                info.name, info.roll, info.address, info.class, info.percent);

        printf("\nRecord stored successfully\n");
        printf("Do you want to add another record? (y/n): ");
        scanf(" %c", &decision);

    } while (decision == 'y' || decision == 'Y');

    fclose(fp);
}

void searchstu() {
    char name[50];
    int class, roll, found = 0;

    printf("Whom do you want to search?\n");
    while (getchar() != '\n');

    printf("Enter name of student: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter class: ");
    scanf("%d", &class);

    printf("Enter roll number: ");
    scanf("%d", &roll);

    struct student current;
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(fp, "Name: %49s\nRoll: %d\nAddress: %49s\nClass: %d\nPercentage: %f\n\n",
                  current.name, &current.roll, current.address, &current.class, &current.percent) == 5) {
        // only for debugging
        printf("Read from file: %s, %d, %s, %d, %.2f\n", current.name, current.roll, current.address, current.class, current.percent);
        
        if (strcmp(name, current.name) == 0 && class == current.class && roll == current.roll) {
            printf("Student Found!!\n");
            printf("Name: %s\nRoll: %d\nAddress: %s\nClass: %d\nPercentage: %.2f\n",
                   current.name, current.roll, current.address, current.class, current.percent);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("The student is not in the records\n");

    fclose(fp);
}


void updatestu() {
    char name[50];
    int class, roll, found = 0;

    printf("----UPDATE EXISTING STUDENT RECORDS----\n");
    while (getchar() != '\n');

    printf("Enter name of student: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter class: ");
    scanf("%d", &class);

    printf("Enter roll number: ");
    scanf("%d", &roll);

    struct student current;
    FILE *fp = fopen("student.txt", "r+");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(fp, "Name: %49s\nRoll: %d\nAddress: %49s\nClass: %d\nPercentage: %f\n\n",
                  current.name, &current.roll, current.address, &current.class, &current.percent) == 5) {
        if (strcmp(name, current.name) == 0 && class == current.class && roll == current.roll) {
            printf("The student record is as follows:\n");
            printf("Name: %s\nRoll: %d\nAddress: %s\nClass: %d\nPercentage: %.2f\n",
                   current.name, current.roll, current.address, current.class, current.percent);
            printf("What do you want to update?\n");
            printf("1. Name\n");
            printf("2. Roll\n");
            printf("3. Address\n");
            printf("4. Class\n");
            printf("5. Percentage\n");

            int choice;
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("Enter the new name: ");
                    while (getchar() != '\n');
                    fgets(current.name, sizeof(current.name), stdin);
                    current.name[strcspn(current.name, "\n")] = '\0';
                    break;
                case 2:
                    printf("Enter the new roll number: ");
                    scanf("%d", &current.roll);
                    break;
                case 3:
                    printf("Enter the new address: ");
                    while (getchar() != '\n');
                    fgets(current.address, sizeof(current.address), stdin);
                    current.address[strcspn(current.address, "\n")] = '\0';
                    break;
                case 4:
                    printf("Enter the new class: ");
                    scanf("%d", &current.class);
                    break;
                case 5:
                    printf("Enter the new percentage: ");
                    scanf("%f", &current.percent);
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }

            
            fseek(fp, -strlen(current.name) - 64, SEEK_CUR);

            fprintf(fp, "Name: %s\nRoll: %d\nAddress: %s\nClass: %d\nPercentage: %.2f\n\n",
                    current.name, current.roll, current.address, current.class, current.percent);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("The student is not in the records\n");
}

// changes made by prastut nepal !!! 