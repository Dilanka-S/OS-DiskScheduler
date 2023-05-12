/*
 Created by Dilanka Vishad Seneviratne on 2022-05-07.
*/

#ifndef TEST_ALGORITHMS_H
#define TEST_ALGORITHMS_H

int checkDirection(int currentPosition, int previousPosition);
int fcfsCalculator(int* dataArray,int currentPosition, int previousPosition,int count);
int sstfCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders);
int sstfClosest(int* dataArray,int currentPosition,int previousPosition,int count, int numCylinders);
int scanClosest(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);
int scanCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);
int cscanCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);
int lookCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);
int clookClosest(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);
int clookCalculator(int* dataArray,int currentPosition, int previousPosition,int count,int numCylinders,int direction);


#endif
