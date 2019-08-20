#include <unistd.h>
#include <string.h>
void pwd(char a[])
{
	char cwd[256];
	getcwd(cwd,sizeof(cwd));
	if(strlen(a)!=0)
		printf("pwd: too many arguments\n");
	else
		printf("%s\n",cwd );
}
