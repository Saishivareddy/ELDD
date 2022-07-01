#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd;
	int addition;
	fd = open("/dev/read", O_RDWR);
	if(fd == -1)
	{
		perror("Error in opening device file :");
		return -1;
	}
	int result = read(fd, &addition, sizeof(addition));
	if(result == -1)
	{
		perror("Error in Writing :");
		return -1;
	}
	close(fd);
	return 0;
}
