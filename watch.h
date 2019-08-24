#include <termios.h>
#include <stdbool.h>
#include <sys/ioctl.h>

bool keyDown() {
    struct termios oldt, newt;
    int bytes;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ioctl(STDIN_FILENO, FIONREAD, &bytes);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return bytes > 0;
}
void watch(char a[])
{
	int p=0,t;
	char *end_a;
	char *token=strtok_r(a," ",&end_a),func[1000],time[1000];
	while(token!=NULL)
	{
		if(p==0)
		{
			if(strcmp(token,"-n")!=0)
			{
				printf("invalid arguments\n");
				return;
			}
		}
		else if(p==1)
		{
			strcpy(time,token);
			t=atoi(token);
		}
		else if(p==2)
		{
			strcpy(func,token);
		}
		p++;
		token=strtok_r(NULL," ",&end_a);
	}
	if(p!=3)
	{
		printf("invalid arguments\n");
		return;
	}
	else
	{
		if(t==0)
		{
			for(int i=0;i<strlen(time);i++)
			{
				if(time[i]!='0')
				{
					printf("invalid arguments\n");
					return;
				}
			}
		}
		else if(strcmp(func,"interrupt")!=0&&strcmp(func,"dirty")!=0)
		{
			printf("invalid arguments\n");
			return;
		}
		else
		{
			if(strcmp(func,"interrupt")==0)
			{	
				int pp=0,b=0;	
				char c;
				while(1)
				{
					if(keyDown())
					{
						char c=getchar();
						printf("\n");
						if(c=='q')
							return;
					}
					char str[1000];
					int l=0;
					static int co=0;
					FILE *f=fopen("/proc/interrupts","r");
					fgets(str,1000,f);
					if(pp==0)
					{
						char *to1=strtok(str," ");
						while(to1!=NULL)
						{
							printf("%s\t",to1 );
							to1=strtok(NULL," ");
							co++;
						}
						if(keyDown())
						{
							char c=getchar();
							printf("\n");
							if(c=='q')
								return;
						}
					}
					printf("\n");
					if(keyDown())
					{
						char c=getchar();
						printf("\n");
						if(c=='q')
							return;
					}
					while(!feof(f))
					{
						fgets(str,1000,f);
						if(l==1)
						{
							char *to1=strtok(str," ");
							to1=strtok(NULL," ");
							for(int i=1;i<co;i++)
							{
								printf("%s\t",to1 );
								to1=strtok(NULL," ");
							}
							if(keyDown())
							{
								char c=getchar();
								printf("\n");
								if(c=='q')
									return;
							}
						}
						l++;
					}
					printf("\n");
					pp++;
					if(keyDown())
					{
						char c=getchar();
						printf("\n");
						if(c=='q')
							return;
					}
					sleep(t);
				}
			}
			else
			{
				int b=0;	
				char c;
				while(1)
				{
					if(keyDown())
					{
						char c=getchar();
						printf("\n");
						if(c=='q')
							return;
					}
					char str[1000];
					int l=0;
					static int co=0;
					FILE *f=fopen("/proc/meminfo","r");
					while(!feof(f))
					{
						fgets(str,1000,f);
						if(l==16)
						{
							char *to1=strtok(str," ");
							for(int i=0;i<3;i++)
							{
								if(i!=0)
									printf("%s",to1 );
								to1=strtok(NULL," ");
							}
							if(keyDown())
							{
								char c=getchar();
								printf("\n");
								if(c=='q')
									return;
							}
						}
						if(keyDown())
						{
							char c=getchar();
							printf("\n");
							if(c=='q')
								return;
						}
						l++;
					}
					if(keyDown())
					{
						char c=getchar();
						printf("\n");
						if(c=='q')
							return;
					}
					sleep(t);
				}
			}
		}
	}
}