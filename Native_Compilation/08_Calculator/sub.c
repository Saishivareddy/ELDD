#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

unsigned int ubuff;

int main()
{
	int fd;
	int num[3];
	num[2] = 2;
	fd = open("/dev/sub", O_RDWR);
	if(fd == -1)
	{
		perror("Error in opening device file :");
		return -1;
	}
	printf("Enter two numbers to subtract : ");
	scanf("%d %d", &num[0], &num[1]);
	write(fd,&num, sizeof(num));
	read(fd, &ubuff, sizeof(ubuff));
	printf("Subtraction of two numbers : %d\n", ubuff); 
	return 0;
}

