/*
AUTHOR: FERNANDO PARNES
CSC 173 - PROJECT 4
DATE: 11/28/2017 - 7:30PM

This program implements a relational database for the registrar database found in FOCS chapter 8.
It represents the database as a HashMap of structs representing the relations of the database. Insert, lookup and Join
functionality are implemented for every relation, as well as special relational algebra operations that are detailed below.

string hashing algorithm was inspired by djb2 algorithm found in:

http://www.cse.yorku.ca/~oz/hash.html

It was modified to accept concatenated strings, and the ultimate hash was modded by 1009.
*/

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

//Hashes a pair of strings by concatenating them and hashing result, this was inspired by the djb2 hashing algorithm, and modified by me.
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
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>     CSG COMP       <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//Individually checks every element of tuple,
//if it is a "*" for strings or -1 for integers consider it an automatic match
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

/*
This function finds a CSG in a single linked list.
Begin by declaring an array of CSG pointers and allocate memory and initializing it to NULL.
For the first element in the list compare elements of given CSG to find matching attributes. If it is a match, add it to accepted array.
Increment the position of listHead, and repeat.
Return accepted once operation is complete.
*/
CSG** CSGInList(CSG* listHead, char course [CNS], int studentID, char grade [GNS]){
CSG** accepted = malloc(100 * sizeof(CSG*));

for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}
int counter = 0;

if(CSGComp(listHead, course, studentID, grade) == 1){

accepted[counter] = listHead;
counter++;
}
listHead = listHead -> nextBucket;

