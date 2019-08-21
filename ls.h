#include <time.h>

void ls(char a[])
{
	DIR *d;
	struct dirent *dir;
	int f1=0,f2=0;
	char *end_token,*end_a,dname[1000];
	char *token;
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
			char *to1=strtok_r(token," ",&end_token);
			if(strcmp(to1,"-a")==0)
				f1=1;
			else if(strcmp(to1,"-l")==0)
				f2=1;
			else if(strcmp(to1,"-la")==0||strcmp(to1,"-al")==0)
			{
				f1=1;
				f2=1;
			}
			else
			{
				strcpy(dname,to1);
			}
		}
		token=strtok_r(NULL," ",&end_a);
	}
	// printf("%s\n",dname );
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
				    {
				    	struct stat buf;
				    	stat(dir->d_name,&buf);
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
				    printf("%s\n", dir->d_name);
				}
			}
			else
			{				
				if(f2==1)
			    {
			    	struct stat buf1;
			    	stat(dir->d_name,&buf1);
					printf((S_ISSOCK(buf1.st_mode))? "s":"");
					printf((S_ISLNK(buf1.st_mode))? "l":"");
					printf((S_ISREG(buf1.st_mode))? "-":"");
					printf((S_ISDIR(buf1.st_mode))? "d":"");
					printf((S_ISBLK(buf1.st_mode))? "b":"");
					printf((S_ISCHR(buf1.st_mode))? "c":"");										    	
					printf((buf1.st_mode & S_IRUSR)? "r":"-");
					printf((buf1.st_mode & S_IWUSR)? "w":"-");
					printf((buf1.st_mode & S_IXUSR)? "x":"-");
					printf((buf1.st_mode & S_IRGRP)? "r":"-");
					printf((buf1.st_mode & S_IWGRP)? "w":"-");
					printf((buf1.st_mode & S_IXGRP)? "x":"-");
					printf((buf1.st_mode & S_IROTH)? "r":"-");
					printf((buf1.st_mode & S_IWOTH)? "w":"-");
					printf((buf1.st_mode & S_IXOTH)? "x":"-");
					printf(" ");
					printf("%lu",buf1.st_nlink );
					printf(" ");					
					struct passwd *pw = getpwuid(buf1.st_uid);
					struct group  *gr = getgrgid(buf1.st_gid);
					printf("%s %s",pw->pw_name,gr->gr_name );
					printf(" ");
					printf("%ld",buf1.st_size );
					printf(" ");					
					char *tt=ctime(&buf1.st_mtim.tv_sec);
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
			    printf("%s\n", dir->d_name);
			}
		}
		// closedir(d);
	}
	else
	{
		// perror(0);
	}
}