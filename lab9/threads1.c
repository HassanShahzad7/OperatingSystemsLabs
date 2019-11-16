#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define MAX 16
#define NTHREADS 4
void *thread_function(void *);
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  total_sum = 0;
int a[] = { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int part = 0;

int main()
{
   clock_t start_t, end_t, total_t;
   pthread_t thread_id[NTHREADS];
   int i, j;
   start_t = clock();

   for(i=0; i < NTHREADS; i++)
   {
      pthread_create( &thread_id[i], NULL, thread_function, NULL );
   }

   for(j=0; j < NTHREADS; j++)
   {
      pthread_join( thread_id[j], NULL); 
   }
  
   /* Now that all threads are complete I can print the final result.     */
   /* Without the join I could be printing a value before all the threads */
   /* have been completed.                                                */

   printf("Final counter value: %d\n", total_sum);
   end_t = clock();
   total_t = (double)(end_t - start_t);
   printf("Total time taken by CPU: %ld\n", total_t  );
   return 0;
}

void *thread_function(void *dummyPtr)
{
   //printf("Thread number %ld\n", pthread_self());
   
   int thread_part = part++;
   for (int i = thread_part * (MAX / 4); i < (thread_part + 1) * (MAX / 4); i++){
pthread_mutex_lock(&mutex1);
        total_sum += a[i]; 
pthread_mutex_unlock( &mutex1 );
}
}
