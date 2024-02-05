#include "kernel/types.h"
#include "user/user.h"

// fork()在父进程中返回子进程的PID
// 在子进程中返回0
int
main(int argc, char *argv[]){
int pid = fork();
if(pid > 0) {
    printf("parent: child=%d\n", pid);
    pid = wait((int *) 0);
    printf("child %d is done\n", pid);
} else if(pid == 0) {
    sleep(5);
    printf("child: exiting\n");
    exit(0);
} else {
    printf("fork error\n");
    exit(1);
}
exit(0);
}
