#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

pthread_mutex_t my_mutex;
int points_in_circle = 0;

void *create_points(void *arg)
{
	int i;
    	double x, y;

	int *num_points = (int *)arg;
	for (i = 0; i < *num_points; i++)
	{
		x = random()/ ((double)RAND_MAX + 1) * 2.0 - 1.0;
        	y = random()/ ((double)RAND_MAX + 1) * 2.0 - 1.0;
        	if (sqrt(pow(x, 2) + pow(y, 2)) <= 1){
			pthread_mutex_lock(&my_mutex);
			points_in_circle++;
			pthread_mutex_unlock(&my_mutex);
		}

	}
	return NULL;
}


int main(int argc, char *argv[])
{
	srandom((unsigned)time(NULL));
	int total_points = atoi(argv[1]);

	int points_per_thread = total_points / 4;
	pthread_t thread1, thread2, thread3, thread4;

	pthread_create(&thread1, NULL, create_points, &points_per_thread);
	pthread_create(&thread2, NULL, create_points, &points_per_thread);
	pthread_create(&thread3, NULL, create_points, &points_per_thread);
	pthread_create(&thread4, NULL, create_points, &points_per_thread);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);

	double pi = 4.0 * points_in_circle / total_points;
	printf("%f\n", pi);

    	return 0;
}

