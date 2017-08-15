#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define TRUE 1
#define FALSE (!(FALSE))
#define userID_MIN 10000000

typedef int Boolean;
typedef char String[101];


typedef struct{
    int courseNumber;
    int section;
    String name;

} subject;

typedef struct{
    int id;
    String name;
    String courseName;
    Boolean isAdmin;
}user;

int main(){
    FILE *fp;
    Boolean isLoggedIn;
    int loggedInID;

}

