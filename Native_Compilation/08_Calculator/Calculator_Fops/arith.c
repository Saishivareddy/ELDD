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
	fd = open("/dev/calculator", O_RDWR);
	if(fd == -1)
	{
		perror("Error in opening device file :");
		return -1;
	}
	printf("Enter two numbers : ");
	scanf("%d %d", &num[0], &num[1]);
	printf("Enter the below choice \n\t1. Addition\n\t2. Substraction\n\t3. Multiplication\n\t4. Division\n");
	scanf("%d", &num[2]);
	write(fd,&num, sizeof(num));
	read(fd, &ubuff, sizeof(ubuff));
	printf("Output is : %d\n", ubuff); 
	return 0;
}

