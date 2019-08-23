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
	execvp(arg[0],arg);
}