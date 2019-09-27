#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <libgen.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include "global.h"
#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "exec.h"
#include "backchk.h"
#include "watch.h"
#include "history.h"
#include "redirchk.h"
#include "env.h"
#include "jobs.h"
#include "fg_bg.h"

void handle_int(int sig)
{
	// npro--;
	char str[1000];
	pid_t pid;
	int status;
	char* exit=(char *)malloc(1000);
	char* estatus=(char *)malloc(1000);
	pid=waitpid(0,&status,WNOHANG);
	type[pid]=1;
	sprintf(exit,"%s with pid %d exited ",pname[pid],pid);
	// strcpy(pname[pid],"");
	if(WIFEXITED(status))
	{
		int ret=WEXITSTATUS(status);
		if(ret==0)
			sprintf(estatus, "normally.\n");
		else
			sprintf(estatus, "abnormally.\n");
	}
	else if(WIFSIGNALED(status))
	{
		int ret=WEXITSTATUS(status);
		if(ret==0)
			sprintf(estatus,"abnormally.\n");
		else
			sprintf(estatus,"normally.\n");
	}
	if(pid>0)
	{
		write(2,exit,strlen(exit));
		write(2,estatus,strlen(estatus));
		prompt(cwd);	
		fflush(stdout);
	}
	free(exit);
	return;
}

void handle_sigint(int sig)
{
	printf("\n");
	return;
}

void check_back()
{
	int status;
	pid_t wpid;
	while((wpid = waitpid(-1, &status, WNOHANG)) > 0) 
	{
		{
			for(int j = 0; j < npro; j++)
			{
				if(procs[j] == wpid)
				{
					type[procs[j]]=1;
					printf("%s [%d]+	Done\t PID %d\n",pname[procs[j]],procs[j], wpid);
					fflush(stdout);
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	int count=0,i;
	while(1)
	{
		char str[1000],*end_str;
		int ss=0,flagecho=0,flagcd=0,flagls=0,tempout,tempin,pp=0,pp1=0,parflag=0;
		signal(SIGINT,handle_sigint);
		check_back();
		if(strlen(cwd)==0)
			strcpy(cwd,realpath(argv[0],NULL));
		prompt(cwd);
		scanf(" %[^\n]s",str);
		char *cstr;
		cstr=(char *)malloc(1000);
		cstr=str;
		int temp_stdin=dup(0);
		int temp_stdout=dup(1);
		// w_history(cstr);
		check_back();
		char *token = strtok_r(str, ";",&end_str),*end_token;
		while (token != NULL)
		{
			int fflag=0;
			char *token1 = strtok_r(token, "|",&end_token),*end_token1;
			if(strlen(end_token)==0)
				fflag=1;
			check_back();
			int in=dup(0);
			int out=dup(1);
			while(token1!=NULL)
			{
				int pro;
				if(fflag)
					pro=-1;
				else
				{
					if (strcmp(token1,"quit")==0)
					{
						exit(0);
					}
					dup2(in,0);
					close(in);
					if(strlen(end_token)==0)
						out=dup(temp_stdout);
					else
					{
						int fd[2];
						pipe(fd);
						out=fd[1];
						in=fd[0];
					}
					dup2(out,1);
					close(out);
					pro=fork();
				}
				char *to1=strtok_r(token1," ",&end_token1);
				char *chk_token=end_token1;
				pp=isback(chk_token);
				check_back();
				if(pro==0||pro==-1)
				{
					// if(pp)
					// {
					// 	if(strlen(end_token)!=0)
					// 	{
					// 		write(1,"Parse error near '|'",21);
					// 		// continue;
					// 		// exit(0);
					// 		// break;
					// 		parflag=1;
					// 		goto A;
					// 	}
					// }
					int ss=0;
					while(to1!=NULL)
					{
						check_back();
						if(flagecho==1)
						{
							echo(to1,end_token1);
							flagecho=0;
							break;
						}
						else if(flagcd==1)
						{
							cd(cwd,to1,end_token1);
							flagcd=0;
							break;
						}
						if(ss==0)
						{
							int p=isredir(end_token1);
							if(strcmp(to1,"pwd")==0)
							{
								pwd(end_token1,p);
							}
							else if(strcmp(to1,"echo")==0)
							{
								flagecho=1;
							}
							else if(strcmp(to1,"cd")==0)
							{
								if(strlen(end_token1)==0)		
								{				
									cd(cwd,end_token1,end_token1);
									break;
								}
								else
									flagcd=1;
							}
							else if(strcmp(to1,"ls")==0)
							{
								ls(cwd,end_token1);
								break;
							}
							else if(strcmp(to1,"pinfo")==0)
							{
								pinfo(end_token1);
								break;
							}
							else if(strcmp(to1,"setenv")==0)
							{
								setE(end_token1);
							}
							else if(strcmp(to1,"unsetenv")==0)
							{
								unsetE(end_token1);
							}
							else if(strcmp(to1,"quit")==0)
							{
								exit(0);
							}
							else if(strcmp(to1,"nightswatch")==0)
							{
								watch(end_token1);
							}
							else if(strcmp(to1,"jobs")==0)
							{
								jobs(end_token1);
							}
							else if(strcmp(to1,"kjob")==0)
							{
								kjob(end_token1);
							}
							else if(strcmp(to1,"overkill")==0)
							{
								overkill(end_token1);
							}
							else if(strcmp(to1,"bg")==0)
							{
								bg(end_token1);
							}
							// else if(strcmp(to1,"history")==0)
							// {
							// 	d_history(end_token);
							// }
							else
							{
								// if(pro==-1)
								{
									pid_t pid=fork();
									int status;
									char *chk_token=end_token1;
									pp1=isredir(chk_token);
									if(pp)
									{
										if(pid==0)
										{
											setpgid(0,0);
											exec(to1,end_token1);
											exit(0);
										}
										else
										{
											procs[npro]=pid;
											npro++;
											strcpy(jobname[pid],token);
											strcpy(pname[pid],token);
											signal(SIGCHLD,handle_int);
										}
									}
									else if(pp1)
									{
										if(pid==0)
										{
											// setpgid(0,0);
											exec1(to1,end_token1);
											exit(0);
										}
										else
										{
											waitpid(pid,&status,0);
										}
									}
									else
									{
										if(pid==0)
										{
											// setpgid(0,0);
											exec(to1,end_token1);
											exit(0);
										}
										else
										{
											waitpid(pid,&status,0);
										}
									}
								}
								// else
									// exec(to1,end_token1);
							}
						}
						to1=strtok_r(NULL," ",&end_token1);
						ss++;
					}
					if(pro!=-1)
						exit(0);
				}
				else
				{
					int status;
					if(pro!=-1)
					{
						waitpid(pro,&status,0);
					}
					dup2(temp_stdin,0);
					dup2(temp_stdout,1);
				}
				token1 = strtok_r(NULL,"|",&end_token);
			}
			dup2(temp_stdin,0);
			dup2(temp_stdout,1);
			token = strtok_r(NULL, ";",&end_str); 
		} 
	}
	return 0;
}
