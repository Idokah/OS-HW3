#include "ex3_q1_given.h"

//------------------------------------------------------------------------
int get_random_in_range()
{
  static int first = 1;
  if (first)
  {
    srand(SEED);
    first = 0;
  }
  int num = (rand() % (RAND_HI - RAND_LO + 1)) + RAND_LO;
  return num;
}

//------------------------------------------------------------------------
int is_prime(int n)
{
  if (n < 2)
    return 0;
  const int sqrt_n = sqrt(n);
  for (int j=2; j <= sqrt_n; j++)
    if (n%j == 0) return 0;
  my_sleep();
  return 1;
}

//---------------------------------
void set_factors(int num, int* n1, int* n2)
{
  for (int j = 2; j < num; j++)
    if (num %j == 0)
    {
      *n1 = j;
      *n2 = num/j;
      return;
    }
  my_exception(__LINE__, __func__, "factors not found");
}

//------------------------------------------------------------------------
void write_matrix(int mat[N][M])
{
  int r, c;
  printf("The Matrix is:\n");
  for (r = 0; r < N; r++)
  {
    for (c = 0; c < M; c++)
    {
      printf("%5d ", mat[r][c]);
      fflush(stdout);
    }
    printf("\n");
  }
}


//------------------------------------------------------------------------
void write_factors(int num, int f1, int f2)
{
  printf("factorizer found: %d = ", num);
  fflush(stdout);
  my_sleep();
  printf("%d X %d\n", f1, f2);
  fflush(stdout);
}

//------------------------------------------------------------------------
void print_msg(const char* msg)
{
  fprintf(stdout, "%s", msg);
  fflush(stdout);
  my_sleep();
  fprintf(stdout, "\n");
  fflush(stdout);
}

//------------------------------------------------------------------------
void write_status(const char* who, int thread_num, const char* what)
{
  fprintf(stdout, "%s #%d ", who, thread_num);
  fflush(stdout);
  my_sleep();
  fprintf(stdout, "%s\n", what);
}

//------------------------------------------------------------------------
// make sure dest is big enough for messages like "initializer #2 starting"
void create_msg(char* dest, const char* who, int num, const char* what)
{
  sprintf(dest, "%s #%d %s", who, num, what);
}

//------------------------------------------------------------------------
void my_sleep()
{
  int p = (int)pthread_self();
  p = p % 30 + 80;
  const struct timespec ts = {0, 1000 * p * SLEEP_FACTOR};
  nanosleep(&ts, NULL);
}

//-----------------------------------------------
// you can use this function - it's not a must
void my_exception(int line, const char* function, char* msg)
{
			fprintf(stderr, "ERROR (line %d function: %s) !!!%s\n", line, function, msg);
      exit(1);
}

