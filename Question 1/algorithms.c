/*
 * Created by Dilanka Vishad Seneviratne on 2022-05-07.
*/
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "fileReader.h"
int checkDirection(int currentPosition, int previousPosition){
    int result = 0;
    if(currentPosition<previousPosition){
        result = -1;
    }else if(currentPosition>previousPosition) {
        result = 1;
    }else{
        printf("Current position and the Previous position are the same!");
    }
    return result;
}

int fcfsCalculator(const int* dataArray,int currentPosition, int previousPosition,int count){
    int result=0,while1=0,difference=0;

    while (while1<count){
        previousPosition = currentPosition;
        currentPosition = dataArray[while1];
        while1+=2;
        difference = abs(currentPosition-previousPosition);
        result = result + difference;
        /*printf("\nNew Previous position, Current Position : %d,%d",previousPosition,currentPosition);
         * */
    }
    return result;
}
int sstfClosest(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders){
    int closest=INT_MAX,x,temp=0, result=0;
    for (x=0; x < count; x+=2){
        if(dataArray[x+1]!=1){
            temp = abs(currentPosition - dataArray[x]);
            if (temp < closest) {
                closest = temp;
                result = x;
            }
        }
    }
    return result;
}
int sstfCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders){
    int result=0,visited=0,closestIdx,x;
    int actualCount = (count-1)/2;
    while (visited<=actualCount){
        for (x=0; x <= count ; x+=2) {
            if(dataArray[x+1]!=1){
                closestIdx = sstfClosest(dataArray, currentPosition,previousPosition,count,numCylinders);
                result = result + abs(currentPosition-dataArray[closestIdx]);
                currentPosition = dataArray[closestIdx];
                dataArray[closestIdx+1] = 1;
                visited++;
            }
        }
    }
    return result;
}
int scanClosest(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int closestIdx=-1, i,j,closestVal=INT_MAX;
    switch (direction) {
        case 1 :
            for (i = 0; i <= count; i+=2) {
                if((dataArray[i+1]==0) && (abs(currentPosition-dataArray[i])<closestVal) && (dataArray[i] > currentPosition)){
                    closestVal = abs(currentPosition - dataArray[i]);
                    closestIdx = i;
                }
            }
            break;
        case -1 :
            for (j = 0; j <= count ; j+=2) {
                if((dataArray[j+1]!=1) && abs(currentPosition-dataArray[j])<closestVal &&(dataArray[j] < currentPosition)){
                    closestVal = abs(currentPosition-dataArray[j]);
                    closestIdx = j;
                }
            }
            break;
        default:
            printf("An error has occurred");
            break;
    }
    return closestIdx;
}
int scanCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int result=0,closestIdx,visited=0,i;
    int actualCount = (count-1)/2;
    for (i = 0; i < count ; i+=2) {
        dataArray[i+1]=0;
    }
    while (visited<=actualCount){
        closestIdx = scanClosest(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
        if(closestIdx==-1){
            if(direction==-1){
                result=result+currentPosition;
                currentPosition=0;
                direction = 1;
            }else if(direction==1){
                result=result+abs(currentPosition-(numCylinders-1));
                currentPosition = numCylinders-1;
                direction = -1;
            }
        }else{
            result = result+ abs(currentPosition-dataArray[closestIdx]);
            currentPosition= dataArray[closestIdx];
            dataArray[closestIdx+1] = 1;
            visited++;
        }
    }
    return result;
}
int cscanCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int result=0, closestIdx,visited=0,i;
    int actualCount = (count-1)/2;
    for (i = 0; i < count ; i+=2) {
        dataArray[i+1]=0;
    }
    while (visited<=actualCount) {
        closestIdx = scanClosest(dataArray, currentPosition, previousPosition, count, numCylinders, direction);
        if (closestIdx == -1) {
            if (direction == -1) {
                result = result + currentPosition;
                currentPosition = 0;
                result = result + (numCylinders - 1);
                currentPosition = numCylinders - 1;
            } else if (direction == 1) {
                result = result + abs(currentPosition - (numCylinders - 1));
                currentPosition = numCylinders - 1;
                result = result + (numCylinders - 1);
                currentPosition = 0;
            }
        } else {
            result = result + abs(currentPosition - dataArray[closestIdx]);
            currentPosition = dataArray[closestIdx];
            dataArray[closestIdx + 1] = 1;
            visited++;
        }
    }
    return result;
}

int lookCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int result=0,closestIdx,visited=0,i;
    int actualCount = (count-1)/2;
    for (i = 0; i <= count ; i+=2) {
        dataArray[i+1]=0;
    }
    /*display(dataArray,count);*/
    while (visited<=actualCount){
        closestIdx = scanClosest(dataArray, currentPosition, previousPosition, count, numCylinders, direction);
        if(closestIdx==-1){
            switch (direction) {
                case 1:
                    direction = -1;
                    break;
                case -1:
                    direction = 1;
                    break;
                default:
                    break;
            }
        }else{
            result= result+ abs(currentPosition-dataArray[closestIdx]);
            currentPosition = dataArray[closestIdx];
            dataArray[closestIdx+1] = 1;
            visited++;
        }
    }
    return result;
}

int clookClosest(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int closestVal=INT_MAX,closestIdx=-1,i;
    switch (direction) {
        case 1 :
            for (i = 0; i <= count; i+=2) {
                /*printf("stuck in for loop 1.");*/
                    if((dataArray[i+1]!=1)&& abs(0-dataArray[i])<closestVal){
                        closestVal = abs(0-dataArray[i]);
                        closestIdx = i;
                    }
            }
            break;
        case -1:
            for (i = 0; i <= count ; i+=2) {
                /*printf("stuck in for loop 2");*/
                if(dataArray[i+1]!=1 &&(abs(numCylinders-1)-dataArray[i]) < closestVal){
                    closestVal = abs((numCylinders-1) - dataArray[i]);
                    closestIdx = i;
                }
            }
            break;
        default:
            break;

    }

    return closestIdx;
}

int clookCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction){
    int result=0,closestIdx,visited=0,i;
    int actualCount = (count-1)/2;
    for (i = 0; i <= count ; i+=2) {
        dataArray[i+1]=0;
    }
    /*display(dataArray,count);*/
    while (visited<=actualCount){
        /*printf("\nstuck in while loop");*/
        closestIdx = clookClosest(dataArray,currentPosition,previousPosition,count,numCylinders,direction);
        /*printf("\nclosest Index is : %d",closestIdx);*/
        if(closestIdx==-1){
            switch (direction) {
                case 1:
                    direction = 1;
                    break;
                case -1:
                    direction = -1;
                    break;
                default:
                    break;
            }
        }else{
            result= result+ abs(currentPosition-dataArray[closestIdx]);
            currentPosition = dataArray[closestIdx];
            dataArray[closestIdx+1] = 1;
            visited++;
        }
    }
    return result;

}

/*
int closestNumberCalculator(int* dataArray,int currentPosition, int previousPosition){
    int closest=0;

    return closest;
}
*/


