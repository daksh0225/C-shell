#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
void pwd(char a[])
{
	char cwd[1000];
	getcwd(cwd,sizeof(cwd));
	char *end_a;
	int temp = dup(1);
	if(strlen(a)!=0)
		printf("pwd: too many arguments\n");
	// else if(strlen(a)!=0)
	// {
	// 	char *token=strtok_r(a," ",&end_a);
	// 	while(token!=NULL)
	// 	{
	// 		if(strcmp(token,">")==0)
	// 		{
	// 			token=strtok_r(NULL," ",&end_a);
	// 			if(strlen(end_a)!=0)
	// 				printf("pwd: too many arguments\n");
	// 			else
	// 			{
	// 				int f=open(token,O_WRONLY|O_CREAT,0644);
	// 				dup2(f,1);
	// 				printf("%s\n",cwd );
	// 				close(f);
	// 			}
	// 		}
	// 		else if(strcmp(token,">>")==0)
	// 		{
	// 			token=strtok_r(NULL," ",&end_a);
	// 			if(strlen(end_a)!=0)
	// 				printf("pwd: too many arguments\n");
	// 			else
	// 			{
	// 				int f=open(token,O_WRONLY|O_CREAT,0644);
	// 				lseek(f,0,2);
	// 				dup2(f,1);
	// 				printf("%s\n",cwd );
	// 				close(f);
	// 			}
	// 		}
	// 		token=strtok_r(NULL," ",&end_a);
	// 	}
	// }
	else
		printf("%s\n",cwd );
	dup2(temp, 1);
	// close(temp);
}
