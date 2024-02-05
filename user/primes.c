#include "kernel/types.h"
#include "user/user.h"

void primes(int lpipe[2])
{
    close(lpipe[1]);
    int data;
    int first = 0;
    int p[2];
    pipe(p);
    // printf("stuck at read");
    int n = read(lpipe[0], &data, sizeof(int));
    if (n == 0)
    {
        // printf("over!! \n");
        exit(0);
    }

    if (n == sizeof(int))
    {
        first = data;
        printf("prime %d\n", first);
    }

    int pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        primes(p);
        close(p[0]);
    }
    else
    {
        close(lpipe[1]);
        close(p[0]);
        int count = 0;
        while (read(lpipe[0], &data, sizeof(int)) == sizeof(int))
        {
            if (data % first != 0)
            {
                count++;
                write(p[1], &data, sizeof(int));
                // printf("%d count\n",count);
            }
        }
        close(p[1]);
        close(lpipe[0]);
        // printf("%d count\n",count);

        if (count == 0)
            exit(0);

        wait(0);
    }
}

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        primes(p);
        close(p[0]);
    }
    else
    {
        close(p[0]);
        for (int i = 2; i <= 35; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }

    exit(0);
}