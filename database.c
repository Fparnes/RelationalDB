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

return hash % MAP_SIZE;
}

//Hashes studentID
int hashStudentID (int studentID){
    return (studentID % MAP_SIZE);
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
//printf("helloAFTERMALLOC! \n");
for(int i = 0; i < 100; i++){
//printf("helloINSIDEFOR!\n");
accepted[i] = NULL;
}
int counter = 0;

//printf("helloBEFOREIF!\n");
if(CSGComp(listHead, course, studentID, grade) == 1){
//printf("helloINIF!\n");
 //printf("%s, %d, %s \n", listHead -> course, listHead -> studentID, listHead -> grade);
// listHead -> nextBucket = NULL;
accepted[counter] = listHead;
counter++;
}
//printf("helloAFTERIF!\n");
listHead = listHead -> nextBucket;

//printf("helloBEFOREWHILE!\n");
while(listHead != NULL){

if(CSGComp(listHead, course, studentID, grade) == 1){

//printf("helloWHILEIF!\n");
accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}

//FINDS CSG IN HASHMAP
CSG** CSGInHash(CSG** hashMap, char course [CNS], int studentID, char grade [GNS]){
CSG** accepted = malloc(100 * sizeof(CSG*));
for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}

int acceptedCounter = 0;
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
CSG** listAccept = CSGInList(hashMap[i], course, studentID, grade);

int counter = 0;

while(listAccept[counter] != NULL){
accepted[acceptedCounter] = listAccept[counter];
acceptedCounter++;
counter++;
}

}

}

return accepted;
}

CSG** DeleteCSGInList(CSG** listHead, char course [CNS], int studentID, char grade [GNS]){

CSG* prevBucket = NULL;
printf("helloINEDEL!\n");
if(CSGComp(*listHead, course, studentID, grade) == 1){
printf("helloFIRSTWHILE!\n");
*listHead = (*listHead) -> nextBucket;
}else{
printf("helloINELSE!\n");
prevBucket = *listHead;
*listHead = (*listHead) -> nextBucket;

}
while(*listHead != NULL){
printf("helloINEWHILEDEL!\n");

if(CSGComp(*listHead, course, studentID, grade) == 1){
if(prevBucket != NULL){

prevBucket -> nextBucket = (*listHead) -> nextBucket;
*listHead = (*listHead) -> nextBucket;

}else{

*listHead = (*listHead) -> nextBucket;

}

}else{

 if(prevBucket != NULL){
 prevBucket = prevBucket -> nextBucket;
 }
 else{
 prevBucket = *listHead;
 }

 *listHead = (*listHead) -> nextBucket;
}

}

}

//DELETES CSG IN HASHMAP
void DeleteCSGInHash(CSG** hashMap, char course [CNS], int studentID, char grade [GNS]){
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCSGInList(&hashMap[i], course, studentID, grade);

}

}
}
//inserts
void insertCSG (CSG *tuple, CSG *csgArray[MAP_SIZE]){

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

void insertSNAP(SNAP *tuple, SNAP *snapArray[MAP_SIZE]){
    int specialIndex = hashStudentID(tuple -> studentID);

    if(snapArray[specialIndex] != NULL){
        tuple -> nextBucket = snapArray[specialIndex];
        }

    snapArray[specialIndex] = tuple;
};

void insertCP(CP *tuple, CP *cpArray[MAP_SIZE]){
int specialIndex = hashString(tuple -> course, tuple -> preReq);

if(cpArray[specialIndex] != NULL){
    tuple->nextBucket = cpArray[specialIndex];
    }

    cpArray[specialIndex] = tuple;
};

void insertCDH (CDH *tuple, CDH *cdhArray[MAP_SIZE]) {
int specialIndex = hashString(tuple -> course, tuple -> day);

if(cdhArray[specialIndex] != NULL){
    tuple -> nextBucket = cdhArray[specialIndex];
    }

    cdhArray[specialIndex] = tuple;
};

void insertCR (CR *tuple,CR *crArray[MAP_SIZE]) {
int specialIndex = hashString(tuple -> course, "");

if(crArray[specialIndex] != NULL){
    tuple -> nextBucket = crArray[specialIndex];
    }

    crArray[specialIndex] = tuple;
};

//lookups
CSG** lookupCSG (CSG* csgArray[MAP_SIZE], char course[CNS], int studentID, char grade[GNS]){
  char studentIDString[SINS];

    sprintf(studentIDString, "%d", studentID);


if(strcmp(course, "*") != 0 && studentID != -1){
int specialIndex = hashString(course, studentIDString);

CSG* listHead = csgArray[specialIndex];

return CSGInList(listHead, course, studentID, grade);

}

return CSGInHash(csgArray, course, studentID, grade);

};

SNAP *lookupSNAP(){

};

CP *lookupCP(){

};

CDH *lookupCDH () {

};

CR *lookupCR () {

};

//deletes
void deleteCSG(CSG* csgArray[MAP_SIZE], char course[CNS], int studentID, char grade[GNS]){
char studentIDString[SINS];

    sprintf(studentIDString, "%d", studentID);


if(strcmp(course, "*") != 0 && studentID != -1){
int specialIndex = hashString(course, studentIDString);

CSG* listHead = csgArray[specialIndex];

printf("DELETEINLIST!\n");
 DeleteCSGInList(&listHead, course, studentID, grade);
 return;

}

 DeleteCSGInHash(csgArray, course, studentID, grade);
 return;
};


void deleteSNAP(){

};

void deleteCP(){

};

void deleteCDH () {

};

void deleteCR () {

};


void printCSGResult(CSG** result){
int counter = 0;

 while(result[counter] != NULL){
   printf("%s, %d, %s \n", result[counter] -> course, result[counter] -> studentID, result[counter] -> grade);
   counter++;
   }
}
int main() {
    CSG* csgArray[MAP_SIZE] = {NULL};

    SNAP* snapArray[MAP_SIZE] = {NULL};

    CP* cpArray[MAP_SIZE] = {NULL};

    CDH* cdhArray[MAP_SIZE] = {NULL};

    CR* crArray[MAP_SIZE] = {NULL};

    CSG tuple;

    strcpy(tuple.course,"CS101");
    tuple.studentID = 12345;
    strcpy(tuple.grade,"A");
    tuple.nextBucket = NULL;

 //printf("hello1!");
    insertCSG (&tuple, csgArray);

//printf("hello2!");
   CSG** result = lookupCSG(csgArray, "CS101", 12345, "*");

//printf("hello3!");


  printCSGResult(result);

   CSG** result2 = lookupCSG(csgArray, "*", 12345, "*");

printCSGResult(result2);

 CSG tuple2;

    strcpy(tuple2.course,"CS101");
    tuple2.studentID = 67890;
    strcpy(tuple2.grade,"B");
    tuple2.nextBucket = NULL;

 //printf("hello1!");
    insertCSG (&tuple2, csgArray);

//printf("hello2!");
   result = lookupCSG(csgArray, "CS101", -1, "*");

     printCSGResult(result);

     deleteCSG(csgArray, "CS101", 67890, "*");

      result = lookupCSG(csgArray, "CS101", -1, "*");
 printf("------------------------------------------------");

          printCSGResult(result);

}