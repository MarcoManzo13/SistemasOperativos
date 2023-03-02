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
	int status, fd, n, m;
	int a[] = {1, 2, 7, 10, 32};
	int b[5];
	pid_A = fork();
	
	if (pid_A == 0)
	{
		fd = creat("datos.txt", 777);
		n = write(fd, a, sizeof(a));
		return 0;
	}
	
	if (pid_A > 0) 
	{
		fd = open("datos.txt", 0);
		m = read(fd, b, sizeof(b));
		for(int i = 0; i < 5; i++)
		{
			printf("%d\n", b[i]);
		}
	return 0;
	}
return 0;
}
