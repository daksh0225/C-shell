void pinfo(char a[])
{
	char file1[1000],state,comm[100],file2[1000],file3[1000],*buf2;
	buf2=(char *)malloc(1000);
	int pid=getppid();
	int ppid,unused,mem=0;
	if(strlen(a)==0)
		sprintf(file3,"/proc/%d/exe",pid);
	else
		sprintf(file3,"/proc/%s/exe",a);
	int i=readlink(file3,buf2,1000);
	if(strlen(a)==0)
		sprintf(file1,"/proc/%d/stat",pid);
	else
		sprintf(file1,"/proc/%s/stat",a);
	FILE *f=fopen(file1,"r");
	if(f==NULL)
	{
		printf("Error: Invalid pid\n");
		return;
	}
	fscanf(f,"%d %s %c %d",&unused,comm,&state,&ppid);
	printf("pid -- %d\n",unused );
	printf("Process Status -- {%c}\n",state);
	if(strlen(a)==0)
		sprintf(file2,"/proc/%d/statm",pid);
	else
		sprintf(file2,"/proc/%s/statm",a);
	FILE *f1=fopen(file2,"r");
	fscanf(f1,"%d %d",&mem,&unused);
	printf("memory -- %d\n",mem);
	buf2[strlen(buf2)]='\0';
	printf("Executable Path -- %s\n",buf2);
	fclose(f);
	fclose(f1);
}