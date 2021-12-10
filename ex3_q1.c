#include <stdio.h>
#include "ex3_q1_given.h"
#include "ex3_q1.h"

int mat[N][M];
int product_arr[M];

pthread_cond_t initializes_done = PTHREAD_COND_INITIALIZER;
pthread_cond_t multipliers_done = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mult_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fact_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t get_random = PTHREAD_MUTEX_INITIALIZER;

int done_init = 0;
int done_multipliers = 0;

void* init_row( void *ptr ) {
    char msg[MAX_MESSAGE_SIZE];
    int row = *((int*) ptr);
    create_msg(msg, INITIALIZER, row+1, STARTING);
    print_message_atomic(msg);

    for (int i = 0; i < M ; ++i) {
        mat[row][i] = rand_prime_num();
    }

    create_msg(msg, INITIALIZER, row+1, DONE);
    print_message_atomic(msg);
    free(ptr);
    pthread_exit(NULL);
}

void* max_multiply_to_product_arr( void *ptr ){
    char msg[MAX_MESSAGE_SIZE];
    int column = *((int*) ptr);

    pthread_mutex_lock(&mult_mutex);
    if (done_init == 0)
        pthread_cond_wait(&initializes_done, &mult_mutex);
    pthread_mutex_unlock(&mult_mutex);

    create_msg(msg, MULTIPLIER, column+1, STARTING);
    print_message_atomic(msg);

    product_arr[column] = max_multiply(column);

    create_msg(msg, MULTIPLIER, column+1, DONE);
    print_message_atomic(msg);
    free(ptr);

    pthread_exit(NULL);
}

void* find_and_print_factors( void *ptr ) {
    char msg[MAX_MESSAGE_SIZE];
    int index = *((int*) ptr);

    pthread_mutex_lock(&fact_mutex);
    if (done_init == 0)
        pthread_cond_wait(&multipliers_done, &fact_mutex);
    pthread_mutex_unlock(&fact_mutex);

    create_msg(msg, FACTORIZER, index+1, STARTING);
    print_message_atomic(msg);

    int factor1, factor2;
    set_factors(product_arr[index], &factor1, &factor2);
    write_factors_atomic(product_arr[index], factor1, factor2);

    create_msg(msg, FACTORIZER, index+1, DONE);
    print_message_atomic(msg);
    free(ptr);

    pthread_exit(NULL);
}

int main() {
    pthread_t initialize_threads[N];
    pthread_t multipliers_threads[M];
    pthread_t factor_threads[M];

    create_threads(initialize_threads, init_row, N, INIT_CREATED);
    create_threads(multipliers_threads, max_multiply_to_product_arr, M, MULT_CREATED);
    create_threads(factor_threads, find_and_print_factors, M, FACT_CREATED);

    wait_for_threads(initialize_threads, N, INIT_TERMINATED);
    write_matrix_atomic();
    signal_threads(&initializes_done, &done_init);

    wait_for_threads(multipliers_threads, M, MULT_TERMINATED);
    signal_threads(&multipliers_done, &done_multipliers);

    wait_for_threads(factor_threads, M, FACT_TERMINATED);

    print_msg("The program finished");
    pthread_exit(NULL);
}

void create_threads(pthread_t* threads_arr, thread_func func, int num, char* finish_msg) {
    int *ptr;
    for (int i = 0; i < num; ++i) {
        ptr = malloc(sizeof(int));
        *ptr = i;
        pthread_create(&threads_arr[i], NULL, func, (void*) ptr);
    }
    print_message_atomic(finish_msg);
}

void wait_for_threads(pthread_t* threads, int num, char* finish_message){
    for (int i = 0 ; i < num; ++i) {
        pthread_join(threads[i], NULL);
    }
    print_message_atomic(finish_message);
}

void signal_threads(pthread_cond_t* cond, int* done_flag) {
    *done_flag = 1 ;
    pthread_cond_broadcast(cond);
}

void write_matrix_atomic() {
    pthread_mutex_lock(&m2);
    write_matrix(mat);
    pthread_mutex_unlock(&m2);
}

void write_factors_atomic(int num, int f1, int f2) {
    pthread_mutex_lock(&m2);
    write_factors(num, f1, f2);
    pthread_mutex_unlock(&m2);
}

void print_message_atomic(char* msg) {
    pthread_mutex_lock(&m2);
    print_msg(msg);
    pthread_mutex_unlock(&m2);
}

int rand_prime_num() {
    int rand = get_random_in_range();
    while (!is_prime(rand))
        rand = get_random_atomic();
    return rand;
}

int get_random_atomic() {
    pthread_mutex_lock(&get_random);
    int rand = get_random_in_range();
    pthread_mutex_unlock(&get_random);
    return rand;
}

int max_multiply(int column) {
    int largest1 = mat[0][column];
    int largest2 = mat[1][column];
    int temp;
    if (largest1 < largest2)
    {
        temp = largest1;
        largest1 = largest2;
        largest2 = temp;
    }

    for (int i = 2; i < N; ++i)
    {
        if (mat[i][column] > largest1)
        {
            largest2 = largest1;
            largest1 = mat[i][column];
        }
        else if (mat[i][column] > largest2 && mat[i][column] != largest1)
        {
            largest2 = mat[i][column];
        }
    }

    return largest1*largest2;
}