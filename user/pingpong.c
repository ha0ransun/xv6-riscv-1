#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  int p[2];
  char *buf[1];

  pipe(p);
  int pid;
  if (fork() == 0) {
  	read(p[0], buf, 1);
  	close(p[0]);
    pid = getpid();
  	printf("%d: received ping\n", pid);
  	write(p[1], "o", 1);
  	close(p[1]);
  	exit(0);
  } else {
  	write(p[1], "i", 1);
  	close(p[1]);
  	read(p[0], buf, 1);
    pid = getpid();
  	printf("%d: received pong\n", pid);
  	close(p[0]);
  	exit(0);
  }
}