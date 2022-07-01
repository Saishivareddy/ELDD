#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd;
	int num1, num2;
	printf("Enter two numbers for addition :");
	scanf("%d %d", &num1,&num2);
	int numbers[2] = {num1, num2};
	fd = open("/dev/write2", O_RDWR);
	if(fd == -1)
	{
		perror("Error in opening device file :");
		return -1;
	}
	int result = write(fd, &numbers, sizeof(numbers));
	if(result == -1)
	{
		perror("Error in Writing :");
		return -1;
	}
	close(fd);
	return 0;
}
