/*  file: ex3_q1_given.h
  ****  do not change or modify this file ****
*/

#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#define RAND_LO          1      // low bound for random numbers
#define RAND_HI          200    // hi  bound for random numbers
#define SEED             1001   // constant seed, yield fixed series of random

#define N                3      // number of rows and also initializer threads
#define M                4      // number of columns and also multiplier/factorizer threads

// print constants - *** USE THESE ONES for output!!  don't use your "own" text ***
#define INIT_CREATED     "main thread created all initializer threads"
#define MULT_CREATED     "main thread created all multiplier threads"
#define FACT_CREATED     "main thread created all factorizer threads"
#define INIT_TERMINATED  "all initializers terminated"
#define MULT_TERMINATED  "all multipliers terminated"
#define FACT_TERMINATED  "all factorizers terminated"

// use the following, combined with create_msg(...) to create messages 
//  like "initializer #2 starting" or "initializer #2 is done"
#define INITIALIZER      "initializer"
#define MULTIPLIER       "multiplier"
#define FACTORIZER       "factorizer"
#define STARTING         "starting"
#define DONE             "is done"

#define SLEEP_FACTOR     150  // used by my_sleep

typedef void* (*thread_func)(void*);  // this should help you writing less code

// *********** function prototypes ***********
// function dealing with numbers
int get_random_in_range();
int is_prime(int n);
void set_factors(int, int*, int*);

// function dealing with writing to stdout or stderr
void create_msg(char* dest, const char* who, int num, const char* what);
void print_msg(const char* msg);
void write_matrix(int mat[N][M]);
void write_factors(int, int, int);


// other misc. functions
void my_sleep();
// call my_exception when your code reached unexpected condition
void  my_exception(int line, const char* function, char* msg);  