while(listHead != NULL){

if(CSGComp(listHead, course, studentID, grade) == 1){

accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> FIND CSG IN HASHMAP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
This function finds all matching CSG's in HashMap.
Begin by declaring an array of CSG pointers and allocate memory and initializing it to NULL.
Loop through the HashMap locations and lists at those locations looking for any matches.
Add those matches to array of accepted items.
Return the accepted array.
*/
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


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SNAP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int SNAPComp(SNAP* csg1, char address[ANS], int studentID, char name[NNS], char phoneNum[PNS]){

if(strcmp(csg1 -> address, address) == 0 || strcmp(address, "*") == 0 ){
if (csg1 -> studentID == studentID || studentID == -1){
if(strcmp(csg1 -> name, name) == 0 || strcmp(name, "*") == 0){
if(strcmp(csg1 -> phoneNum, phoneNum) == 0 || strcmp(phoneNum, "*") == 0){

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int CRComp(CR* cr1, char course[CNS], char room[RNS]){

if(strcmp(cr1 -> course, course) == 0 || strcmp(course, "*") == 0 ){
if(strcmp(cr1 -> room, room) == 0 || strcmp(room, "*") == 0){

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CDH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int CPComp(CP* cp1, char course[CNS], char preReq[PNS]){

if(strcmp(cp1 -> course, course) == 0 || strcmp(course, "*") == 0 ){
if(strcmp(cp1 -> preReq, preReq) == 0 || strcmp(preReq, "*") == 0){

return 1;
}
}
return 0;
}

CP** CPInList(CP* listHead,char course[CNS], char preReq[PNS]){
CP** accepted = malloc(100 * sizeof(CDH*));

for(int i = 0; i < 100; i++){

accepted[i] = NULL;
}
int counter = 0;

if(CPComp(listHead, course, preReq) == 1){

accepted[counter] = listHead;
counter++;
}
listHead = listHead -> nextBucket;

while(listHead != NULL){

if(CPComp(listHead,course, preReq) == 1){

accepted[counter] = listHead;
counter++;

}else{

 listHead = listHead -> nextBucket;

 }
}
return accepted;
}

//FINDS CDH IN HASHMAP
CP** CPInHash(CP** hashMap,char course[CNS], char preReq[PNS]){
CP** accepted = malloc(100 * sizeof(CP*));
for(int i = 0; i < 100; i++){
accepted[i] = NULL;
}

int acceptedCounter = 0;
for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
CP** listAccept = CPInList(hashMap[i], course, preReq);

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DELETE CSG <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
Deletes items that match from a linked-list, re-arranging links as necessary. The listhead is also renamed if it gets deleted.
Deletion is accomplished by unlinking item to be deleted from linked list.

*/
CSG** DeleteCSGInList(CSG** listHead, char course [CNS], int studentID, char grade [GNS]){

CSG* prevBucket = NULL;
CSG* currBucket = *listHead;

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


//Iterates through a hashmap and uses delete in list function to delete all desired items.
void DeleteCSGInHash(CSG** hashMap, char course [CNS], int studentID, char grade [GNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCSGInList(&hashMap[i], course, studentID, grade);

}

}

}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DELETE SNAP LIST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  DELETE CP  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
CP** DeleteCPInList(CP** listHead, char course[CNS], char preReq[PNS]){

CP* prevBucket = NULL;
CP* currBucket = *listHead;

if(CPComp(*listHead, course, preReq) == 1){
*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}else{
prevBucket = *listHead;
currBucket = currBucket -> nextBucket;

}
while(currBucket != NULL){

if(CPComp(currBucket, course, preReq) == 1){
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


// DELETE CP IN HASH
void DeleteCPInHash(CP** hashMap, char course[CNS], char preReq[PNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCPInHash(&hashMap[i], course, preReq);

}

}

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>  DELETE CDH  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

CDH** DeleteCDHInList(CDH** listHead, char course[CNS], char day[DNS], char hour[HNS]){

CDH* prevBucket = NULL;
CDH* currBucket = *listHead;

if(CDHComp(*listHead, course, day, hour) == 1){
*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}else{
prevBucket = *listHead;
currBucket = currBucket -> nextBucket;

}

while(currBucket != NULL){

if(CDHComp(currBucket, course, day, hour) == 1){
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
// DELETE CDH IN HASH
void DeleteCDHInHash(CDH** hashMap, char course[CNS], char day[DNS], char hour[HNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCDHInHash(&hashMap[i], course, day, hour);

}

}

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DELETE CR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

CR** DeleteCRInList(CR** listHead, char course[CNS], char room[RNS]){

CR* prevBucket = NULL;
CR* currBucket = *listHead;

if(CRComp(*listHead, course, room) == 1){
*listHead = (*listHead) -> nextBucket;
currBucket = *listHead;
}else{
prevBucket = *listHead;
currBucket = currBucket -> nextBucket;

}
while(currBucket != NULL){

if(CRComp(currBucket, course, room) == 1){
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


// DELETE CR IN HASH
void DeleteCRInHash(CR** hashMap, char course[CNS], char room[RNS]){

for(int i = 0; i < MAP_SIZE; i++ ){

if(hashMap[i] != NULL){
DeleteCRInHash(&hashMap[i], course, room);

}

}

}


// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INSERT CSG <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INSERT SNAP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertSNAP(SNAP *tuple, SNAP *snapArray[MAP_SIZE]){

      int specialIndex = hashStudentID(tuple -> studentID);
//    printf("%d \n", specialIndex);

      if(snapArray[specialIndex] != NULL){

      tuple -> nextBucket = snapArray[specialIndex];
      }

      snapArray[specialIndex] = tuple;
};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INSERT CP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void insertCP(CP *tuple, CP *cpArray[MAP_SIZE]){
int specialIndex = hashString(tuple -> course, tuple -> preReq);

if(cpArray[specialIndex] != NULL){
    tuple->nextBucket = cpArray[specialIndex];
    }

    cpArray[specialIndex] = tuple;
};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INSERT CDH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertCDH (CDH *tuple, CDH *cdhArray[MAP_SIZE]) {
int specialIndex = hashString(tuple -> course, tuple -> day);

if(cdhArray[specialIndex] != NULL){
    tuple -> nextBucket = cdhArray[specialIndex];
    }

    cdhArray[specialIndex] = tuple;
};

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>INSERT CR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void insertCR (CR *tuple,CR *crArray[MAP_SIZE]) {
int specialIndex = hashString(tuple -> course, "");

if(crArray[specialIndex] != NULL){
    tuple -> nextBucket = crArray[specialIndex];
    }

    crArray[specialIndex] = tuple;
};

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> LOOKUP CSG <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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

///////////////////////////////////////////// CP LOOKUP /////////////////////////////////////////////////////
CP **lookupCP(CP* cpArray[MAP_SIZE],char course[CNS], char preReq[PNS]){
if(strcmp(course, "*") != 0 && strcmp(preReq, "*") != 0){
int specialIndex = hashString(course, preReq);

CP* listHead = cpArray[specialIndex];

if(listHead == NULL){
return NULL;
}

return CPInList(listHead, course, preReq);

}

return CPInHash(cpArray, course, preReq);
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

void deleteCP(CP* cpArray[MAP_SIZE], char course[CNS], char preReq[PRS]){
if(strcmp(course, "*") != 0 && strcmp(preReq, "*") != 0){
int specialIndex = hashString(course, preReq);

CP* listHead = cpArray[specialIndex];

 DeleteCPInList(&cpArray[specialIndex], course, preReq);

 return;
}

DeleteCPInHash(cpArray, course, preReq);
 return;
};

void deleteCDH (CDH* cdhArray[MAP_SIZE], char course[CNS], char day[DNS], char hour[HNS]) {
if(strcmp(course, "*") != 0 && strcmp(day, "*") != 0){
int specialIndex = hashString(course, day);

CDH* listHead = cdhArray[specialIndex];

 DeleteCDHInList(&cdhArray[specialIndex], course, day, hour);

 return;
}

DeleteCDHInHash(cdhArray, course, day, hour);
 return;
};

void deleteCR (CR* crArray[MAP_SIZE], char course[CNS], char room[RNS]) {
if(strcmp(course, "*") != 0){
int specialIndex = hashString(course, "");

CR* listHead = crArray[specialIndex];

 DeleteCRInList(&crArray[specialIndex], course, room);

 return;
}

DeleteCRInHash(crArray, course, room);
 return;
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

void printCPResult(CP** result){
int counter = 0;

if(result == NULL){
return;
}


 while(result[counter] != NULL){
   printf("%s, %s \n", result[counter] -> course, result[counter] -> preReq);
   counter++;
   }
}


void printCDHResult(CDH** result){
int counter = 0;

if(result == NULL){
return;
}
 while(result[counter] != NULL){
   printf("%s, %s,  %s \n", result[counter] -> course, result[counter] -> day, result[counter] -> hour);
   counter++;
   }
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PRINT CRDH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PRINT DH <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void printDHResult(DH** result){
int counter = 0;

if(result == NULL){
return;
}
 while(result[counter] != NULL){
   printf("%s, %s \n",result[counter] -> day, result[counter] -> hour);
   counter++;
   }
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> GET GRADE FOR STUDENT IN COURSE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
Uses SNAP array to identify studentID of given student, and uses said ID in a CSG lookup to find
the grade for a given student in a course.

*/
char* getGradeForStudentInCourse(char name[NNS],char course[CNS], CSG* csgArray[MAP_SIZE], SNAP* snapArray[MAP_SIZE]){
int studentID = 0;

SNAP** result = lookupSNAP(snapArray, "*", -1, name, "*");

studentID = result[0] -> studentID;

CSG** result1 = lookupCSG(csgArray, course, studentID, "*");

return result1[0] -> grade;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> STUDENT LOCATION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
Begins by finding studentID in SNAP array, using said ID in a CSG lookup to find courses thy are enrolled in.
Use said courses to find time and day for courses. Find course that meets at specified time, and then lookup what room
that course meets in.
Return the room (student location), or NULL if not found.
*/
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
//Selects given course using a lookup.
CSG** csgCourseSelector (char course[CNS], CSG* csgArray[MAP_SIZE]){
return lookupCSG(csgArray, course, -1, "*");
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> STUDENT ID PROJECTION <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
Returns a list of student ID's within the given CSG Array.

*/
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
/*
Makes use of new struct CRDH (course, room, day, hour) to store the information in both a CDH and CR structs.
Function creates new CRDH struct, populates it with aforementioned info and returns it. It does this by looking at the courses
in CDH struct and adding the appropriate row (for room) found in CR struct.

*/
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
/*
First join given tables using prev function. Creates an Array of accepted CRDH structs that have the matching room.
Returns a list of a new structs DH (day, hour), where the info for said structs is pulled from the aforementioned CRDH structs.

*/
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

    insertCSG (&tuple, csgArray);

   CSG** result = lookupCSG(csgArray, "CS101", 12345, "*");

   CSG** result2 = lookupCSG(csgArray, "*", 12345, "*");

 printf("----------------------------------------------------------------\n");


 CSG tuple2;

    strcpy(tuple2.course,"CS101");
    tuple2.studentID = 67890;
    strcpy(tuple2.grade,"B");
    tuple2.nextBucket = NULL;

    insertCSG (&tuple2, csgArray);

  CSG tuple22;

  strcpy(tuple22.course,"EE200");
  tuple22.studentID = 12345;
  strcpy(tuple22.grade,"C");
  tuple22.nextBucket = NULL;

  insertCSG (&tuple22, csgArray);

  CSG tuple222;

  strcpy(tuple222.course,"EE200");
  tuple222.studentID = 22222;
  strcpy(tuple222.grade,"B+");
  tuple222.nextBucket = NULL;

  insertCSG (&tuple222, csgArray);

    CSG tuple2222;

    strcpy(tuple2222.course,"CS101");
    tuple2222.studentID = 33333;
    strcpy(tuple2222.grade,"A-");
    tuple2222.nextBucket = NULL;

    insertCSG (&tuple2222, csgArray);

  CSG tuple22222;

  strcpy(tuple22222.course,"PH100");
  tuple22222.studentID = 67890;
  strcpy(tuple22222.grade,"C-");
  tuple22222.nextBucket = NULL;

  insertCSG (&tuple22222, csgArray);

  result = lookupCSG(csgArray, "*", -1, "*");

  printCSGResult(result);



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 result = lookupCSG(csgArray, "CS101", -1, "*");
 printf("----------------------------------------------------------------\n");

 printCSGResult(result);

  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SNAP TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

printf("\nINSERTS AND DIFFERENT LOOKUPS: \n");

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


   SNAP** result3 = lookupSNAP(snapArray, "*", -1, "C. Brown", "*");

   SNAP** result4 = lookupSNAP(snapArray, "*", 67890, "L. Van Pelt", "*");


    printSNAPResult(result3);

    printSNAPResult(result4);

  SNAP tuple44;

    strcpy(tuple44.name , "P. Patty");
    tuple44.studentID = 22222;
    strcpy(tuple44.address,"56 Grape Blvd.");
    strcpy(tuple44.phoneNum,"555-5678");
    tuple44.nextBucket = NULL;

      insertSNAP(&tuple44, snapArray);

printf("\nSNAP RELATION: \n");
   SNAP** result44 = lookupSNAP(snapArray, "*", -1, "*", "*");
    printSNAPResult(result44);

//--------------------------------------------------------------------------------------------------------------
    deleteSNAP(snapArray, "*", 67890, "L. Van Pelt", "*");

    printf("\n\nAfter Deletion of L. Van Pelt: \n ");
    result4 = lookupSNAP(snapArray, "*", -1,"*" , "*");

    printSNAPResult(result4);

 printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CR TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

 CR tuple5;

     strcpy(tuple5.course , "CS101");
     strcpy(tuple5.room,"Turing Hall");
     tuple5.nextBucket = NULL;

     insertCR(&tuple5, crArray);

 CR tuple55;

      strcpy(tuple55.course , "EE200");
      strcpy(tuple55.room,"25 Ohm Hall");
      tuple55.nextBucket = NULL;

      insertCR(&tuple55, crArray);

 CR tuple555;

      strcpy(tuple555.course , "PH100");
      strcpy(tuple555.room,"Newton Lab.");
      tuple555.nextBucket = NULL;

      insertCR(&tuple555, crArray);

   printf("\nLOOKUP ON CSC101:\n");

      CR** result5 = lookupCR(crArray, "CS101", "*");

      printCRResult(result5);

    printf("\nLOOKUP ON ENTIRE CR RELATION:\n");

      result5 = lookupCR(crArray, "*", "*");

      printCRResult(result5);

   printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CDH TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

 CDH tuple6;

     strcpy(tuple6.course , "CS101");
     strcpy(tuple6.day,"M");
     strcpy(tuple6.hour,"9AM");
     tuple6.nextBucket = NULL;

     insertCDH(&tuple6, cdhArray);

  CDH tuple66;

      strcpy(tuple66.course , "CS101");
      strcpy(tuple66.day,"W");
      strcpy(tuple66.hour,"9AM");
      tuple66.nextBucket = NULL;

      insertCDH(&tuple66, cdhArray);

   CDH tuple666;

       strcpy(tuple666.course , "CS101");
       strcpy(tuple666.day,"F");
       strcpy(tuple666.hour,"9AM");
       tuple666.nextBucket = NULL;

       insertCDH(&tuple666, cdhArray);

    CDH tuple6666;

        strcpy(tuple6666.course , "EE200");
        strcpy(tuple6666.day,"Tu");
        strcpy(tuple6666.hour,"10AM");
        tuple6666.nextBucket = NULL;

        insertCDH(&tuple6666, cdhArray);

    CDH tuple66666;

        strcpy(tuple66666.course , "EE200");
        strcpy(tuple66666.day,"W");
        strcpy(tuple66666.hour,"1PM");
        tuple66666.nextBucket = NULL;

        insertCDH(&tuple66666, cdhArray);

    CDH tuple666666;

        strcpy(tuple666666.course , "EE200");
        strcpy(tuple666666.day,"Th");
        strcpy(tuple666666.hour,"10AM");
        tuple666666.nextBucket = NULL;

        insertCDH(&tuple666666, cdhArray);

    printf("\n Lookup on CDH for CS101: \n");
    CDH** result6 = lookupCDH(cdhArray, "CS101", "*", "*");

          printCDHResult(result6);

        printf("\n Lookup on CDH Relation: \n");

        result6 = lookupCDH(cdhArray, "*", "*", "*");

        printCDHResult(result6);

   printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CP TEST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

CP tuple7;

     strcpy(tuple7.course , "CS101");
     strcpy(tuple7.preReq,"CS100");
     tuple7.nextBucket = NULL;

     insertCP(&tuple7, cpArray);


CP tuple77;

     strcpy(tuple77.course , "EE200");
     strcpy(tuple77.preReq,"EE205");
     tuple77.nextBucket = NULL;

     insertCP(&tuple77, cpArray);

CP tuple777;

     strcpy(tuple777.course , "EE200");
     strcpy(tuple777.preReq,"CS100");
     tuple777.nextBucket = NULL;

     insertCP(&tuple777, cpArray);

CP tuple7777;

     strcpy(tuple7777.course , "CS120");
     strcpy(tuple7777.preReq,"CS101");
     tuple7777.nextBucket = NULL;

     insertCP(&tuple7777, cpArray);

CP tuple77777;

     strcpy(tuple77777.course , "CS121");
     strcpy(tuple77777.preReq,"CS120");
     tuple77777.nextBucket = NULL;

     insertCP(&tuple77777, cpArray);

CP tuple777777;

     strcpy(tuple777777.course , "CS205");
     strcpy(tuple777777.preReq,"CS101");
     tuple777777.nextBucket = NULL;

     insertCP(&tuple777777, cpArray);

CP tuple7777777;

     strcpy(tuple7777777.course , "CS206");
     strcpy(tuple7777777.preReq,"CS121");
     tuple7777777.nextBucket = NULL;

     insertCP(&tuple7777777, cpArray);

CP tuple77777777;

     strcpy(tuple77777777.course , "CS206");
     strcpy(tuple77777777.preReq,"CS205");
     tuple77777777.nextBucket = NULL;

     insertCP(&tuple77777777, cpArray);

   printf("\nLOOKUP ON CSC101:\n");

      CP** result7 = lookupCP(cpArray, "CS101", "*");

      printCPResult(result7);

    printf("\nLOOKUP ON ENTIRE CP RELATION:\n");

      result7 = lookupCP(cpArray, "*", "*");

      printCPResult(result7);

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 2, A <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");
    printf("\n Grade for C.Brown in CS101: \n");

    printf("\n %s \n", getGradeForStudentInCourse("C. Brown", "CS101", csgArray, snapArray));

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 2, B <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    printf("\n Where is C. Brown 9AM on a Monday: \n");

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

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PART 3, 8.15 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< \n");

    DH** newTable2= proSelJoin(cdhArray, crArray, "Turing Hall");
    printDHResult(newTable2);
}