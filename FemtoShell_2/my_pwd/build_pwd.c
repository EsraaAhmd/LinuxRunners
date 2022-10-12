#include <stdio.h>
#include "string.h"
#include <unistd.h>

#define PATH_MAX_SIZE 200

int main(int argc)
{
	char path[PATH_MAX_SIZE];
	char errMsg[]={"Too many parameters...\n"};
	int errMsgSize=sizeof(errMsg);	
	if (argc>=2)
	{
		//printf("Too many parameters..!");
		write(STDOUT_FILENO, errMsg,errMsgSize); 
	}
	else if(argc == 1)
	{
		
		getcwd(path,PATH_MAX_SIZE);
		write(STDOUT_FILENO,path,PATH_MAX_SIZE);
		write(STDOUT_FILENO,"\n",1); //print new line

		//printf("%s\n",getcwd(path,PATH_MAX_SIZE));
	}
	else
	{
		//no action needed
	}

	return 0;
}
