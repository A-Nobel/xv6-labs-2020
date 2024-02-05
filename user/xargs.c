#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    char buf[512];
    char data;
    int count = 0;
    char *args[100];
    int init_arg_count = argc -2;
    args[0] = argv[1];
    for(int i = 2;i<argc;i++){
        args[i-1]=argv[i];
    }
    int args_count = init_arg_count;

char *p = buf;
    while(read(0,&data,1)==1){
        

if(data!= '\n' && data != ' '){
    buf[count++] = data;
    // printf("%c",data);
}
        else if(data == ' '){
            buf[count++] = 0;


                // printf("%s buf\n",buf);
    args[++args_count] = p;
    p+=count;
    // printf("%s args0 %s argsbuff",args[0],args[args_count]);

            
        } else{
            buf[count++] = 0;


                // printf("%s buf\n",buf);
    args[++args_count] = p;
    p+=count;
    args[++args_count] = 0;
    // printf("%s args0 %s argsbuff",args[0],args[args_count]);


                // args[++args_count] = 0;
            int pid =fork();
            
            if(pid==0){
                exec(argv[1],args);
                exit(0);
            } else{
                args_count = init_arg_count;
                wait(0);

            }
        }
    }
    exit(0);
}