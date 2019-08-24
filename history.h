#include <fcntl.h>

void w_history(char a[])
{
	int fd1=open("cmd.txt",O_WRONLY|O_CREAT,0644);
	lseek(fd1,0,SEEK_END);
	write(fd1,a,strlen(a));
	write(fd1,"\n",1);
	close(fd1);
	return;
}