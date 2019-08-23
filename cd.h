void cd(const char *file,char *a,char *b)
{
	int i;
	char  file1[1000];
	if(strlen(b)!=0)
		printf("cd: too many arguments\n");
	else
	{
		char *path;
		path=(char *)malloc(1000);
		if(strlen(a)==0)
		{
			path=realpath(file,NULL);
			dirname(path);
		}
		else if(a[0]=='~')
		{
			char *c;
			c=(char *)malloc(sizeof(char)*1000);
			path=realpath(file,NULL);
			dirname(path);
			int l2=strlen(a);
			for(int j=1;j<l2;j++)
				c[j-1]=a[j];
			strcat(path,c);
		}
		else
		{
			strcpy(path,a);
		}
		i=chdir(path);
		if(i!=0)
			printf("cd: no such file or directory: %s\n",path );
	}
}