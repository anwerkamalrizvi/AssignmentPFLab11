/*Q3. Design a Student Course Enrollment System where:
• A Course structure contains the course name, code, and instructor.
• A Student structure contains name, roll number, and an array of courses enrolled in.
• The system should:
o Store student and course enrollment data in a file (binary or text).
o Display the courses enrolled by a student.
o Save a student's enrollment data and generate a report on the total number of students
enrolled in each course.
o Allow for modification of course enrollment and update the file accordingly.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char course_name[50], course_code[20],instructor[50];
} Course;

typedef struct
{
    char student_name[50];
    int roll_number, num_courses;
    Course courses[5];
   
} Student;

void addCourseToStudent(Student *student)
{
    if (student->num_courses >= 5)
    {
        printf("Too many courses enrolled. \n");
        return;
    }

    printf("Course Name : ");
    scanf(" %[^\n]s", student->courses[student->num_courses].course_name);
    printf("Course Code: ");
    scanf(" %s", student->courses[student->num_courses].course_code);
    printf("Instructor Name:");
    scanf(" %[^\n]s", student->courses[student->num_courses].instructor);

    student->num_courses++;
}

void saveStudentData(const char *filename, Student *student, int num_students)

{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("file open error\n");
        return;
    }

      fwrite(&num_students, sizeof(int), 1, file); 
    fwrite(student, sizeof(Student), num_students, file); 
    fclose(file);
}
void loadStudentData(const char *filename, Student *students, int *num_students)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("No previous data found.\n");
        return;
    }

    fread(num_students, sizeof(int), 1, file); 
    fread(students, sizeof(Student), *num_students, file);
    fclose(file);
}

void displayStudentCourses(Student *students, int num_students, int roll_number)
{
    for (int i = 0; i < num_students; i++)
    {
        if (students[i].roll_number == roll_number)
        {
            printf("Courses for %s:\n", students[i].student_name);
            for (int j = 0; j < students[i].num_courses; j++)
            {
                printf("%d. %s (%s) by %s\n", j + 1,

                       students[i].courses[j].course_name,
                       students[i].courses[j].course_code,
                       students[i].courses[j].instructor);
            }
            return;
        }
    }
    printf("No student found with roll number %d.\n", roll_number);
}

void generateReport(Student *students, int num_students)
{
    Course course_count[100];
    int course_frequency[100] = {0};
    int total_courses = 0;

    for (int i = 0; i < num_students; i++)
    {
        for (int j = 0; j < students[i].num_courses; j++)
        {
            int found = 0;
            for (int k = 0; k < total_courses; k++)
            {
                if (strcmp(course_count[k].course_code, students[i].courses[j].course_code) == 0)
                {
                    course_frequency[k]++;
                    found = 1;
                    break;
                }
            }
            if (!found)
            {
            course_count[total_courses] = students[i].courses[j];
                course_frequency[total_courses]++;

                total_courses++;


            }
        }
    }

    printf("Course Enrollment Report:\n");
    for (int i = 0; i < total_courses; i++)
    {
        printf("%s (%s) - %d students\n", course_count[i].course_name,
               course_count[i].course_code, course_frequency[i]);
    }


}

int main()
{
    const char *filename = "student_data.bin";
    Student students[100];
    int num_students = 0, choice;
loadStudentData(filename, students, &num_students);

    while (1)
    {
        printf("Student Enrollment Menu\n"
               "1. Add Student\n"
               "2. Enroll Student in Course\n"
               "3. Display Student Courses\n"
               "4. Generate Report\n"
               "5. Exit\n"
               "Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Student Name : ");
            scanf(" %[^\n]s", students[num_students].student_name);
            printf("Roll Number: ");
            scanf("%d", &students[num_students].roll_number);

            students[num_students].num_courses = 0;
            num_students++;

        }
        else if (choice == 2)
        {
            int roll_number;
            printf("Enter Roll Number:");
            scanf("%d", &roll_number);
            for (int i = 0; i < num_students; i++)
            {
                if (students[i].roll_number == roll_number)
                {
                addCourseToStudent(&students[i]);
                break;

                }// if


            }//for 
        }//else if 
        else if (choice == 3)
        {
         int roll_number;
            printf("Enter Roll Number:");
        scanf("%d", &roll_number);

            displayStudentCourses(students, num_students, roll_number);


        }
        else if (choice == 4)
        {
            generateReport(students, num_students);
        }
        else if (choice == 5)
        {
         saveStudentData(filename, students, num_students);
            printf("Data saved. Exiting.\n");
            break;

        }
        else
        {
        printf("Invalid choice.\n");
        }
    }

    return 0;
}
