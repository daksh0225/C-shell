int isredir(char a[])
{
	if(strlen(a)==0)
		return 0;
	else
	{
		int i;
		for(i=0;i<strlen(a);i++)
		{
			if(a[i]=='<'||a[i]=='>')
				return 1;
		}
	}
	return 0;
}