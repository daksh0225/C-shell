#include <time.h>
void lsl(char a[])
{
	struct stat buf;
	stat(a,&buf);
	printf((S_ISSOCK(buf.st_mode))? "s":"");
	printf((S_ISLNK(buf.st_mode))? "l":"");
	printf((S_ISREG(buf.st_mode))? "-":"");
	printf((S_ISDIR(buf.st_mode))? "d":"");
	printf((S_ISBLK(buf.st_mode))? "b":"");
	printf((S_ISCHR(buf.st_mode))? "c":"");										    	
	printf((buf.st_mode & S_IRUSR)? "r":"-");
	printf((buf.st_mode & S_IWUSR)? "w":"-");
	printf((buf.st_mode & S_IXUSR)? "x":"-");
	printf((buf.st_mode & S_IRGRP)? "r":"-");
	printf((buf.st_mode & S_IWGRP)? "w":"-");
	printf((buf.st_mode & S_IXGRP)? "x":"-");
	printf((buf.st_mode & S_IROTH)? "r":"-");
	printf((buf.st_mode & S_IWOTH)? "w":"-");
	printf((buf.st_mode & S_IXOTH)? "x":"-");
	printf(" ");
	printf("%lu",buf.st_nlink );
	printf(" ");					
	struct passwd *pw = getpwuid(buf.st_uid);
	struct group  *gr = getgrgid(buf.st_gid);
	printf("%s %s",pw->pw_name,gr->gr_name );
	printf(" ");					
	printf("%ld",buf.st_size );
	printf(" ");					
	char *tt=ctime(&buf.st_mtim.tv_sec);
	char *t1=strtok(tt," ");
	int s1=0;
	while(t1!=NULL)
	{
		if(s1==1||s1==2)
			printf("%s ",t1 );
		else if(s1==3)
		{

			char *ttt=strtok(t1,":");
			int s2=0;
			while(ttt!=NULL)
			{
				if(s2==0)
					printf("%s:",ttt );
				else if(s2==1)
					printf("%s",ttt );
				ttt=strtok(NULL,":");
				s2++;
			}
		}
		s1++;
		t1=strtok(NULL," ");
	}
	printf(" ");			
}

void ls(const char *file,char a[])
{
	DIR *d;
	struct dirent *dir;
	int f1=0,f2=0;
	char *end_token,*end_a,dname[1000];
	char *token;
	token=(char *)malloc(1000);
	end_token=(char *)malloc(1000);
	end_a=(char *)malloc(1000);
	if(strlen(a)!=0)
		token=strtok_r(a," ",&end_a);
	else
	{
		token=NULL;
		strcpy(dname,".");
	}
	while(token!=NULL)
	{
		if(strcmp(token,"-a")==0)
		{
			f1=1;
			strcpy(dname,".");
		}
		else if(strcmp(token,"-l")==0)
		{
			f2=1;
			strcpy(dname,".");
		}
		else if(strcmp(token,"-la")==0||strcmp(token,"-al")==0)
		{
			f1=1;
			f2=1;
			strcpy(dname,".");
		}
		else
		{
			if(strcmp(token,"-a")==0)
				f1=1;
			else if(strcmp(token,"-l")==0)
				f2=1;
			else if(strcmp(token,"-la")==0||strcmp(token,"-al")==0)
			{
				f1=1;
				f2=1;
			}
			else
			{
				if(token[0]=='~')
				{
					char *c,*path;
					c=(char *)malloc(1000);
					path=(char *)malloc(1000);
					path=realpath(file,NULL);
					dirname(path);
					for(int i=1;i<strlen(token);i++)
						c[i-1]=a[i];
					strcat(path,c);
					strcpy(dname,path);
				}
				else
					strcpy(dname,token);
			}
		}
		token=strtok_r(NULL," ",&end_a);
	}
	d = opendir(dname);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if(dir->d_name[0]=='.')
			{
				if(f1==1)
				{
				    if(f2==1)
						lsl(dir->d_name);
				    printf("%s\n", dir->d_name);
				}
			}
			else
			{				
				if(f2==1)
					lsl(dir->d_name);
			    printf("%s\n", dir->d_name);
			}
		}
		closedir(d);
	}
	else
		printf("ls: cannot access '%s': No such file or directory\n",dname);
		// perror(0);
}