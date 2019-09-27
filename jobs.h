void jobs(char *a)
{
     if(strlen(a)!=0)
     {
               printf("jobs: too many arguments");
               fflush(stdout);
               return ;
     }

     int i,cnt=0;
     for(i=0;i<npro;i++)
     {
          if(type[procs[i]]==0 && strlen(jobname[procs[i]])!=0)
          {
                    cnt++;
                    char file[1000],state,comm[100],cond[50];
                    int unused;
                    sprintf(file,"/proc/%d/stat",procs[i]);
                    FILE *f=fopen(file,"r");
                    if(f)
                    {
                              fscanf(f,"%d %s %c",&unused,comm,&state);
                    }
                    if(state=='T')
                              strcpy(cond,"Stopped");
                    else
                              strcpy(cond,"Running");
                    printf("[%d] %s %s [%d]\n",cnt,cond,jobname[procs[i]],procs[i]);
                    fflush(stdout);
          }
     }
     if(cnt==0)
          npro=0;
}

void kjob(char *a)
{
     if(strlen(a)==0)
     {
          printf("kjob: too few arguments");
          fflush(stdout);
          return;
     }
     char *end_a;
     char *token=strtok_r(a," ",&end_a);
     int jobn=atoi(token);
     if(strlen(end_a)==0)
     {
          printf("kjob: too few arguments");
          fflush(stdout);
          return;
     }
     token=strtok_r(NULL," ",&end_a);
     if(strlen(end_a)!=0)
     {
          printf("kjob: too many arguments");
          fflush(stdout);
          return;
     }
     int ksig=atoi(token);
     if(!(ksig>=1 && ksig<=31))
     {
          printf("kjob; Invalid signal number");
          fflush(stdout);
          return;
     }
     int i,cnt=0,flag=0;
     for(i=0;i<npro;i++)
     {
          if(type[procs[i]]==0 && strlen(jobname[procs[i]])!=0)
          {
               cnt++;
               if(cnt==jobn)
               {
                    flag=1;
                    break;
               }
               else
               {
                    flag=0;
               }                    
          }
     }
     if(flag==0)
          printf("kjob: Invalid job number");
     else
          kill(procs[i],ksig);    
     fflush(stdout);
}

void overkill(char *a)
{
     if(strlen(a)!=0)
     {
          printf("overkill: too many arguments\n");
          fflush(stdout);
          return;
     }
     int i,cnt=0,flag=0;
     for(i=0;i<npro;i++)
     {
          if(type[procs[i]]==0 && strlen(jobname[procs[i]])!=0)
          {
               kill(procs[i],9);
          }
     }    
}