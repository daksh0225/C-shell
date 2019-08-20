#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <libgen.h>
#include <string.h>
#include "prompt.h"
#include "pwd.h"

int main(int argc, char const *argv[])
{
	char str[256],*end_str;
	int ss=0;
	while(1)
	{
		prompt(argv[0]);
		scanf("%[^\n]%*c",str);
		char *token = strtok_r(str, ";",&end_str),*end_token; 
		while (token != NULL) 
		{ 
			char *to1=strtok_r(token," ",&end_token);
			ss=0;
			while(to1!=NULL)
			{
				if(ss==0)
				{
					if(strcmp(token,"pwd")==0)
						pwd();
				}
				to1=strtok_r(NULL," ",&end_token);
				ss++;
			}
			token = strtok_r(NULL, ";",&end_str); 
		} 
	}
	return 0;
}