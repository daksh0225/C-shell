#include <unistd.h>
void pwd()
{
	char cwd[256];
	getcwd(cwd,sizeof(cwd));
	printf("%s\n",cwd );
}
