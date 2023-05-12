#ifndef SCHEDULER_H
#define SCHEDULER_H

int FCFS_algorithm(int req_list[],int current_pos,int previous_pos);
int SSTF_algorithm(int req_list[],int cur_pos,int reqs,int cylinders);
int SCAN_algorithm(int req_list[],int cur_pos,int reqs,int dir,int cylinders);
int CSCAN_algorithm(int req_list[],int cur_pos,int reqs,int dir,int cylinders);
int LOOK_algorithm(int req_list[],int cur_pos,int reqs,int dir,int cylinders);
int CLOOK_algorithm(int req_list[],int cur_pos,int reqs,int dir,int cylinders);

#endif