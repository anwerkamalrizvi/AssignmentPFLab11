/*Define a structure for an employee with fields such as name, employee ID, and salary.
Create a nested structure for a department that contains multiple employees.
Write a program that calculates the total salary of all employees in a specific department.*/
#include <stdio.h>
#include <string.h>
#define n 20
typedef struct employee{
    char name[n];
    int employee_id;
    float salary;
}Emp;
typedef struct department{
    char department[n];
    int no_of_emp;
    Emp emp[n];
}Dept_Name;

float salary(Dept_Name Dep){
    float total_salary = 0;
    for (int i = 0; i < Dep.no_of_emp; i++)
    {
        total_salary= total_salary + Dep.emp[i].salary;
    }
    printf("\nTotal salary for department %s and their employees is %.2f  ", Dep.department,total_salary);
    
}//end salary
int main() {
    Dept_Name Dep;
    char str[30] = "Artificial Intelligence";       //This is department
    strcpy(Dep.department,str);                     //Copy department name through  strcpy
    Dep.no_of_emp = 4;                              //total employees capacity

    strcpy(Dep.emp[0].name, "Khalid");              //Name of the employee
    Dep.emp[0].employee_id = 1;
    Dep.emp[0].salary = 305000;

    strcpy(Dep.emp[1].name, "Anwer");
    Dep.emp[1].employee_id = 2;
    Dep.emp[1].salary = 550040;

    strcpy(Dep.emp[2].name, "Omer");
    Dep.emp[2].employee_id = 3;
    Dep.emp[2].salary = 1000;

    strcpy(Dep.emp[3].name, "Salman");
    Dep.emp[3].employee_id = 4;
    Dep.emp[3].salary = 69000;

    for (int i = 0; i < Dep.no_of_emp; i++)
    {
        printf("\nEmployee: %s ", Dep.emp[i].name);
        printf("\nIb: %d ", Dep.emp[i].employee_id);
        printf("\nSalary: %.2f ", Dep.emp[i].salary);
    }
    salary(Dep);


    return 0;
}