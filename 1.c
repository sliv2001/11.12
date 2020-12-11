#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char** argv){
	int fd;
	struct flock f1 = {0};
	if (argc!=2)
		err(-1, "Wrong args");
	if ((fd = open(argv[1], O_RDONLY))<0)
		err(-1, "cant open file");
	if (fcntl(fd, F_GETLK, &f1)<0)
		err(-1, "wrong fcntl");
	while (f1.l_type != F_UNLCK){
		printf("File locked by pid %d with length %ld\n", f1.l_pid, f1.l_len);
		if (fcntl(fd, F_GETLK, &f1)<0)
			err(-1, "wrong fcntl");
	}
	printf("File has no (more) locks\n");
	close(fd);
	return 0;
}
