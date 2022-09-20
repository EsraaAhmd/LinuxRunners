#include <stdio.h>
#include <string.h>

int main(void)
{
	 char echoMsg[1000];

	while(1)
	{
		fgets(echoMsg,1000,stdin);
		//fgets(echoMsg,4,stdin);
		if(strcmp(echoMsg,"exit\n")==0)
		{
			printf("Good Bye :) \n");
			break;
		
		}
		else
		{
			printf("%s\n",echoMsg);
			continue;
		}
	}
	return 0;
}


