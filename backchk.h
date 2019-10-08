int isback(char a[])
{
	if(strlen(a)==0)
		return 0;
	else
	{
		int i;
		for(i=0;i<strlen(a);i++)
		{
			if(a[i]=='&')
				return 1;
		}
	}
	return 0;
}

void check_back()
{
	int status;
	pid_t wpid;
	while((wpid = waitpid(-1, &status, WNOHANG)) > 0) 
	{
		for(int j = 0; j < npro; j++)
		{
			if(procs[j] == wpid)
			{
				type[procs[j]]=1;
				char estatus[100];
				int ret=WEXITSTATUS(status);
				if(ret==0)
				{
					sprintf(estatus,"normally");
				}
				else
				{
					sprintf(estatus,"abnormally");
				}					
				printf("%s [%d]+	Done\t PID %d %s\n",pname[procs[j]],procs[j], wpid,estatus);
				type[procs[j]]=1;
				fflush(stdout);
			}
		}
	}
}