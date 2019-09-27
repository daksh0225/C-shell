void bg(char *a)
{
          if(strlen(a)==0)
          {
                    printf("bg: too few arguments\n");
                    fflush(stdout);
                    return;
          }
          char *end_a;
          char *token=strtok_r(a," ",&end_a);
          if(strlen(end_a)!=0)
          {
                    printf("bg: too many arguments\n");
                    fflush(stdout);
                    return;
          }
          int job=atoi(token);
          int i,cnt=0,flag=0;
          for(i=0;i<npro;i++)
          {
                    if(type[procs[i]]==0 && strlen(jobname[procs[i]])!=0)
                    {
                              cnt++;
                              if(cnt==job)
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
          if(flag==1)
          {
                    kill(procs[i],18);
          }
          else
          {
                    printf("bg: Invalid job number");
                    fflush(stdout);
                    return;
          }
          
}