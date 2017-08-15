#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define userID_MIN 10000000

typedef int Boolean;
typedef char String[101];

int subjCtr, userCtr;

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
user allUsers[1000];

void banner(){

    printf("Welcome to My LaSalle!\n");

}

void signup(){
    FILE *fp;
    String tempFirst, tempLast, tempCourse, tempUser, tempPass;
    int tempID;

        printf("Enter ID Number: ");
        scanf("%d", &tempID);
        printf("Enter your First Name: ");
        scanf("%s", tempFirst);
        printf("Enter your Last Name: ");
        scanf("%s", tempLast);
        printf("Enter your Degree Program: ");
        scanf("%s", tempCourse);
        printf("Enter desired username: ");
        scanf("%s", tempUser);
        printf("Enter desired password: ");
        scanf("%s", tempPass);

        fp = fopen("users.txt", "a");
        fprintf(fp, "\n%s %s %d %s %s %s 0 0", tempUser, tempPass, tempID, tempFirst, tempLast, tempCourse);
        fclose(fp);
}

void home(){
    printf("What would you like to do?\n");
    printf("[1] Login\n");
    printf("[2] Signup\n");
    printf("[3] Exit MyLaSalle\n");
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
    printf("[6] Log Out\n");
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
    int i=0, ctr=0, tempID, tempCrsNum;

    FILE *fp;
    fp = fopen("users'courses.txt", "r");

    while(fscanf(fp, "%d %d", &tempID, &tempCrsNum)==2){
        if(tempID == loggedInUser.id)
        {
            loggedInUser.EnrolledCourses[loggedInUser.enrolledCtr] = tempCrsNum;
            loggedInUser.enrolledCtr++;
        }
          fclose(fp);
    }


    fp = fopen("users'courses.txt", "r");
    for(i=0; i<userCtr; i++)
    {
        fp = fopen("users'courses.txt", "r");
        while(fscanf(fp, "%d %d", &tempID, &tempCrsNum)==2){
            if(allUsers[i].id == tempID)
            {
                allUsers[i].EnrolledCourses[allUsers[i].enrolledCtr] = tempCrsNum;
                allUsers[i].enrolledCtr++;
            }
        }
        fclose(fp);
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
    FILE *fp_mycourse, *fp_course, *fp_user;
    int i;
    struct user tempUSERS[1000];
    fp_course = fopen("subjects.txt", "w");
    fp_course = fopen("tempusers'courses.txt", "w");
    for(i=0;i<subjCtr;i++){
        fprintf(fp_course, "%d %d %s %d\n", allSubjects[i].courseNumber, allSubjects[i].maxSize, allSubjects[i].name, allSubjects[i].studentsEnrolled);
    }

    fclose(fp_course);


   // fclose(fp_mycourse);
  //  fclose(fp_user);

}

void showAdminMenu(){
    printf("Welcome Admin %s %s!\n", loggedInUser.firstName, loggedInUser.lastName);
    printf("[1] View all classes\n");
    printf("[2] Add classes\n");
    printf("[3] Remove Classes\n");
    printf("[4] View class list\n");
    printf("[5] Set class size limit\n");
    printf("[6] View profile of students\n");
    printf("Choice: ");
}

void addClasses(){
    String tempName;
    int tempMax;
    printf("Input class name: ");
    scanf("%s", tempName);
    printf("Input Max Number of students: ");
    scanf("%d", &tempMax);

    allSubjects[subjCtr].courseNumber = allSubjects[subjCtr-1].courseNumber+1;
    allSubjects[subjCtr].maxSize = tempMax;
    allSubjects[subjCtr].studentsEnrolled = 0;
    strcpy(allSubjects[subjCtr].name, tempName);
    subjCtr++;

    printf("Added class: %s!\n\n", tempName);
}

void removeClasses(){

    subject tempSubj[1000];
    int num, i=0, t=0;
    printf("Input course number to be removed from the courses list: ");
    scanf("%d", &num);
    printf("%s", allSubjects[i].name);
    for(i=0; i<subjCtr; i++){
        if(num == allSubjects[i].courseNumber)
        {
            printf("%s removed from courses!\n",allSubjects[i].name);
        }
        else{
            tempSubj[t].courseNumber = allSubjects[i].courseNumber;
            tempSubj[t].maxSize = allSubjects[i].maxSize;
            tempSubj[t].studentsEnrolled = allSubjects[i].studentsEnrolled;
            strcpy(tempSubj[t].name, allSubjects[i].name);
            t++;

        }
    }

    for(i=0; i<subjCtr-1; i++){
        allSubjects[i].courseNumber = tempSubj[i].courseNumber;
        allSubjects[i].maxSize = tempSubj[i].maxSize ;
        allSubjects[i].studentsEnrolled = tempSubj[i].studentsEnrolled;
        strcpy(allSubjects[i].name, tempSubj[i].name);
    }

    subjCtr--;

}

void showAllProfiles(){
    int i;
    printf("******List of all profiles******\n");
    for(i=0; i<userCtr; i++){
       printf("%d %s %s\n", allUsers[i].id, allUsers[i].firstName, allUsers[i].lastName);
    }
}

void setClassSize(){
    int tempMax, tempNum,x;
    showCourses();
    printf("Input class number of size you want to modify: ");
    scanf("%d", &tempNum);
    printf("Input modified max number of students in the said class: ");
    scanf("%d", &tempMax);

    int i;
    for(i=0; i<subjCtr; i++){
        if(allSubjects[i].courseNumber == tempNum){
            x = allSubjects[i].maxSize;
            allSubjects[i].maxSize = tempMax;
            break;
        }
    }

    printf("Max Size of %s has been changed from %d to %d\n", allSubjects[i].name, x, allSubjects[i].maxSize);



}

void viewProfile(){
    int i, tempID;
    showAllProfiles();
    printf("Input ID Number of Profile you want to view: ");
    scanf("%d", &tempID);
        for(i=0; i<userCtr; i++)
        {
            if(allUsers[i].id == tempID && !allUsers[i].isAdmin)
            {
                printf("ID Number: %d\n", allUsers[i].id);
                printf("First Name: %s\n", allUsers[i].firstName);
                printf("Last Name: %s\n", allUsers[i].lastName);
                printf("Degree Program: %s\n", allUsers[i].courseName);
                printf("Username: %s\nPassword: %s\n\n\n", allUsers[i].username, allUsers[i].password);
                break;
            }
        }
}

void viewClassList(){
    int i, j, k, tempNum;
    subject tempSubject;
    showCourses();
    printf("Input class number of class to look at its class list: ");
    scanf("%d", &tempNum);
    for(i=0; i<subjCtr; i++){
        if(tempNum == allSubjects[i].courseNumber)
            tempSubject = allSubjects[i];
    }
    printf("Class list for %s\n", tempSubject.name);
    for(i=0; i<userCtr; i++){
        for(j=0; j<allUsers[i].enrolledCtr; j++)
        {
            if(allUsers[i].EnrolledCourses[j] == tempSubject.courseNumber){
                printf("%d %s %s\n", allUsers[i].id, allUsers[i].firstName, allUsers[i].lastName);
                break;
            }
        }

    }
}
int main(){
    subjCtr = 0, userCtr = 0;
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
                            }

                            strcpy(allUsers[userCtr].courseName, tempCrs);
                            strcpy(allUsers[userCtr].username, tempUser);
                            strcpy(allUsers[userCtr].password, tempPass);
                            strcpy(allUsers[userCtr].firstName, tempFirst);
                            strcpy(allUsers[userCtr].lastName, tempLast);
                            allUsers[userCtr].isAdmin = tempisAdmin;
                            allUsers[userCtr].id = tempId;
                            allUsers[userCtr].enrolledCtr = 0;
                            userCtr++;
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

                            fclose(fp);
                            fp = fopen("users.txt", "r");
                            printf("\n");
                            isLoggedIn = TRUE;
                            fclose(fp);
                        }
                        getMyCourses();
                        break;

                case 2: signup(); break;
                case 3: printf("Thank You for using My LaSalle!");
                    exit(0); break;
            }
        }
        else if(isLoggedIn && loggedInUser.isAdmin == FALSE){
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
                case 6: saveMLS(); break; //signout
            }
        }

        else if(isLoggedIn && loggedInUser.isAdmin == TRUE)
        {
            choice=-1;
            showAdminMenu();
            scanf("%d", &choice);
            switch(choice){
                case 1: showCourses(); break;
                case 2: addClasses(); break;
                case 3: showCourses(); removeClasses(); break;
                case 4: viewClassList(); break;
                case 5: setClassSize(); break;
                case 6: viewProfile(); break;
            }

        }
    }while(1);


    fclose(fp);
}




