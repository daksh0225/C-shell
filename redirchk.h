int out_redir(char *cmd)
{
	int i, flag = 1;
	for(i=0; i<strlen(cmd); i++)
		if(cmd[i] == '>')
			break;
	if(i == strlen(cmd))
		return 0;
	if(i == strlen(cmd) -1)
		return 1;
	i++;
	if(cmd[i] == '>')
	{	
		flag = 2;
		i++;
	}
	while(i < strlen(cmd) && cmd[i] == ' ')
		i++;
	while(i < strlen(cmd) && cmd[i] != ' ')
		output_file[output_file_len++] = cmd[i++];
	output_file[output_file_len] = '\0';
	return flag;
}

int in_redir(char *cmd)
{
	int i, flag = 1;
	for(i=0; i<strlen(cmd); i++)
		if(cmd[i] == '<')
			break;
	if(i == strlen(cmd))
		return 0;
	if(i == strlen(cmd) -1)
		return 1;
	i++;
	// if(cmd[i] == '<')
	// {	
	// 	flag = 2;
	// 	i++;
	// }
	while(i < strlen(cmd) && cmd[i] == ' ')
		i++;
	while(i < strlen(cmd) && cmd[i] != ' ')
		output_file[output_file_len++] = cmd[i++];
	output_file[output_file_len] = '\0';
	return flag;
}