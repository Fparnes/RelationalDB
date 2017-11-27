//
// Created by fernp on 11/13/2017.
//

#ifndef CSC173PROJ4_DATABASE_H
#define CSC173PROJ4_DATABASE_H
#define CNS 5
#define PRS 5
#define GNS 5
#define DNS 2
#define HNS 4
#define NNS 100
#define ANS 100
#define PNS 10
#define RNS 100
#define SINS 6
#define MAP_SIZE 1009



typedef struct CSG  {
    char course[CNS];
    int  studentID;
    char grade[GNS];
    struct CSG *nextBucket;
}CSG;

typedef struct SNAP {
    char name[NNS];
    char address[ANS];
    char phoneNum[PNS];
    int studentID;
    struct SNAP *nextBucket;
}SNAP;

typedef struct CP {
    char course[CNS];
    char preReq[PRS];
    struct CP *nextBucket;
}CP;

typedef struct CDH {
    char course[CNS];
    char day[DNS];
    char hour[HNS];
    struct CDH *nextBucket;
}CDH;

typedef struct CR {
    char course[CNS];
    char room[CNS];
    struct CR *nextBucket;
}CR;


#endif //CSC173PROJ4_DATABASE_H
