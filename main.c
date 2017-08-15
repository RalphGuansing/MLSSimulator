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

void showLoggedInCourses(){
    int i, j;
    Boolean found = FALSE;
    for(i=0; i<loggedInUser.enrolledCtr; i++){
        for(j=0; j<subjCtr; j++){
            if(loggedInUser.EnrolledCourses[i] == allSubjects[j].courseNumber)
            {
                found = TRUE;
                printf("%d %d %s %d\n", allSubjects[j].courseNumber, allSubjects[j].maxSize, allSubjects[j].name, allSubjects[j].studentsEnrolled);
                continue;
            }
        }

    }
    if(!found){
        printf("No enrolled subjects\n");
    }

}

void getMyCourses(){
    int i, ctr=0, tempID, tempCrsNum;

    FILE *fp;
    fp = fopen("users'courses.txt", "r");

    while(fscanf(fp, "%d %d", &tempID, &tempCrsNum)==2){
        if(tempID == loggedInUser.id)
        {
            loggedInUser.EnrolledCourses[loggedInUser.enrolledCtr] = tempCrsNum;
            loggedInUser.enrolledCtr++;
        }
    }


}

void dropCourse(int num){
    int i;
    for(i=0;i<loggedInUser.enrolledCtr; i++){
        if(num == loggedInUser.EnrolledCourses[i]){
            loggedInUser.EnrolledCourses[i] = 0; break;
        }
    }

    for(i=0; i<subjCtr; i++){
        if(num == allSubjects[i].courseNumber)
        {
            allSubjects[i].studentsEnrolled--;
            printf("%s dropped!\n",allSubjects[i].name); break;
        }
    }
}

void showProfile(){
    printf("You are %s %s\n", loggedInUser.firstName, loggedInUser.lastName);
    printf("Your ID Number is %d\n", loggedInUser.id);
    printf("You are taking up %s\n", loggedInUser.courseName);
    printf("Your username is \n", loggedInUser.username);
    printf("Your password is \n", loggedInUser.password);
    printf("This term, you are taking: \n");
    showLoggedInCourses();
}

void saveMLS(){
    FILE *temp;
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
                                strcpy(loggedInUser.password, tempPass);
                                loggedInUser.id = tempId;
                                strcpy(loggedInUser.firstName, tempFirst);
                                strcpy(loggedInUser.lastName, tempLast);
                                loggedInUser.isAdmin = tempisAdmin;
                                loggedInUser.enrolledCtr = 0;
                                getMyCourses();
                                break;
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
                case 1: showCourses();break;

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
                                break;
                            }
                        }
                        if(!flag){
                            printf("No subject with that course number has been found.\n\n");
                        }

                        break;
                case 3: printf("Your classes are: \n");
                        showLoggedInCourses();
                        printf("Input Course Number to drop: ");
                        scanf("%d", &tempCrs);
                        dropCourse(tempCrs);

                        break;
                case 4: showLoggedInCourses(); break;
                case 5: showProfile(); break;
                case 6: saveMLS(); break;
            }
        }
    }while(1);

    fclose(fp);
}




