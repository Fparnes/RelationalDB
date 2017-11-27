#include "database.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//concatenate strings
char* concatString (char* string1, char* string2){

char* result = malloc(strlen(string1) + strlen(string2) + 1);

strcpy(result, string1);
strcat(result, string2);

return result;
}

//Hashes a pair of strings by concatenating them and hashing result
unsigned long hashString(char* str1, char* str2){
char* concat = concatString(str1, str2);

unsigned long hash = 5381;
int counter = 0;

while(counter =  *concat++){
hash = ((hash << 5) + hash) + counter;
}

return hash % 1009;
}

//Hashes studentID
int hashStudentID (int studentID){
    return (studentID % 1009);
}

//Compares two CSG's
int CSGComp(CSG* csg1, char course [CNS], int studentID, char grade [GNS]){

if(strcmp(csg1 -> course, course) == 0 || strcmp(course, "*") == 0 ){
if (csg1 -> studentID == studentID || studentID == -1){
if(strcmp(csg1 -> grade, grade) == 0 || strcmp(grade, "*") == 0){
return 1;
}
}
}

return 0;
}

//find CSG in a list
CSG** CSGInList(CSG* listHead, char course [CNS], int studentID, char grade [GNS]){
CSG** accepted = malloc(100 * sizeof(CSG*));
printf("helloAFTERMALLOC! \n");
for(int i = 0; i < 100; i++){
printf("helloINSIDEFOR!\n");
accepted[i] = NULL;
}
int counter = 0;

printf("helloBEFOREIF!\n");
if(CSGComp(listHead, course, studentID, grade) == 1){
printf("helloINIF!\n");
 printf("%s, %d, %s \n", listHead -> course, listHead -> studentID, listHead -> grade);
// listHead -> nextBucket = NULL;
accepted[counter] = listHead;
counter++;
}
printf("helloAFTERIF!\n");
listHead = listHead -> nextBucket;

printf("helloBEFOREWHILE!\n");
while(listHead != NULL){

printf("helloINEWHILE!\n");
if(CSGComp(listHead, course, studentID, grade) == 1){

printf("helloWHILEIF!\n");
accepted[counter] = listHead;
counter++;

printf("helloBEFOREELSE!\n");
}else{

printf("helloINELSE!\n");
 listHead = listHead -> nextBucket;

 }
}
printf("helloBEFORERETURN!\n");
return accepted;
}

//inserts
void insertCSG (CSG *tuple, CSG *csgArray[1009]){

    char studentIDString[SINS];

    sprintf(studentIDString, "%d", tuple -> studentID);
   /// printf("helloINSERT! \n");
    int specialIndex = hashString(tuple -> course, studentIDString);
   // printf("%d \n" , specialIndex );
//printf("helloINSERT22! \n");
    if(csgArray[specialIndex] != NULL){
    //printf("helloIMANIF! \n");
    tuple -> nextBucket = csgArray[specialIndex];
    }

    csgArray[specialIndex] = tuple;

   // printf("helloINSERT333! \n");
};

void insertSNAP(SNAP *tuple, SNAP *snapArray[1009]){
    int specialIndex = hashStudentID(tuple -> studentID);

    if(snapArray[specialIndex] != NULL){
        tuple -> nextBucket = snapArray[specialIndex];
        }

    snapArray[specialIndex] = tuple;
};

void insertCP(CP *tuple, CP *cpArray[1009]){
int specialIndex = hashString(tuple -> course, tuple -> preReq);

if(cpArray[specialIndex] != NULL){
    tuple->nextBucket = cpArray[specialIndex];
    }

    cpArray[specialIndex] = tuple;
};

void insertCDH (CDH *tuple, CDH *cdhArray[1009]) {
int specialIndex = hashString(tuple -> course, tuple -> day);

if(cdhArray[specialIndex] != NULL){
    tuple -> nextBucket = cdhArray[specialIndex];
    }

    cdhArray[specialIndex] = tuple;
};

void insertCR (CR *tuple,CR *crArray[1009]) {
int specialIndex = hashString(tuple -> course, "");

if(crArray[specialIndex] != NULL){
    tuple -> nextBucket = crArray[specialIndex];
    }

    crArray[specialIndex] = tuple;
};

//lookups
CSG** lookupCSG (CSG* csgArray[1009], char course[CNS], int studentID, char grade[GNS]){
  char studentIDString[SINS];

//printf("helloLOOKUP! \n");
    sprintf(studentIDString, "%d", studentID);

//printf("helloLOOKUP2! \n");

    if(strcmp(grade, "*") == 0){
   // printf("helloINSIDEIF! \n");
int specialIndex = hashString(course, studentIDString);

//printf("%d \n", specialIndex);
CSG* listHead = csgArray[specialIndex];

//printf("helloFINAL! \n");
return CSGInList(listHead, course, studentID, grade);

}


};

SNAP *lookupSNAP(){

};

CP *lookupCP(){

};

CDH *lookupCDH () {

};

CR *lookupCR () {

};



int main() {
    CSG* csgArray[1009] = {NULL};

    SNAP* snapArray[1009] = {NULL};

    CP* cpArray[1009] = {NULL};

    CDH* cdhArray[1009] = {NULL};

    CR* crArray[1009] = {NULL};

    CSG tuple;

    strcpy(tuple.course,"CS101");
    tuple.studentID = 12345;
    strcpy(tuple.grade,"A");
    tuple.nextBucket = NULL;

 printf("hello1!");
    insertCSG (&tuple, csgArray);

printf("hello2!");
   CSG** result = lookupCSG(csgArray, "CS101", 12345, "*");

printf("hello3!");
   int counter = 0;

   while(result[counter] != NULL){
   printf("%s, %d, %s \n", result[counter] -> course, result[counter] -> studentID, result[counter] -> grade);
   counter++;
   }

}