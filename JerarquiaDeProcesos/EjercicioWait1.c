#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


void random_number();

int main()
{
	pid_t A, B, M;
	int status;
	srand(time(0));

	A = fork();
	// Hijo A
	if( A == 0 )
	{
		printf("Hijo A, mi pid es %d\n", getpid());
		random_number();
		return(0);
	}
	
	B = fork();
	// Hijo B
	if( B == 0 )
	{
		printf("Hijo B, mi pid es %d\n", getpid());
		random_number();
		return(0);
	}
	
	M = fork();
	// Hijo C
	if( M == 0 )
	{
		printf("Hijo M, mi pid es %d\n", getpid());
		random_number();
		return(0);
	}
	
	// Father
	if( A > 0 )
	{
	wait(&status);
	printf("Mi hijo terminó con estado: %d.\n\n", WEXITSTATUS(status));
	wait(&status);
	printf("Mi hijo terminó con estado: %d.\n\n", WEXITSTATUS(status));
	wait(&status);
	printf("Mi hijo terminó con estado: %d.\n\n", WEXITSTATUS(status));
	}
	return 0;

}

// Write an array into a file
void random_number()
{
	int a =rand();
	int b = a % 100;
	printf("%d\n", b + 1);
}
