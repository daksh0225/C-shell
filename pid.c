#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(void)
{
	int n;
	struct rusage usage;
	printf("My process ID : %d\n", getpid());
	printf("My parent's ID: %d\n", getppid());
	while(1)
	{
		scanf("%d",&n);
		printf("%d\n",n );
	}
	return 0;	
}