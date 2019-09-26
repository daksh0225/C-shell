#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct stat s;
void prompt(const char *file)
{
	int i,flag=0,x,pl=0;
	char hostbuffer[1000],*userbuffer,cwd[1000],*path;
	char *pp=(char *)malloc(sizeof(char)*1000);
	userbuffer=(char *)malloc(1000);
	path=(char *)malloc(1000);
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
			if(l2>l1)
			{
				if(cwd[l1]=='/')
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
					pp[pl] = '\0';
				}
				else
					pp=cwd;
			}
			else
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
				pp[pl] = '\0';
			}
		}
		else
			pp=cwd;
	}
	else
		pp=cwd;
	int ll=strlen(pp);
	pp[ll]='\0';
	char buf[1000];
	sprintf(buf,"<%s@%s:%s>", userbuffer,hostbuffer,pp);
	write(1,buf,strlen(buf));
	fflush(stdout);
}