#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <libgen.h>
#include <string.h>
#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "ls.h"
#include <time.h>
#include "pinfo.h"
#include "exec.h"
#include <sys/wait.h>
#include "backchk.h"
#include "watch.h"
#include <signal.h>
#include "history.h"
#include <fcntl.h>
char cwd[1000];

void handle_int(int sig)
{
	pid_t pid;
	int status;
	char* exit=(char *)malloc(1000);
	char* estatus=(char *)malloc(1000);
	pid=waitpid(0,&status,WNOHANG);
	printf("%d\n",pid );
	sprintf(exit,"\npid %d exited.\n",pid);
	if(WIFEXITED(status))
	{
		int ret=WEXITSTATUS(status);
		if(ret==0)
			sprintf(estatus, "normally\n");
		else
			sprintf(estatus, "abnormally\n");
	}
	if(pid>0)
	{
		write(2,exit,strlen(exit));
		write(2,estatus,strlen(estatus));
	}
	free(exit);
	prompt(cwd);
	return;
}

int main(int argc, char const *argv[])
{
	while(1)
	{
		char str[1000],*end_str;
		int ss=0,flagecho=0,flagcd=0,flagls=0;
		a:
		if(strlen(cwd)==0)
			strcpy(cwd,realpath(argv[0],NULL));
		prompt(cwd);
		scanf(" %[^\n]s",str);
		w_history(str);
		char *token = strtok_r(str, ";",&end_str),*end_token; 
		while (token != NULL) 
		{ 
			char *to1=strtok_r(token," ",&end_token);
			ss=0;
			while(to1!=NULL)
			{
				if(flagecho==1)
				{
					echo(to1,end_token);
					flagecho=0;
					break;
				}
				else if(flagcd==1)
				{
					cd(cwd,to1,end_token);
					flagcd=0;
					break;
				}
				if(ss==0)
				{
					if(strcmp(to1,"pwd")==0)
					{
						pwd(end_token);
					}
					else if(strcmp(to1,"echo")==0)
					{
						flagecho=1;
					}
					else if(strcmp(to1,"cd")==0)
					{
						if(strlen(end_token)==0)		
						{				
							cd(cwd,end_token,end_token);
							break;
						}
						else
							flagcd=1;
					}
					else if(strcmp(to1,"ls")==0)
					{
						ls(cwd,end_token);
						break;
					}
					else if(strcmp(to1,"pinfo")==0)
					{
						pinfo(end_token);
						break;
					}
					else if(strcmp(to1,"exit")==0)
					{
						exit(0);
					}
					else if(strcmp(to1,"nightswatch")==0)
					{
						watch(end_token);
					}
					else
					{
						pid_t pid=fork();
						int status;
						int pp;
						char *chk_token=end_token;
						pp=isback(chk_token);
						if(pp)
						{
							if(pid==0)
							{
								exec(token,end_token);
								exit(0);
							}
							else
							{
								signal(SIGCHLD,handle_int);
							}
						}
						else
						{
							if(pid==0)
							{
								exec(token,end_token);
								exit(0);
							}
							else
							{
								waitpid(pid,&status,0);
							}
						}
					}
				}
				to1=strtok_r(NULL," ",&end_token);
				ss++;
			}
			token = strtok_r(NULL, ";",&end_str); 
		} 
	}
	return 0;
}
