#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <libgen.h>
#include <string.h>
void prompt(const char *file)
{
	int hostname,i,j,flag=0,x,pl=0;
	char hostbuffer[256],*userbuffer,cwd[256],*path;
	char *pp=(char *)malloc(sizeof(char)*256);
	hostname=gethostname(hostbuffer,sizeof(hostbuffer));
	userbuffer=getlogin();
	getcwd(cwd,sizeof(cwd));
	path=realpath(file,NULL);
	dirname(path);
	int l1=strlen(path);
	int l2=strlen(cwd);
	if(l1<=l2)
	{
		x=l1;
		for(i=0;i<x;i++)
		{
			if(path[i]!=cwd[i])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			pp[0]='~';
			pl=1;
			if(i!=l2)
			{
				for(;i<l2;i++)
				{
					pp[pl]=cwd[i];
					pl++;
				}
			}
		}
	}
	else
		pp=cwd;
	printf("<%s@%s:%s>", userbuffer,hostbuffer,pp);
}