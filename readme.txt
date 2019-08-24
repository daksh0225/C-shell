1 shell.c:
	main() : main() function is just used for taking user input and check which command the user entered in main function and then calls different function and then calling the necessary function

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2 prompt.h:
	prompt(): This function repeatedly prints prompt

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3 cd.h:
	cd(): This changes current working directory when user enters cd command

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

4 pwd.h:
	pwd(): shows path of current working directory

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

5 echo.h:
	echo(): prints the input given by user to stdout

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

6 ls.h:
	ls(): decides what flag is given by user
	lsl(): used for printing the output for commands ls -l and ls -la

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

7 pinfo.h:
	pinfo(): used to execute pinfo command which prints the process information of given pid

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

8 history.h:
	w_history(): used to store commands from queue into file cmd.txt
	d_history(): used to previously entered commands

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

9 exec.h:
	exec(): used to execute the command given by the user (commands other than pwd,cd,echo,ls,pinfo)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

10 watch.h:
	keyDown(): used to check whether a keyboard interrut was given or not
	watch(): used to decide whether argument given to nightwatch was interrupt or dirty.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

11 backchk.h:
	isback(): used to check whether given command is to be run in background or foreground.