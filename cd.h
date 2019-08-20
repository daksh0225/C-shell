#include <unistd.h>
#include <string.h>
#include <errno.h>

void cd(const char *file,char *a,char *b)
{
	int i;
	if(strlen(b)!=0)
		printf("cd: too many arguments\n");
	else
	{
		if(a[0]=='~')
		{
			char c[1000],*path;	
			path=realpath(file,NULL);
			dirname(path);
			int l2=strlen(a);
			for(int j=1;j<l2;j++)
				c[j-1]=a[j];
			strcat(path,c);
			printf("%s\n",path );
			i=chdir(path);
		}
		else
			i=chdir(a);
		// getcwd(c,sizeof(c));
		// printf("%s\n",c );
		if(i!=0)
			perror(0);
	}
}