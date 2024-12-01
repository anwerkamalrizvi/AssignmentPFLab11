/*Q2. Employee Salary Record (Binary File):
• Write a program to store employee salary records (name, ID, salary) in a binary file.
• Implement functionality to read the records from the file and calculate the total salary expense
of the company.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char name[50];
    int id;
    double salary;
} Employee;

void addEmployee(const char *filename) 
{
    FILE *file = fopen(filename, "ab"); 
    if (file == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    Employee emp;

    printf("Enter employee name: ");
    scanf(" %[^\n]", emp.name);

    printf("Enter employee ID: ");

    scanf("%d", &emp.id);

    printf("Enter employee salary: ");
    scanf("%lf", &emp.salary);
    fwrite(&emp, sizeof(Employee),1,  file);
    fclose(file);

    printf("Employeer record aded successfully.\n");
}

void displayEmployeesAndCalculateTotal(const char *filename) 
{
    FILE *file = fopen(filename, "rb"); 
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Employee emp;
    double totalSalary = 0.0;

    printf("\nEmployee Record:\n");
    printf("%-20s %-10s %-10s\n", "Name", "ID", "Salary");
    while (fread(&emp, sizeof(Employee), 1, file))
     
    {
        printf("%-20s %-10d %-10.2lf\n",emp.name,emp.id,emp.salary);
        totalSalary += emp.salary;
    }
    printf("Salary Total: %.2lf\n",totalSalary);

    fclose(file);
}

int main(){
    const char *filename = "employee_records.bin";
    int choice;

    do {
        printf("\nEmployee Salary Record Menu:\n");
        printf("1. Add any Employee Record\n");
        printf("2. Display Records | Calculate Total Salary\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(filename);
                break;
            case 2:
                displayEmployeesAndCalculateTotal(filename);
                break;
            case 3:
                printf("Bye Bye\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice!=3);

    return 0;
}
