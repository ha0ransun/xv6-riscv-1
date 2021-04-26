#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
prime() {
	int p, n;
	read(0, &p, 1);
	printf("prime %d\n", p);
	while (read(0, &n, 1)) {
		if (n % p != 0) {
			int fd[2];
			pipe(fd);
			if (fork() == 0) {
				close(0);
				dup(fd[0]);
				close(fd[0]);
				close(fd[1]);
				prime();
			} else {
				close(fd[0]);
				write(fd[1], &n, 1);
				while (read(0, &n, 1)) {
					if (n % p != 0)
						write(fd[1], &n, 1);
				}
				close(fd[1]);
				close(0);
				wait((int*) 0);
				break;
			}
		}
	}
	exit(0);
}

void
main() {
	int fd[2], m;
	pipe(fd);
	close(0);
	dup(fd[0]);
	close(fd[0]);

	if (fork() == 0){
		close(fd[1]);
		prime();
	}
	else {
		close(fd[0]);
		for (m = 2; m < 36; ++m) {
			write(fd[1], &m, 1);
		}
		close(fd[1]);
		wait((int*) 0);
		exit(0);
	}
}



