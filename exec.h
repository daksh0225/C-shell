#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
void exec(char a[], char b[])
{
	char* arg[1000];
	arg[0]=a;
	int i=1;
	char *token,*end_b;
	if(strlen(b)!=0)
		token=strtok_r(b," ",&end_b);
	else
		token=NULL;
	while(token!=NULL)
	{
		if(strcmp(token,"&")!=0)
		{
			arg[i]=token;
			i++;
		}
		token=strtok_r(NULL," ",&end_b);
	}
	arg[i]=NULL;
	if(execvp(arg[0],arg)!=0)
		printf("Error: command not found: %s\n",arg[0] );
}

void exec1(char a[], char b[])
{
	char *arg[1000];
	arg[0]=a;
	int i=1;
	char *token, *end_b;
	if(strlen(b)!=0)
		token=strtok_r(b," ",&end_b);
	else
		token=NULL;
	while(token!=NULL)
	{
		static int flag=0,f=0;
		if(strcmp(token,"<")==0)
		{
			arg[i]=NULL;
			token=strtok_r(NULL," ",&end_b);
			int f=open(token,O_RDONLY|O_CREAT,0644);
			dup2(f,0);
			int pid=fork(),status;
			if(pid==0)
			{
				if(execvp(arg[0],arg)!=0)
					printf("Error: command not found: %s\n",arg[0] );
				exit(0);
			}
			else
				waitpid(pid,&status,0);
			i=0;
			dup2(f,0);
			flag=1;
		}
		else if(strcmp(token,">")==0)
		{
			arg[i]=NULL;
			token=strtok_r(NULL," ",&end_b);
			int f=open(token,O_WRONLY|O_CREAT,0644);
			if(flag==0)
				dup2(f,1);
			if(execvp(arg[0],arg)!=0)
				printf("Error: command not found: %s\n",arg[0] );
			i=0;
		}
		else if(strcmp(token,">>")==0)
		{
			arg[i]=NULL;
			token=strtok_r(NULL," ",&end_b);
			int f=open(token,O_WRONLY|O_CREAT,0644);
			lseek(f,0,2);
			dup2(f,1);
			if(execvp(arg[0],arg)!=0)
				printf("Error: command not found: %s\n",arg[0] );
			i=0;
		}
		else
		{
			arg[i]=token;
			i++;
		}
		// if(f==0)
		token=strtok_r(NULL," ",&end_b);
	}
}