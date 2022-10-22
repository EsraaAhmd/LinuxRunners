#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define	MAX_SIZE_CMD	256
#define	MAX_SIZE_ARG	16

//"escape sequence" to clear the shell
//"\033" stands for ESC
//"\033[H" moves the cursor to the mos top left point
//"\033[J" clears the screen from the position of the cursor to the end
#define clear() printf("\033[H\033[J")


char cmd[MAX_SIZE_CMD];  // string holder for the command
char *argv[MAX_SIZE_ARG];  // an array for command and arguments
int pid;	// global variable for the child process ID
char i;		// global for loop counter


/****************************************************************************
 * \Syntax          : void Shell_voidInit()
 * \Description     : Function to initialize the shell and greet the user.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *****************************************************************************/
void Shell_voidInit()
{
        clear();
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("                ******************************************\n");
        printf("                ***********Hello From My Shell************\n");
        printf("                *********Feel Free To Use It :D***********\n");
        printf("\n");
        printf("                ******************************************\n");
        sleep(3);
        clear();
}

/****************************************************************************
 * \Syntax          : void Shell_voidPWD()
 * \Description     : Function to print the user and the working directory.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *****************************************************************************/
void Shell_voidPWD()
{
        char cwd[1024];
        char *username =getenv("USER");
        //Set the color to Bold Light Magneta
        printf("\033[1;95m%s@%s\033[0m",username,username);
        printf(":");
        getcwd(cwd,sizeof(cwd));
        //Set the color to Bold Light cyan      
        printf("\033[1;96m~%s\033[0m",cwd);
        printf("$ ");

}


/****************************************************************************
 * \Syntax          : void Shell_voidTokenizer()
 * \Description     : Function to tokenize the input string.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *****************************************************************************/
void Shell_voidTokenizer()
{
	// split string into argv
	char *ptr;
	i = 0;
	ptr = strtok(cmd, " ");
	while(ptr != NULL)
	{
		//printf("%s\n", ptr);
		argv[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}

	// check for "&"
	if(!strcmp("&", argv[i-1]))
	{
		argv[i-1] = NULL;
		argv[i] = "&";
	}
	else
	{
		argv[i] = NULL;
	}
	
}



/****************************************************************************
 * \Syntax          : void Shell_voidGetCMD()
 * \Description     : Function to get the cmd as a string.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *****************************************************************************/
void Shell_voidGetCMD()
{
	// get command from user
	//printf("Shell>\t");
	Shell_voidPWD();
	fgets(cmd, MAX_SIZE_CMD, stdin);
	// remove trailing newline
	if ((strlen(cmd) > 0) && (cmd[strlen (cmd) - 1] == '\n'))
        	cmd[strlen (cmd) - 1] = '\0';
	//printf("%s\n", cmd);
}


void Shell_voidStart()
{
	Shell_voidInit();
	while(1){
		// get the command from user
		Shell_voidGetCMD();

		// bypass empty commands
		if(!strcmp("", cmd))
		        continue;

		// check for "exit" command
                if(!strcmp("exit", cmd)) 
			break;

		// fit the command into *argv[]
		Shell_voidTokenizer();

		// fork and execute the command
		pid = fork();
		if(-1 == pid)
		{
			printf("failed to create a child\n");
		}
		else if(0 == pid)
		{
			// printf("hello from child\n");
			// execute a command
			execvp(argv[0], argv);
		}
		else
		{
			// printf("hello from parent\n");
			// wait for the command to finish if "&" is not present
			if(NULL == argv[i]) 
				waitpid(pid, NULL, 0);
		}
	}
}



void log_handle(int sig)
{

	FILE *pFile;
        pFile = fopen("log.txt", "a");
        if(pFile==NULL) perror("Error opening file.");
        else fprintf(pFile, "[LOG] child proccess terminated.\n");
        fclose(pFile);
}

int main(void)
{
	// tie the handler to the SGNCHLD signal
	signal(SIGCHLD, log_handle);

	// start the shell
	Shell_voidStart();

	return 0;

}

