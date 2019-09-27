#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void setE(char *a)
{
          if(strlen(a)==0)
          {
                    printf("setenv: too few arguments\n");
                    fflush(stdout);
                    return;
          }
          char *end_a;
          char  *token=strtok_r(a," ",&end_a);
          if(strlen(end_a)==0)
                    putenv(token);
          else 
          {
                    char *var=token,*val;
                    int cnt=0,flag=0;
                    while(token!=NULL)
                    {
                              if(cnt>1)
                              {
                                        printf("setenv: too many arguments\n");
                                        fflush(stdout);
                                        return;
                              }         
                              else
                              {
                                        val=token;
                              }
                              token=strtok_r(NULL," ",&end_a);                              
                              cnt++;
                    }
                    setenv(var,val,1);
          }
}
void unsetE(char *a)
{
          if(strlen(a)==0)
          {
                    printf("unsetenv: too few arguments\n");
                    fflush(stdout);
                    return;                    
          }
          char *end_a;
          char *token=strtok_r(a," ",&end_a);
          if(strlen(end_a)!=0)
          {
                    printf("unsetenv: too many arguments\n");
                    fflush(stdout);
                    return;                    
          }         
          unsetenv(token);
}
