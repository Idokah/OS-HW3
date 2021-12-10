//
// Created by Ido Kahlon on 10/12/2021.
//

#ifndef HW3_EX3_Q1_H
#define HW3_EX3_Q1_H

#define MAX_MESSAGE_SIZE  100

void create_threads2(pthread_t* threads_arr, thread_func func, int num, char* finish_msg);
void wait_for_threads(pthread_t* threads, int num, char* finish_message);
void signal_threads(pthread_cond_t* cond, int* done_flag);
void print_message_atomic(char* msg);
int rand_prime_num();
int get_random_atomic();
void write_matrix_atomic();
int max_multiply(int column);
void write_factors_atomic(int num, int f1, int f2);

#endif //HW3_EX3_Q1_H
