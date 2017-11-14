//
// Created by fernp on 11/13/2017.
//

#ifndef CSC173PROJ4_DATABASE_H
#define CSC173PROJ4_DATABASE_H
typedef struct CSG  {
    char course[5];
    int  studentID;
    char grade[5];
    struct CSG *nextBucket;
}CSG;

typedef struct SNAP {
    char name[100];
    char Address[100];
    char phoneNum[10];
    int studentID;
    struct SNAP *nextBucket;
}SNAP;

typedef struct CP {
    char course[5];
    char preReq[5];
    struct CP *nextBucket;
}CP;

typedef struct CDH {
    char course[5];
    char day[2];
    char hour[4];
    struct CDH *nextBucket;
}CDH;

typedef struct CR {
    char course[5];
    char room[100];
    struct CR *nextBucket;
}CR;
#endif //CSC173PROJ4_DATABASE_H
