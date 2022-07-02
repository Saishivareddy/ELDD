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
	num[2] = 1;
	fd = open("/dev/add", O_RDWR);
	if(fd == -1)
	{
		perror("Error in opening device file :");
		return -1;
	}
	printf("Enter two numbers to add : ");
	scanf("%d %d", &num[0], &num[1]);
	write(fd,&num, sizeof(num));
	read(fd, &ubuff, sizeof(ubuff));
	printf("Addition of two numbers : %d\n", ubuff); 
	return 0;
}

