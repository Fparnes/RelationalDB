#include "database.h"
#include <string.h>
#include <stdlib.h>

char* concatString (char* string1, char* string2){

char* result = malloc(strlen(string1) + strlen(string2) + 1);

strcpy(result, string1);
strcat(result, string2);

return result;
}

unsigned long hashString(char* str1, char* str2){
char* concat = concatString(str1, str2);

unsigned long hash = 5381;
int counter = 0;

while(counter =  *concat++){
hash = ((hash << 5) + hash) + counter;
}

return hash;
}

int hashStudentID (int studentID){
    return (studentID % 1009);
}

void insertCSG (CSG *tuple, CSG *csgArray[1009]){

    int specialIndex = hashStudentID(tuple -> studentID);

    if(csgArray[specialIndex] != NULL){
    tuple -> nextBucket = csgArray[specialIndex];
    }

    csgArray[specialIndex] = tuple;
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
int specialIndex = hashString(tuple->course, tuple->day);

if(cdhArray[specialIndex] != NULL){
    tuple->nextBucket = cdhArray[specialIndex];
    }

    cdhArray[specialIndex] = tuple;
};

void insertCR (CR *tuple,CR *crArray[1009]) {
int specialIndex = hashString(tuple->course, "");

if(crArray[specialIndex] != NULL){
    tuple->nextBucket = crArray[specialIndex];
    }

    crArray[specialIndex] = tuple;
};

CSG *lookupCSG (){

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
    CSG* csgArray[1009];

    SNAP* snapArray[1009];

    CP* cpArray[1009];

    CDH* cdhArray[1009];

    CR* crArray[1009];

}