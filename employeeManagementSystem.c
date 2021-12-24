#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

/// set the cursor to the top-left corner of window
COORD coord = {0,0};

///This function changes the cursors cordinates
void movexy(int x,int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main() {

    FILE *fp, *ft; ///file pointers for file handling
    char respond, choice;

    /** structure that represent a employee */
    struct emp {
        char name[40]; //name of employee
        int age;       // age of employee
        float bs;      // salary of employee
    };

    struct emp employee; /// structure variable creation
    long int recsize; /// size of each record of employee
    char empName[40]; /// string to store the name of employee

    /** open the file
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMPLOYEE.DAT","rb+");
    if(fp == NULL) {
        fp = fopen("EMPLOYEE.DAT","wb+");
        if(fp == NULL) {
            printf("Connot open file. There is an error......");
            exit(1);
        }
    }

    recsize = sizeof(employee); /// sizeo of each record i.e. size of structure variable e

    /*infinite loop to re iterate the main menu*/
    while (2) {

        system("cls");
        printf("EMPLOYEE MANAGEMENT SYSTEM (SCT GROUP NO.3)");
        movexy(30,4); /// move the cursor to postion 30, 10 from top-left corner
        printf("1. Add a new Employee"); /// option for add record
        movexy(30,6);
        printf("2. List Employees"); /// option for showing existing record
        movexy(30,8);
        printf("3. Modify Employee Details"); /// option for editing record
        movexy(30,10);
        printf("4. Delete Employees"); /// option for deleting record
        movexy(30,12);
        printf("5. Exit"); /// exit from the program
        movexy(30,14);
        printf("**To do a task enter the relavent number**");
        movexy(30,18);
        printf("Give the number: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard

        switch (choice) {
        case '1':  /// if user press 1
            system("cls");
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file
            printf("\nEMPLOYEE MANAGEMENT SYSTEM \n\n");
            respond = 'y';
            while (respond == 'y') { /// if user want to add another record
                
                printf("\n\nEnter employee details...........\n");
                printf("\nEnter name: ");
                scanf("%s",employee.name);
                printf("\nEnter age: ");
                scanf("%d", &employee.age);
                printf("\nEnter basic salary: ");
                scanf("%f", &employee.bs);

                fwrite(&employee,recsize,1,fp); /// write the record in the file

                printf("\nAdd another record(y/n) ");
                fflush(stdin);
                respond = getche();
            }
            break;
        case '2':
            system("cls");
            printf("Employee list\n==============\n");
            rewind(fp);     ///this moves file cursor to start of the file
            while (fread(&employee,recsize,1,fp)==1) {   /// read the file and fetch the record one record per fetch
                printf("\n%s %d %.2f",employee.name,employee.age,employee.bs);   /// print the name, age and basic salary
            }
            printf("\n\nPress anny key to go back to the previous menu");
            getch();
            break;

        case '3':   /// if user press 3 then do editing existing record
            system("cls");
            respond = 'y';

            while (respond == 'y') {

                printf("EMPLOYEE MANAGEMENT SYSTEM\n\n");
                printf("Enter the employee name to modify: ");
                scanf("%s", empName);
                rewind(fp);

                while (fread(&employee,recsize,1,fp)==1) {    /// fetch all record from file

                    if (strcmp(employee.name,empName) == 0) {     ///if entered name matches with that in file
                        printf("\nEnter new name,age and salary respectively: ");
                        scanf("%s%d%f",employee.name,&employee.age,&employee.bs);
                        fseek(fp,-recsize,SEEK_CUR);    /// move the cursor 1 step back from current position
                        fwrite(&employee,recsize,1,fp);     /// override the record
                        break;
                    }
                }
                printf("\nModify another record(y/n)");
                fflush(stdin);
                respond = getche();
            }
            break;
        case '4':
            system("cls");
            respond = 'y';

            while (respond == 'y') {

                printf("\nEnter name of employee to delete: ");
                scanf("%s",empName);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file

                while (fread(&employee,recsize,1,fp) == 1) {  /// read all records from file

                    if (strcmp(employee.name,empName) != 0) {  /// if the entered record match
                        fwrite(&employee,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }

                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n)");
                fflush(stdin);
                respond = getche();
            }
            break;
        case '5':
            fclose(fp);  /// close the file
            printf("\nPROGRAMME ENDED UP");
            exit(0); /// exit from the program
        }
    }
    return 0;
}
