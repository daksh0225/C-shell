void handle_sigint(int sig)
{
	// printf("%d",pro);
	if(pro != 0&&pro!=-1)
	{
		int temp = pro;
		kill(pro, SIGINT);
		pro = 0;
	}
}

void handle_sigZ()
{
	// int pid=getpid();
	if(pid>0)
	{
		flagz = 1;
		int i;
		int temp = pid;
		for(i=0;i<fnpro;i++)
		{
			if(fprocs[i]==pid)
			{
				flagz= 0;
				kill(temp, 19);
				printf("\n%s\t%s\t[%d]\n","Stopped",fjobname[fprocs[i]],fprocs[i]);
				procs[npro]=pid;
				type[procs[npro]]=0;
				strcpy(jobname[procs[npro]],fjobname[fprocs[i]]);
				strcpy(pname[procs[npro]],fjobname[fprocs[i]]);
				npro++;
				break;
			}
		}
		fflush(stdout);
		pid =0;
	}	
}
