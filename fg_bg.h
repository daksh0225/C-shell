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
                    printf("bg: Invalid job number\n");
                    fflush(stdout);
                    return;
          }
          
}

void fg(char *b,char *a)
{
          if(strlen(a)==0)
          {
                    printf("fg; too few arguments\n");
                    fflush(stdout);
                    return;
          }
          char *end_a;
          char *token=strtok_r(a," ",&end_a);
          if(strlen(end_a)!=0)
          {
                    printf("fg: too many arguments\n");
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
                    int previous=job;
                    int shpid=getpid();
                    type[procs[i]]=1;
                    int status;
                    signal(SIGTTOU,SIG_IGN);
                    signal(SIGTTIN,SIG_IGN);
                    tcsetpgrp(0,getpgid(procs[i]));
                    strcpy(fjobname[procs[fnpro]],jobname[procs[i]]);
                    strcpy(fpname[procs[fnpro]],jobname[procs[i]]);
                    fnpro++;
                    kill(procs[i],SIGCONT);
                    waitpid(procs[i],&status,WUNTRACED);
                    tcsetpgrp(0,shpid);
                    signal(SIGTTOU,SIG_DFL);
                    signal(SIGTTIN,SIG_DFL);
                    // check_back();
                    // signal(SIGTSTP,handle_sigZ);
                    // signal(SIGINT,handle_sigint);
                    if(WIFSTOPPED(status))
                    {
                              if(procs[i]>0)
                              {
                                        flagz = 1;
                                        int j;
                                        int temp = procs[i];
                                        for(j=0;j<fnpro;j++)
                                        {
                                                  if(fprocs[j]==procs[i])
                                                  {
                                                            flagz= 0;
                                                            kill(temp, 19);
                                                            printf("\n%s\t%s\t[%d]\n","Stopped",fjobname[fprocs[j]],fprocs[j]);
                                                            procs[npro]=procs[j];
                                                            type[procs[npro]]=0;
                                                            strcpy(jobname[procs[npro]],fjobname[fprocs[j]]);
                                                            strcpy(pname[procs[npro]],fjobname[fprocs[j]]);
                                                            npro++;
                                                            break;
                                                  }
                                        }
                                        fflush(stdout);
                                        procs[j] =0;
                              }	
                    }
          }
          else
          {
                    printf("fg: Invalid job number\n");
                    fflush(stdout);
                    return;
          }
}