#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "algorithms.h"
#include "scheduler.h"
#include "menus.h"

pthread_mutex_t mutex_eka; 
pthread_cond_t condition_eka;

int buffer1[1003];
int numCylinders, currentPosition, previousPosition,count=0;
int buffer2;
int buffer_safety_lock[2] = {0,0};
int direction;

int finished[6];
int seek_time_identifier;


void* threadA(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = fcfsCalculator(buffer1,currentPosition,previousPosition,count);
    seek_time_identifier =  1;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* threadB(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = sstfCalculator(buffer1,buffer1[1001],buffer1[1002],count,buffer1[1000]);
    seek_time_identifier =  2;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* threadC(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = scanCalculator(buffer1,buffer1[1001],buffer1[1002],count,buffer1[1000],direction);
    seek_time_identifier =  3;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* threadD(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = cscanCalculator(buffer1,buffer1[1001],buffer1[1002],count,buffer1[1000],direction);
    seek_time_identifier =  4;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* threadE(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = lookCalculator(buffer1,buffer1[1001],buffer1[1002],count,buffer1[1000],direction);
    seek_time_identifier =  5;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* threadF(){
    pthread_mutex_lock(&mutex_eka);
    while(buffer_safety_lock[1] == 1){
        pthread_cond_wait(&condition_eka,&mutex_eka);
    }
    direction = checkDirection(currentPosition,previousPosition);
    buffer2 = clookCalculator(buffer1,buffer1[1001],buffer1[1002],count,buffer1[1000],direction);
    seek_time_identifier =  6;
    buffer_safety_lock[1] = 1;
    pthread_mutex_unlock(&mutex_eka);

    pthread_exit(NULL);
}

void* parentThread(){
    pthread_t childA,childB,childC,childD,childE,childF;

    while(1){
        char filename[10];
        FILE* file;
        int temp=0,requests=0;
        welcomeMessage();
        fileReadBanner();
        scanf("%s",filename);
        printf("\n");

        if(strcmp(filename,"QUIT")==0){
            exit(0);
        }

        file = fopen(filename,"r");

        while (file == NULL)
        {
            printf("\nIncorrect file name has been entered");
            printf("\nYour selection : ");
            scanf("%s",filename);
            printf("\n");

            file = fopen(filename,"r");

            if (!strcmp(filename, "QUIT"))
            {
                exit(0);
            }
        }

        memset(finished,0,sizeof(int)*6);
        seek_time_identifier = 0;
        memset(buffer_safety_lock,0,sizeof(int)*2);

        fscanf(file,"%d %d %d ",&numCylinders,&currentPosition,&previousPosition);
        buffer1[1000] = numCylinders;
        buffer1[1001] = currentPosition;
        buffer1[1002] = previousPosition;
        while (!feof(file)){
            fscanf(file,"%d",&requests);
            buffer1[temp] = requests;
            temp=temp+2;
            buffer1[temp+1] = 0;
            count=count+1;
        }
        count = (count * 2)-1;


        if (pthread_create(&childA, NULL, &threadA, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }
        if (pthread_create(&childB, NULL, &threadB, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }
        if (pthread_create(&childC, NULL, &threadC, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }
        if (pthread_create(&childD, NULL, &threadD, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }
        if (pthread_create(&childE, NULL, &threadE, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }
        if (pthread_create(&childF, NULL, &threadF, NULL) != 0) {
            perror("Failed to create parent thread");
            exit(0);
        }

        int x = 0;
        while(x != 6) 
        {
            
            if (seek_time_identifier == 1 && finished[0] == 0 )
            {
                printf("FCFS: %d\n",buffer2);
                buffer_safety_lock[1] = 0;
                finished[0] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
            }
            else if (seek_time_identifier == 2 && finished[1] == 0 )
            {
                printf("SSTF: %d\n",buffer2);
                buffer_safety_lock[1] = 0;
                finished[1] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
                
            }
            else if (seek_time_identifier == 3 && finished[2] == 0 )
            {
                printf("SCAN: %d\n",buffer2);
                buffer_safety_lock[1] = 0;
                finished[2] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
            }
            else if (seek_time_identifier == 4 && finished[3] == 0 )
            {
                printf("CSCAN: %d\n",buffer2);    
                buffer_safety_lock[1] = 0;
                finished[3] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
            }
            else if (seek_time_identifier == 4 && finished[4] == 0 )
            {
                printf("LOOK: %d\n",buffer2);
                buffer_safety_lock[1] = 0;
                finished[4] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
            }
            else if (seek_time_identifier == 5 && finished[5] == 0 )
            {
                printf("CLOOK: %d\n",buffer2);
                buffer_safety_lock[1] = 0;
                finished[5] = 1;
                pthread_cond_broadcast(&condition_eka);
                x += 1;
            } 
        }

        if (pthread_join(childA, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }
        if (pthread_join(childB, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }
        if (pthread_join(childC, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }
        if (pthread_join(childD, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }
        if (pthread_join(childE, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }
        if (pthread_join(childF, NULL) != 0) {
            perror("Failed to join parent thread");
            exit(0);
        }

    }

}

int main()
{
    pthread_t parent;

    pthread_mutex_init(&mutex_eka,NULL);
    pthread_cond_init(&condition_eka,NULL);

    if (pthread_create(&parent, NULL, &parentThread, NULL) != 0) {
        perror("Failed to create parent thread");
    }

    if (pthread_join(parent, NULL) != 0) {
        perror("Failed to join parent thread");
    }

    pthread_mutex_destroy(&mutex_eka);
    pthread_cond_destroy(&condition_eka); 
    
    return 0;

}