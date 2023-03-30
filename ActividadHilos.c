// Marco Antonio Manzo Ruiz 173127

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREADS_NO 10

void* odd_thread( void *args )
{
    printf( "Soy impar.\n" );
    pthread_exit( NULL );
}
void* even_thread( void *args )
{
    printf( "Soy par.\n" );
    pthread_exit( NULL );
}

int main()
{
    pthread_t threads[THREADS_NO];
    int state, i;
    
    for(i=0; i < THREADS_NO; i++) 
    {
        if (i % 2 == 0)
        {
        	state = pthread_create( &threads[i], NULL, even_thread, NULL );
        printf( "Main creo un hilo en la iteración %d.\n", i );
        }
        else if (i % 2 != 0)
        {
        	state = pthread_create( &threads[i], NULL, odd_thread, NULL );
        printf( "Main creo un hilo en la iteración %d.\n", i );
        }
        
        if (state != 0) 
        {
            perror("pthread_create() error.");
            exit(-1);
        }
    }
    
    for (i = 0; i < THREADS_NO; i++)
    {
    	state = pthread_join(threads[i], NULL);
    	
    	if (state != 0) 
        {
            perror("pthread_join() error.");
            exit(-1);
        }
    	
    }
    exit(0);
}
