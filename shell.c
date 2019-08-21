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

int main(int argc, char const *argv[])
{
	char *cwd=(char *)malloc(1000);
	while(1)
	{
		char str[1000],*end_str;
		int ss=0,flagecho=0,flagcd=0,flagls=0;
		if(strlen(cwd)==0)
			cwd=realpath(argv[0],NULL);
		printf("%s\n",cwd );
		prompt(cwd);
		scanf(" %[^\n]s",str);
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
				else if(flagls==1)
				{
					flagls=0;
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
						ls(end_token);
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