#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define userID_MIN 10000000

typedef int Boolean;
typedef char String[101];


typedef struct subject{
    int courseNumber, maxSize;
    String name;
    struct subject *pNext;
} subject;

typedef struct user{
    String username, password, firstName, lastName, courseName;
    int id;
    Boolean isAdmin;
    int EnrolledCourses[30];
}user;

user loggedInUser;


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
int main(){
    FILE *fp;
    Boolean isLoggedIn = FALSE;
    int choice=-1;
    String user, pass, tempUser, tempPass,tempFirst, tempLast, tempCrs;
    int tempId, tempisAdmin;
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

                        while(fscanf(fp, "%s %s %d %s %s %s %d", tempUser, tempPass, &tempId, tempFirst, tempLast, tempCrs, &tempisAdmin) == 7)
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
                            }
                        }
                        if(!found)
                            printf("User does not exist.\n");
                        else
                            isLoggedIn = TRUE;
                        break;

                case 2: signup(); break;
                case 3: break;//logout
            }
        }
        else if(isLoggedIn){
            choice = -1;
            loggedIn();
            scanf("%d", &choice);
        }
    }while(1);

    fclose(fp);
}




