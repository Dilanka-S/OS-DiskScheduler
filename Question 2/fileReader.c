/*
// Created by Dilanka Vishad Seneviratne on 2022-05-07.
*/
#include <stdio.h>
#include <stdlib.h>


#include "algorithms.h"

void display(int* dataArray, int count);

void readFile(FILE* file){
    int numCylinders = 0,currentPosition=0,previousPosition=0;
    int requests=0, count=0, temp=0, direction;
    int* dataArray;
    int fcfsResult=0, sstfResult=0, scanResult=0, cscanResult=0, lookResult=0
            ,clookResult=0;

    fscanf(file,"%d %d %d ",&numCylinders,&currentPosition,&previousPosition);

    dataArray = (int*) malloc((sizeof (int)*1000));
    while (!feof(file)){
        fscanf(file,"%d",&requests);
        /*printf("%d ",requests);*/
        dataArray[temp] = requests;
        temp=temp+2;
        dataArray[temp+1] = 0;
        count=count+1;
    }
    count = (count * 2)-1;
    direction = checkDirection(currentPosition,previousPosition);
    fcfsResult = fcfsCalculator(dataArray,currentPosition,previousPosition,count);
    sstfResult = sstfCalculator(dataArray,currentPosition,previousPosition,count,numCylinders);
    scanResult = scanCalculator(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
    cscanResult = cscanCalculator(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
    lookResult = lookCalculator(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
    clookResult = clookCalculator(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
    printf("\nFCFS\t: %d",fcfsResult);
    printf("\nSSTF\t: %d",sstfResult);
    printf("\nSCAN\t: %d",scanResult);
    printf("\nCSCAN\t: %d",cscanResult);
    printf("\nLOOK\t: %d",lookResult);
    printf("\nCLOOK\t: %d",clookResult);
    printf("\n______________________________________________________________\n");
}

void display(int* dataArray, int count){
    int x;
    printf("\n\n");
    for (x=0;x<count;x+=2){
        printf("%d | %d",dataArray[x],dataArray[x+1]);
        printf("\n");
    }
}
