#include "database.h"

int hashStudentID (int studentID){
    return (studentID % 1009);
}

void insertCSG (CSG tuple, CSG csgArray[1009]){

    int specialIndex = hashStudentID(tuple.studentID);

    csgArray[specialIndex] = tuple;
};

void insertSNAP(SNAP tuple, SNAP snapArray[1009]){
    int specialIndex = hashStudentID(tuple.studentID);

    snapArray[specialIndex] = tuple;
};

void insertCP(){

};

void insertCDH () {

};

void insertCR () {

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
    CSG csgArray[1009];

    SNAP snapArray[1009];

    CP cpArray[1009];

    CDH cdhArray[1009];

    CR crArray[1009];

}