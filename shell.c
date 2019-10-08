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
#include "signals.h"
#include "fg_bg.h"

int main(int argc, char const *argv[])
{
	int count=0,i;
	while(1)
	{
		char str[1000],*end_str;
		int ss=0,flagecho=0,flagcd=0,flagls=0,tempout,tempin,pp=0,pp1=0,parflag=0;
		signal(SIGTSTP,handle_sigZ);
		signal(SIGINT,handle_sigint);
		check_back();
		if(strlen(cwd)==0)
			strcpy(cwd,realpath(argv[0],NULL));
		fflush(stdout);
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
				// int pro;
				output_file_len=0;
				int oo=out_redir(token1),ii=in_redir(token1);
				if(fflag)
				{
					pro=-1;
					char  temptoken[1000];
					dup2(in,0);
					close(in);
					if(oo)
					{
						int temp_len = 0;
						for(int i=0;i<strlen(token1);i++)
						{
							if(token1[i]=='>' || token1[i] == '<')
								break;
							else
							{
								temptoken[temp_len++] = token1[i];
							}								
						}
						strcpy(token1, temptoken);
						token1[temp_len] = '\0';
						if(oo==1)
						{
							int fd=open(output_file,O_WRONLY|O_CREAT|O_TRUNC,0644);
							out=dup(fd);
							close(fd);
						}
						else if(oo==2)
						{
							int fd=open(output_file,O_WRONLY|O_CREAT|O_APPEND,0644);
							out=dup(fd);
							close(fd);
						}
					}
					if(ii)
					{
						int temp_len = 0;
						for(int i=0;i<strlen(token1);i++)
						{
							if(token1[i]=='<'|| token1[i]=='>')
								break;
							else
							{
								temptoken[temp_len++] = token1[i];
							}								
						}
						strcpy(token1, temptoken);
						token1[temp_len] = '\0';
						if(ii==1)
						{
							int fd=open(output_file,O_RDONLY,0644);
							dup2(fd,0);
							close(fd);
						}
					}
					dup2(out,1);
					// dup2(in,0);
					close(out);
					// close(in);
				}
				else
				{
					if (strcmp(token1,"quit")==0)
					{
						exit(0);
					}
					dup2(in,0);
					close(in);
					if(strlen(end_token)==0)
					{
						out=dup(temp_stdout);
						if(oo)
						{
							char  temptoken[1000];
							int temp_len = 0;
							for(int i=0;i<strlen(token1);i++)
							{
								if(token1[i]=='>')
									break;
								else
								{
									temptoken[temp_len++] = token1[i];
								}								
							}
							strcpy(token1, temptoken);
							token1[temp_len] = '\0';
							if(oo==1)
							{
								int fd=open(output_file,O_WRONLY|O_CREAT|O_TRUNC,0644);
								out=dup(fd);
								close(fd);
							}
							else if(oo==2)
							{
								int fd=open(output_file,O_WRONLY|O_CREAT|O_APPEND,0644);
								out=dup(fd);
								close(fd);
							}
						}
						if(ii)
						{
							char  temptoken[1000];
							int temp_len = 0;
							for(int i=0;i<strlen(token1);i++)
							{
								if(token1[i]=='<')
									break;
								else
								{
									temptoken[temp_len++] = token1[i];
								}								
							}
							strcpy(token1, temptoken);
							token1[temp_len] = '\0';
							if(ii==1)
							{
								int fd=open(output_file,O_RDONLY,0644);
								dup2(fd,0);
								close(fd);
							}
						}
					}
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
							if(strcmp(to1,"pwd")==0)
							{
								pwd(end_token1);
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
							else if(strcmp(to1,"fg")==0)
							{
								fg(to1,end_token1);
							}
							// else if(strcmp(to1,"history")==0)
							// {
							// 	d_history(end_token);
							// }
							else
							{
								// if(pro==-1)
								{
									pid=fork();
									int status;
									char *chk_token=end_token1;
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
										}
									}
									else
									{
										if(pid==0)
										{
											exec(to1,end_token1);
											exit(0);
										}
										else
										{
											fprocs[fnpro]=pid;
											fnpro++;
											strcpy(fjobname[pid],token);
											strcpy(fpname[pid],token);
											waitpid(pid,&status,WUNTRACED);
										}
									}
								}
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
