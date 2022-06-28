#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned char read_buff[1024];
unsigned char write_buff[1024];

int main()
{
	int fd;
	int option;
	fd = open("/dev/mydevice", O_RDWR);
	if(fd == -1)
	{
		perror("Cannot open the device file\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		printf("****Please Enter the Option****\n");
		printf("	1. Write	\n");
		printf("	2. Read		\n");
		printf("	3. Exit		\n");
		scanf("%d", &option);
		printf("Your option is %d\n", option);
		switch(option)
		{
			case 1:
				printf("Enter the string to write into driver\n");
				scanf("%s", write_buff);
				printf("Data Writing....");
				write(fd, write_buff, strlen(write_buff)+1);
				printf("Done!\n");
				break;
			case 2:
				printf("Data Reading....");
				read(fd, read_buff, 1024);
				printf("Done!\n");
				printf("Data = %s\n", read_buff);
				break;
			case 3:
				close(fd);
				exit(1);
				break;
			default:
				printf("Enter the valid option\n");
				break;
		}
	}

	return 0;
}
