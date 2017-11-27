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


///////////////////////////////////////////////SNAP//////////////////////////////////////////////////
int SNAPComp(SNAP* csg1, char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){

if(strcmp(csg1 -> address, address) == 0 || strcmp(address, "*") == 0 ){
if (csg1 -> studentID == studentID || studentID == -1){
if(strcmp(csg1 -> name, name) == 0 || strcmp(name, "*") == 0){
if(strcmp(csg1 -> phoneNum, phoneNum) == 0 || strcmp(phoneNum, "*") == 0){
//printf("HERE \n");
return 1;
}
}
}
}

return 0;
}

SNAP** SNAPInList(SNAP* listHead,char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){
SNAP** accepted = malloc(100 * sizeof(SNAP*));

for(int i = 0; i < 100; i++){

accepted[i] = NULL;
}
int counter = 0;

//printf("------------------------------------------------------------------- \n");
////if(listHead != NULL){
////  printf("%s, %d, %s, %s \n", listHead -> name, listHead -> studentID, listHead -> address, listHead -> phoneNum);
////}
//
////if(listHead != NULL){
//////  printf("%s, %d, %s, %s \n", name, studentID, address, phoneNum);
////}
//printf("------------------------------------------------------------------- \n");

if(SNAPComp(listHead, address, studentID, name, phoneNum) == 1){

accepted[counter] = listHead;
counter++;
}
listHead = listHead -> nextBucket;

while(listHead != NULL){

if(SNAPComp(listHead,address, studentID, name, phoneNum) == 1){

accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}

//FINDS SNAP IN HASHMAP
SNAP** SNAPInHash(SNAP** hashMap,char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){
SNAP** accepted = malloc(100 * sizeof(SNAP*));
for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}

int acceptedCounter = 0;
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
SNAP** listAccept = SNAPInList(hashMap[i], address, studentID, name, phoneNum);

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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSG** DeleteCSGInList(CSG** listHead, char course [CNS], int studentID, char grade [GNS]){

CSG* prevBucket = NULL;
CSG* currBucket = *listHead;
//if(*listHead != NULL){
//  printf("%s, %d, %s \n", (*listHead) -> course, (*listHead) -> studentID, (*listHead) -> grade);
//}

if(CSGComp(*listHead, course, studentID, grade) == 1){
*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}else{
prevBucket = *listHead;
currBucket = currBucket -> nextBucket;

}
while(currBucket != NULL){

if(CSGComp(currBucket, course, studentID, grade) == 1){
if(prevBucket != NULL){

prevBucket -> nextBucket = currBucket -> nextBucket;
currBucket = currBucket -> nextBucket;

}else{

*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}

}else{

 if(prevBucket != NULL){
 prevBucket = prevBucket -> nextBucket;
 }
 else{
 prevBucket = *listHead;
 }

 currBucket = currBucket -> nextBucket;
}

}
// printf("==================================");


//if(*listHead != NULL){
//  printf("%s, %d, %s \n", (*listHead) -> course, (*listHead) -> studentID, (*listHead) -> grade);
//}
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
//    printf("%d \n", specialIndex);

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

//LOOKUPS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!LOOKUPS!!!!!!!LOOKUPS!!!!!!!!!!LOOKUPS
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

SNAP** lookupSNAP(SNAP* snapArray[MAP_SIZE],char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){
if(studentID != -1){
int specialIndex = hashStudentID(studentID);
//printf("%d \n", specialIndex);
SNAP* listHead = snapArray[specialIndex];



return SNAPInList(listHead, address, studentID, name, phoneNum);

}

return SNAPInHash(snapArray, address, studentID, name, phoneNum);
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

 DeleteCSGInList(&csgArray[specialIndex], course, studentID, grade);

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
void printSNAPResult(SNAP** result){
int counter = 0;

 while(result[counter] != NULL){
   printf("%s, %d, %s, %s \n", result[counter] -> name, result[counter] -> studentID, result[counter] -> address, result[counter] -> phoneNum);
   counter++;
   }
}

char* getGradeForStudentInCourse(char name[NNS],char course[CNS], CSG* csgArray[MAP_SIZE], SNAP* snapArray[MAP_SIZE]){
int studentID = 0;

SNAP** result = lookupSNAP(snapArray, "*", -1, name, "*");

studentID = result[0] -> studentID;

CSG** result1 = lookupCSG(csgArray, course, studentID, "*");

return result1[0] -> grade;
}
int main() {
    CSG* csgArray[MAP_SIZE] = {NULL};

    SNAP* snapArray[MAP_SIZE] = {NULL};

    CP* cpArray[MAP_SIZE] = {NULL};

    CDH* cdhArray[MAP_SIZE] = {NULL};

    CR* crArray[MAP_SIZE] = {NULL};

  printf("---------------------CSG TEST -------------------- \n");

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


//  printCSGResult(result);

   CSG** result2 = lookupCSG(csgArray, "*", 12345, "*");

//printCSGResult(result2);

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

 deleteCSG(csgArray, "*", 67890, "B");

 result = lookupCSG(csgArray, "CS101", -1, "*");
 printf("------------------------------------------------ \n");

 printCSGResult(result);

  printf("---------------------SNAP TEST -------------------- \n");


    SNAP tuple3;

    strcpy(tuple3.name , "C. Brown");
    tuple3.studentID = 12345;
    strcpy(tuple3.address,"12 Apple St.");
    strcpy(tuple3.phoneNum,"555-1234");
    tuple3.nextBucket = NULL;



    insertSNAP(&tuple3, snapArray);

// for(int i = 0; i < MAP_SIZE; i++ ){
//if(snapArray[i] != NULL){
//  printf("%s, %d, %s, %s \n", snapArray[i] -> name, snapArray[i] -> studentID, snapArray[i] -> address, snapArray[i] -> phoneNum);
//}
//}
   SNAP** result3 = lookupSNAP(snapArray, "*", -1, "C. Brown", "*");

    printSNAPResult(result3);

    printf("%s \n", getGradeForStudentInCourse("C. Brown", "CS101", csgArray, snapArray));

}