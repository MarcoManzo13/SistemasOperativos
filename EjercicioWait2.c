#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	pid_t A, B, M;
	int status;

	A = fork();
	// Hijo A
	if( A == 0 )
	{
		sleep(10);
		printf("Hijo A, mi pid es %d\n", getpid());
		return(10);
	}
	
	B = fork();
	// Hijo B
	if( B == 0 )
	{
		printf("Hijo B, mi pid es %d\n", getpid());
		return(0);
	}
	
	M = fork();
	// Hijo M
	if( M == 0 )
	{
		sleep(3);
		printf("Hijo M, mi pid es %d\n", getpid());
		return(3);
	}
	
	// Father
	if( A > 0 )
	{
	waitpid(M, &status, 0);
	printf("Mi hijo M terminó con estado: %d.\n", WEXITSTATUS(status));
	waitpid(A, &status, 0);
	printf("Mi hijo A terminó con estado: %d.\n", WEXITSTATUS(status));
	waitpid(B, &status, 0);
	printf("Mi hijo B terminó con estado: %d.\n", WEXITSTATUS(status));
	}
	return 0;

}
