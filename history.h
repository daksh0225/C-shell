#include <fcntl.h>

void w_history(char a[])
{
	int fd1=open("cmd.txt",O_WRONLY|O_CREAT,0644);
	lseek(fd1,0,SEEK_END);
	write(fd1,a,strlen(a));
	write(fd1,"\n",1);
	close(fd1);
	return;
}
// void history(char cmdline[],char tilda[])
// {
//     char location[1000],temp[1000];
//     strcpy(location,tilda);
//     strcpy(temp,tilda);
//     strcat(location,"/cmd.txt");
//     strcat(temp,"/temp.txt");
//     char buf[1000];
//     int count = 0;
//     FILE *fptr;
//     fptr = fopen(location,"ab+");
//     while( fgets(buf, 1000, fptr) != NULL )
//     {
//         count++;
//         //printf("%d",count);
//     }
//     if(count<20)
//     {
//         fprintf(fptr,"%s\n",cmdline);
//         fclose(fptr);
//     }
//     else
//     {   count=0;
//         fclose(fptr);
//         FILE *fptr1;
//         FILE *fptr2;
//         fptr1 = fopen(location,"ab+");
//         fptr2 = fopen(temp,"ab+");
//         while( fgets(buf, 1000, fptr1) != NULL )
//         {
//             ++count;
//             if(count==1)
//                 ;
//             else
//             {
//                 fprintf(fptr2,"%s",buf);
//             }
//         }
//         fprintf(fptr2,"%s\n",cmdline);
//         fclose(fptr1);
//         fclose(fptr2);
//         remove(location);
//         rename(temp,location);
//     }    
// }

void d_history(char a[])
{
	int x;
	if(strlen(a)==0)
		x=10;
	else
		x=atoi(a);
	FILE *f=fopen("cmd.txt","r");
	int l=0;
	char *str;
	str=(char *)malloc(1000);
	while(!feof(f))
	{
		fgets(str,1000,f);		
		l++;
	}
	fseek(f,0,SEEK_SET);
	int l1=0;
	while(!feof(f))
	{
		fgets(str,1000,f);
		if(l-l1<=x+1&&l-l1!=1)
			printf("%s",str );
		l1++;
	}
	fclose(f);
}