#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	pid_t pid_A;
	int status;
	
	pid_A = fork();

	// Child process
	if( pid_A == 0 )
	{
	return 0;
	}
	else
	{
	execl("/home/marco/Documents/SistemasOperativosParcial1/HelloWorldExe", "", NULL);
	perror("Execl no funcionó.");
	}
	return 0;
}
