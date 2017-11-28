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


///////////////////////////////////////////////  SNAP  ////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////// CR /////////////////////////////////////////////////////////////

int CRComp(CR* cr1, char course[CNS], char room[RNS]){

if(strcmp(cr1 -> course, course) == 0 || strcmp(course, "*") == 0 ){
if(strcmp(cr1 -> room, room) == 0 || strcmp(room, "*") == 0){

//printf("HERE \n");
return 1;

}
}

return 0;
}

CR** CRInList(CR* listHead,char course[CNS], char room[RNS]){
CR** accepted = malloc(100 * sizeof(CR*));

for(int i = 0; i < 100; i++){

accepted[i] = NULL;
}
int counter = 0;

if(CRComp(listHead, course, room) == 1){

accepted[counter] = listHead;
counter++;
}
listHead = listHead -> nextBucket;

while(listHead != NULL){

if(CRComp(listHead,course, room) == 1){

accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}

//FINDS CR IN HASHMAP
CR** CRInHash(CR** hashMap,char course[CNS], char room[RNS]){
CR** accepted = malloc(100 * sizeof(CR*));
for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}

int acceptedCounter = 0;
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
CR** listAccept = CRInList(hashMap[i], course, room);

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

//////////////////////////////////////////////////// CDH //////////////////////////////////////////////////////////////////

int CDHComp(CDH* cdh1, char course[CNS], char day[DNS], char hour[HNS]){

if(strcmp(cdh1 -> course, course) == 0 || strcmp(course, "*") == 0 ){
if(strcmp(cdh1 -> day, day) == 0 || strcmp(day, "*") == 0){
if(strcmp(cdh1 -> hour, hour) == 0 || strcmp(hour, "*") == 0){

return 1;
}
}
}
return 0;
}

CDH** CDHInList(CDH* listHead,char course[CNS], char day[DNS], char hour[HNS]){
CDH** accepted = malloc(100 * sizeof(CDH*));

for(int i = 0; i < 100; i++){

accepted[i] = NULL;
}
int counter = 0;

if(CDHComp(listHead, course, day, hour) == 1){

accepted[counter] = listHead;
counter++;
}
listHead = listHead -> nextBucket;

while(listHead != NULL){

if(CDHComp(listHead,course, day, hour) == 1){

accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}

//FINDS CDH IN HASHMAP
CDH** CDHInHash(CDH** hashMap,char course[CNS], char day[DNS], char hour[HNS]){
CDH** accepted = malloc(100 * sizeof(CDH*));
for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}

int acceptedCounter = 0;
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
CDH** listAccept = CDHInList(hashMap[i], course, day, hour);

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

/////////////////////////////////////////////////////DELETE CSG //////////////////////////////////////////////////////////////

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

}


//DELETES CSG IN HASHMAP
void DeleteCSGInHash(CSG** hashMap, char course [CNS], int studentID, char grade [GNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCSGInList(&hashMap[i], course, studentID, grade);

}

}

}

///////////////////////////////////////////////////////// DELETE SNAP /////////////////////////////////////////////////

SNAP** DeleteSNAPInList(SNAP** listHead, char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){

SNAP* prevBucket = NULL;
SNAP* currBucket = *listHead;

if(SNAPComp(*listHead, address, studentID, name, phoneNum) == 1){
*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}else{
prevBucket = *listHead;
currBucket = currBucket -> nextBucket;

}
while(currBucket != NULL){

if(SNAPComp(currBucket, address, studentID, name, phoneNum) == 1){
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

}


// DELETE SNAP IN HASH
void DeleteSNAPInHash(SNAP** hashMap, char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteSNAPInHash(&hashMap[i], address,studentID, name, phoneNum);

}

}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

if(listHead == NULL){
return NULL;
}
return CSGInList(listHead, course, studentID, grade);

}

return CSGInHash(csgArray, course, studentID, grade);

};

SNAP** lookupSNAP(SNAP* snapArray[MAP_SIZE],char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){
if(studentID != -1){
int specialIndex = hashStudentID(studentID);
//printf("%d \n", specialIndex);
SNAP* listHead = snapArray[specialIndex];

if(listHead == NULL){
return NULL;
}

return SNAPInList(listHead, address, studentID, name, phoneNum);

}

return SNAPInHash(snapArray, address, studentID, name, phoneNum);
};

CP **lookupCP(){

};

/////////////////////////////////////////// CDH LOOKUP /////////////////////////////////////////////////////////////
CDH **lookupCDH (CDH* cdhArray[MAP_SIZE], char course[CNS], char day[DNS], char hour[HNS]) {
if(strcmp(course, "*") != 0 && strcmp(day, "*") != 0){
int specialIndex = hashString(course, day);

CDH* listHead = cdhArray[specialIndex];

if(listHead == NULL){
return NULL;
}

return CDHInList(listHead, course, day, hour);

}

return CDHInHash(cdhArray, course, day, hour);
};

////////////////////////////////// CR LOOKUP //////////////////////////////////////////////////////////////////
CR **lookupCR (CR* crArray[MAP_SIZE], char course[CNS], char room[RNS]) {

if(strcmp(course, "*") != 0){
int specialIndex = hashString(course, "");

CR* listHead = crArray[specialIndex];

if(listHead == NULL){
return NULL;
}

return CRInList(listHead, course, room);
}
return CRInHash(crArray, course, room);
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

//////////////////////////////// DELETE SNAP ////////////////////////////////////////
void deleteSNAP(SNAP* snapArray[MAP_SIZE],char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){

if(studentID != -1){
int specialIndex = hashStudentID(studentID);

SNAP* listHead = snapArray[specialIndex];

 DeleteSNAPInList(&snapArray[specialIndex], address, studentID, name, phoneNum);

 return;
}

 DeleteSNAPInHash(snapArray,  address, studentID, name, phoneNum);
 return;
};

//void deleteCP(CP* cpArray[MAP_SIZE], char course[CNS], char preReq[PRS]){
//if(studentID != -1){
//int specialIndex = hashString(course, preReq);
//
//CP* listHead = cpArray[specialIndex];
//
// DeleteCPInList(&cpArray[specialIndex], course, preReq);
//
// return;
//}
//
// DeleteCPInHash(cpArray, course, preReq);
// return;
//};

void deleteCDH () {

};

void deleteCR () {

};


void printCSGResult(CSG** result){
int counter = 0;
if(result == NULL){
return;
}
 while(result[counter] != NULL){
   printf("%s, %d, %s \n", result[counter] -> course, result[counter] -> studentID, result[counter] -> grade);
   counter++;
   }
}
void printSNAPResult(SNAP** result){
int counter = 0;

if(result == NULL){
return;
}


 while(result[counter] != NULL){
   printf("%s, %d, %s, %s \n", result[counter] -> name, result[counter] -> studentID, result[counter] -> address, result[counter] -> phoneNum);
   counter++;
   }
}

void printCRResult(CR** result){
int counter = 0;

if(result == NULL){
return;
}


 while(result[counter] != NULL){
   printf("%s, %s \n", result[counter] -> course, result[counter] -> room);
   counter++;
   }
}

void printCDHResult(CDH** result){
int counter = 0;

if(result == NULL){
return;
}
 while(result[counter] != NULL){
   printf("%s, %s, %s \n", result[counter] -> course, result[counter] -> day, result[counter] -> hour);
   counter++;
   }
}

void printCRDHResult(CRDH** result){
int counter = 0;

if(result == NULL){
return;
}
 while(result[counter] != NULL){
   printf("%s, %s, %s, %s \n", result[counter] -> course, result[counter] -> room, result[counter] -> day, result[counter] -> hour);
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


char* studentLocation(char name[NNS], char hour[HNS], char day[DNS], CSG* csgArray[MAP_SIZE], SNAP* snapArray[MAP_SIZE], CDH* cdhArray[MAP_SIZE], CR* crArray[MAP_SIZE]){
int studentID = 0;

SNAP** result = lookupSNAP(snapArray, "*", -1, name, "*");

int counter = 0;

if(result == NULL){
return NULL;
}

studentID = result[0] -> studentID;

CSG** coursesEnr = lookupCSG(csgArray, "*", studentID, "*");

 while(coursesEnr[counter] != NULL){

   CDH** coursesAtTime = lookupCDH(cdhArray, coursesEnr[counter] -> course, day, hour);
   counter++;

   if(coursesAtTime !=  NULL){
   CR** roomResult = lookupCR(crArray, coursesAtTime[0] -> course, "*");
   if(roomResult != NULL){
   return roomResult[0] -> room;
   }
   }

   }

return NULL;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>   Select CSG course <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
CSG** csgCourseSelector (char course[CNS], CSG* csgArray[MAP_SIZE]){
return lookupCSG(csgArray, course, -1, "*");
}

int* studentIDproj(CSG* csgArray[MAP_SIZE]){
int counter = 0;
int* studentIDList = malloc(100 * sizeof(int*));

for(int i = 0; i < 100; i++){
studentIDList[i] = -1;
}

while(csgArray[counter] != NULL){
studentIDList[counter] = csgArray[counter] -> studentID;
counter++;
}
return studentIDList;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> JOIN BY COURSE (CR, CDH) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
CRDH** cdhcrJoinByCourse(CDH* cdhArray[MAP_SIZE], CR* crArray[MAP_SIZE]){

int counter = 0;

CRDH** table = malloc(100 * sizeof(CRDH*));
for(int i = 0; i < 100; i++){
table[i] = NULL;
}

for(int c = 0; c < MAP_SIZE; c++){

if(cdhArray[c] != NULL){
char cdhCourse[CNS];
strcpy(cdhCourse,cdhArray[c] -> course);

CR** result = lookupCR(crArray, cdhCourse, "*");

char room[RNS];
strcpy(room ,result[0] -> room);

CRDH* tuple = malloc(sizeof(CRDH));

strcpy(tuple -> course, cdhCourse);
strcpy(tuple -> room, room);
strcpy(tuple -> day, cdhArray[c] -> day);
strcpy(tuple -> hour, cdhArray[c] -> hour);

table[counter] = tuple;
counter++;
}
}

return table;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROJECT, SELECT AND JOIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

DH** proSelJoin(CDH* cdhArray[MAP_SIZE], CR* crArray[MAP_SIZE], char room[RNS]){
CRDH** result = cdhcrJoinByCourse(cdhArray, crArray);
DH** projected = malloc(100 * sizeof(DH*));

for(int i = 0; i < 100; i++){
 projected[i] = NULL;
}

int c = 0;

CRDH** accepted = malloc(100 * sizeof(CRDH*));

for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}
int counter = 0;
while(result[c] != NULL){

if(strcmp(result[c] -> room, room) == 0){
accepted[counter] = result[c];
counter++;
}
c++;
}

counter = 0;
while(accepted[counter] != NULL){

DH* tuple = malloc(sizeof(DH));

strcpy(tuple -> day, accepted[counter] -> day);
strcpy(tuple -> hour, accepted[counter] -> hour);

projected[counter] = tuple;
counter++;
}
return projected;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MAIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int main() {
    CSG* csgArray[MAP_SIZE] = {NULL};

    SNAP* snapArray[MAP_SIZE] = {NULL};

    CP* cpArray[MAP_SIZE] = {NULL};

    CDH* cdhArray[MAP_SIZE] = {NULL};

    CR* crArray[MAP_SIZE] = {NULL};

  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CSG TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

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
 printf("----------------------------------------------------------------\n");

 printCSGResult(result);

  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SNAP TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");


    SNAP tuple3;

    strcpy(tuple3.name , "C. Brown");
    tuple3.studentID = 12345;
    strcpy(tuple3.address,"12 Apple St.");
    strcpy(tuple3.phoneNum,"555-1234");
    tuple3.nextBucket = NULL;

  SNAP tuple4;

    strcpy(tuple4.name , "L. Van Pelt");
    tuple4.studentID = 67890;
    strcpy(tuple4.address,"34 Pear Ave.");
    strcpy(tuple4.phoneNum,"555-5678");
    tuple4.nextBucket = NULL;

      insertSNAP(&tuple3, snapArray);

      insertSNAP(&tuple4, snapArray);

// for(int i = 0; i < MAP_SIZE; i++ ){
//if(snapArray[i] != NULL){
//  printf("%s, %d, %s, %s \n", snapArray[i] -> name, snapArray[i] -> studentID, snapArray[i] -> address, snapArray[i] -> phoneNum);
//}
//}
   SNAP** result3 = lookupSNAP(snapArray, "*", -1, "C. Brown", "*");

   SNAP** result4 = lookupSNAP(snapArray, "*", 67890, "L. Van Pelt", "*");


    printSNAPResult(result3);

    printf("L Van Pelt: ");
    printSNAPResult(result4);

    deleteSNAP(snapArray, "*", 67890, "L. Van Pelt", "*");

    printf("After Deletion: ");
    result4 = lookupSNAP(snapArray, "*", 67890, "L. Van Pelt", "*");

    printSNAPResult(result4);


 printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 2, A <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    printf("\n %s \n", getGradeForStudentInCourse("C. Brown", "CS101", csgArray, snapArray));

 printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CR TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

 CR tuple5;

     strcpy(tuple5.course , "CS101");
     strcpy(tuple5.room,"Turing Hall");

     tuple5.nextBucket = NULL;

     insertCR(&tuple5, crArray);

      CR** result5 = lookupCR(crArray, "CS101", "*");

      printCRResult(result5);

   printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CDH TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

 CDH tuple6;

     strcpy(tuple6.course , "CS101");
     strcpy(tuple6.day,"M");
     strcpy(tuple6.hour,"9AM");
     tuple6.nextBucket = NULL;

     insertCDH(&tuple6, cdhArray);

      CDH** result6 = lookupCDH(cdhArray, "CS101", "*", "*");

      printCDHResult(result6);

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 2, B <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    printf("\n %s \n" , studentLocation("C. Brown", "9AM", "M", csgArray,snapArray, cdhArray, crArray));

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 3, 8.12 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    CSG** part3Result = csgCourseSelector("CS101", csgArray);

    printCSGResult(part3Result);

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 3, 8.13 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    int* sIDresult = studentIDproj(part3Result);
    int idCounter = 0;
    while(sIDresult[idCounter] != -1){
    printf("\n %d \n", sIDresult[idCounter]);
    idCounter++;
    }

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 3, 8.14 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    CRDH** newTable= cdhcrJoinByCourse(cdhArray,crArray);
    printCRDHResult(newTable);

}