/*
// Created by Dilanka Vishad Seneviratne on 2022-05-07.
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "fileReader.h"

void welcomeMessage(){
    printf("*================================*\n");
    printf("|            WELCOME             |\n");
    printf("|            TO  THE             |\n");
    printf("|   DISK SCHEDULER SIMULATION    |\n");
    printf("*================================*\n");
}
void exitMessage(){
    printf("*================================*\n");
    printf("|           THANK YOU            |\n");
    printf("|         FOR USING THE          |\n");
    printf("|   DISK SCHEDULER SIMULATION    |\n");
    printf("*================================*\n");
}

void fileReadBanner(){
    printf("\n> Please enter the name of the file you want to get the output for\n");
    printf("\tOR\n> 'QUIT' to close the program");
    printf("\n\nYour selection : ");
}
void mainMenu(){
    char filename[10];
    FILE* file;

    fileReadBanner();
    scanf("%s",filename);
    printf("\n");

    while (strcmp(filename,"QUIT")){
        file = fopen(filename,"r");
        if (file!=NULL){

            printf("\nFor %s:",filename);
            readFile(file);
            fileReadBanner();
            scanf("%s", filename);
            printf("\n");
        }else {
            printf("Incorrect file name! Please enter again!");
            fileReadBanner();
            scanf("%s", filename);
            printf("\n");
        }
    }
}


