char cwd[1000],pname[100000][50],jobname[100000][50];
char fpname[100000][50],fjobname[100000][50],output_file[1000];
int npro=0,procs[100000],type[100000]={0},flagz=1;
int fnpro=0,fprocs[100000],output_file_len=0;
pid_t pro,pid;