#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define userID_MIN 10000000

typedef int Boolean;
typedef char String[101];

int subjCtr;

typedef struct subject{
    int courseNumber, maxSize, studentsEnrolled;
    String name;
} subject;

typedef struct user{
    String username, password, firstName, lastName, courseName;
    int id;
    Boolean isAdmin;
    int EnrolledCourses[30];
    int enrolledCtr;
}user;

user loggedInUser;
subject allSubjects[1000];

void banner(){

    printf("Welcome to My LaSalle!\n");

}

void signup(){
}

void home(){
    printf("What would you like to do?\n");
    printf("[1] Login\n");
    printf("[2] Signup\n");
    printf("Choice: ");
}

void loggedIn(){
    printf("Hello %s %s!\n", loggedInUser.firstName, loggedInUser.lastName);
    printf("What would you like to do?\n");
    printf("[1] View available classes\n");
    printf("[2] Enroll classes\n");
    printf("[3] Drop classes\n");
    printf("[4] View my classes\n");
    printf("[5] View my profile\n");
    printf("Choice: ");
}

void showCourses(){
    int i;
    printf("Per column:\n[Course Number] [Max Students] [Name] [Students Enrolled]\n");
    for(i=0; i<subjCtr; i++)
    {
        printf("%d %d %s %d\n", allSubjects[i].courseNumber, allSubjects[i].maxSize, allSubjects[i].name, allSubjects[i].studentsEnrolled);
    }
}
int main(){
    subjCtr = 0;
    FILE *fp;
    Boolean isLoggedIn = FALSE;
    int choice=-1;
    int i;
    String user, pass, tempUser, tempPass,tempFirst, tempLast, tempCrs;
    int tempId, tempisAdmin, tempCrsCtr;
    Boolean found = FALSE;
    fp = fopen("users.txt", "r");

    do{
        if(!found)
        {
            choice = -1;
            banner();
            home();
            scanf("%d", &choice);
            switch(choice)
            {
                case 1:
                        printf("Username: ");
                        scanf("%s", &user);
                        printf("Password: ");
                        scanf("%s", &pass);


                        if (fp == NULL)
                            printf("File does not exist");

                        while(fscanf(fp, "%s %s %d %s %s %s %d %d", tempUser, tempPass, &tempId, tempFirst, tempLast, tempCrs, &tempisAdmin, &tempCrsCtr) == 8)
                        {
                            if(strcmp(user, tempUser) == 0 && strcmp(pass, tempPass) == 0)
                            {
                                found = TRUE;
                                printf("Welcome to My LaSalle! %s!\n", tempUser);
                                strcpy(loggedInUser.courseName, tempCrs);
                                strcpy(loggedInUser.username, tempUser);
                                loggedInUser.id = tempId;
                                strcpy(loggedInUser.firstName, tempFirst);
                                strcpy(loggedInUser.lastName, tempLast);
                                loggedInUser.isAdmin = tempisAdmin;
                                loggedInUser.enrolledCtr = tempCrsCtr;
                            }
                        }
                        if(!found)
                            printf("User does not exist.\n");
                        else{
                            i=0;
                            fp = fopen("subjects.txt", "r");
                            printf("Loading");
                            while(fscanf(fp, "%d%d%s%d", &allSubjects[i].courseNumber, &allSubjects[i].maxSize, allSubjects[i].name, &allSubjects[i].studentsEnrolled) == 4)
                            {
                                if(i%10 == 0)
                                    printf(".");
                                i++;
                                subjCtr++;
                            }
                            printf("\n");
                            isLoggedIn = TRUE;
                        }
                        break;

                case 2: signup(); break;
                case 3: break;//logout
            }
        }
        else if(isLoggedIn){
            choice = -1;
            loggedIn();
            scanf("%d", &choice);
            int tempCrs;
            switch(choice)
            {
                case 1: showCourses(); break;

                case 2: showCourses();
                        Boolean flag = FALSE;
                        printf("Input Course Number to enroll: ");
                        scanf("%d", &tempCrs);
                        for(i=0; i<subjCtr; i++)
                        {
                            if(tempCrs == allSubjects[i].courseNumber)
                            {
                                printf("Enrolled %s!\n\n", allSubjects[i].name);
                                flag = TRUE;
                                loggedInUser.EnrolledCourses[loggedInUser.enrolledCtr] = tempCrs;
                                loggedInUser.enrolledCtr++;
                                allSubjects[i].studentsEnrolled++;
                            }
                        }
                        if(!flag){
                            printf("No subject with that course number has been found.\n\n");
                        }
                        break;
            }
        }
    }while(1);

    fclose(fp);
}




