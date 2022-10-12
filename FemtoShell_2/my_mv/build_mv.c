#include <stdio.h>


int main(int argc, char *argv[])
{
	if (argc !=3)
	{
		printf("error using this command...\n");
		return -1;
	}
	else
	{
		rename(argv[1],argv[2]);
		return 0;
	}
}

