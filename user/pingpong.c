#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]){

    int p1[2];
    int p2[2];

    pipe(p1);
    pipe(p2);
    int pid  = fork();
    if(pid == 0){
        char buffer[1];
        close(p1[1]);
        close(p2[0]);

        
        // while(1){
            if(read(p1[0],buffer,1)>0){
                printf("%d: received ping\n",getpid());
                // break;
            }
        // }

        write(p2[1],"x",1);
        // printf("child write %d",n);
        close(p1[0]);
        close(p2[1]);
        exit(0);

    } else {
        char buffer[1];
        close(p1[0]);
        close(p2[1]);

        write(p1[1],"x",1);
        // printf("parent write %d",n);
        // while(1){
            if(read(p2[0],buffer,1)>0){
                printf("%d: received pong\n",getpid());
                // break;
            }
        // }

        close(p2[0]);
        close(p1[1]);
        // wait(0);
        exit(0);
    }

}