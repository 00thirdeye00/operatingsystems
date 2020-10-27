#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid(),fork()
#include <sys/wait.h> // wait()

#define READ  0
#define WRITE 1

void child_a(int fd[]) {

  // TODO: Add code here.
    close(fd[READ]);
    int dup_chk_a;
    char *const cmd[5] = {"ls", "ls", "-F", "-1", NULL};
    dup_chk_a = dup2(fd[WRITE], WRITE);
    if(dup_chk_a < 0)
        perror("Issue with dup2_a");
    execlp(cmd[0], cmd[1], cmd[2], cmd[3], NULL);
    perror("return from execlp() is not expected(child_a)\n");
    exit(EXIT_FAILURE);
}

void child_b(int fd[]) {

  // TODO: Add code here.
    close(fd[WRITE]);
    int dup_chk_b;
    char *const cmd[2] = {"nl", NULL};
    dup_chk_b = dup2(fd[READ], READ);
    if(dup_chk_b < 0)
        perror("Issue with dup2_b");
    execlp(cmd[0], cmd[0], NULL);
    perror("return from execlp() is not expected(child_b)\n");
    exit(EXIT_FAILURE);
}

int main(void) {
  int fd[2];

  // TODO: Add code here.
    int pid_a, pid_b;
    
    pipe(fd);
    
    pid_a = fork();
    if(pid_a == 0){
        close(fd[0]);
        child_a(fd);  
    }

    pid_b = fork();
    if(pid_b == 0){
        child_b(fd);
    }
    
    close(fd[1]);

    //while(wait(NULL) != -1);
    //while((pid_a != 0) && (pid_b != 0)){
        wait(NULL);
        wait(NULL);
    //}
    
    puts("----main process exited----\n");
}
