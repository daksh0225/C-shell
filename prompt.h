#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct stat s;
void prompt(const char *file)
{
	int i,flag=0,x,pl=0;
	char hostbuffer[1000],*userbuffer,cwd[1000],*path;
	char *pp=(char *)malloc(sizeof(char)*1000);
	gethostname(hostbuffer,sizeof(hostbuffer));
	userbuffer=getlogin();
	getcwd(cwd,sizeof(cwd));
	stat(file,&s);
	path=realpath(file,NULL);
	if(!S_ISDIR(s.st_mode))
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
		else
			pp=cwd;
	}
	else
		pp=cwd;
	printf("<%s@%s:%s>", userbuffer,hostbuffer,pp);
}