#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define ORANGE_MAX_VALUE 1000000
#define APPLE_MAX_VALUE  100000000
#define MSECOND          1000000


struct Apple {
  unsigned long long a;
  char c[124];
  unsigned long long b;
};

struct Orange {
  int a[ORANGE_MAX_VALUE];
  int b[ORANGE_MAX_VALUE]; 
};

void *adda(void *x)
{
  unsigned long long sum = 0;
  timeval tpstart,tpend;
  float time_use = 0;

  gettimeofday(&tpstart, NULL);

  for (sum = 0; sum < APPLE_MAX_VALUE; ++sum)
  {
    ((Apple *)x)->a += sum;
  }

  gettimeofday(&tpend, NULL);
  time_use = MSECOND * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec -
      tpstart.tv_usec;
  time_use /= MSECOND;

  printf("main tread:%x,Used time:%f \n",pthread_self(),time_use);
  
  return NULL;
}
void *addb(void *y)
{
  unsigned long long sum = 0;
  timeval tpstart,tpend;
  float time_use = 0;

  gettimeofday(&tpstart, NULL);
  

  for (sum = 0; sum < APPLE_MAX_VALUE; ++sum)
  {
    ((Apple *)y)->b += sum;
  }

  gettimeofday(&tpend, NULL);

  time_use = MSECOND * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec -
      tpstart.tv_usec;
  time_use /= MSECOND;

  printf("main tread:%x,Used time:%f \n",pthread_self(),time_use);
  
  return NULL;
}
int main(int argc, const char *grgv[]) {
  // insert code here...
  Apple test = {0,0};
  Orange test1 = {{0},{0}};
  pthread_t ThreadA,ThreadB;

  unsigned long long sum, index;
  sum = 0;
  index = 0;
  struct timeval tpstart, tpend;
  float timeuse;
  
  // get start time
  gettimeofday(&tpstart, NULL);

  pthread_create(&ThreadA, NULL, adda, &test);
  
  pthread_create(&ThreadB, NULL, addb, &test);

  for (index = 0; index < ORANGE_MAX_VALUE; index++)
  {
    sum += test1.a[index] + test1.b[index];
  }

  pthread_join(ThreadA, NULL);
  pthread_join(ThreadB, NULL);
  // get end time
  gettimeofday(&tpend, NULL);

  // calculate time
  timeuse = MSECOND * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec -
      tpstart.tv_usec;
  timeuse /= MSECOND;

  printf("main tread:%x,Used time:%f \n",pthread_self(),timeuse);
  printf("a = %llu, b = %llu, sum = %llu \n",test.a,test.b,sum);

  return 0;
}

