#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
/*
int ls(){
  pid_t pid = fork();
  if(pid<0){
    perror("fork made an error");
  }
  if(pid == 0){
    execlp("pwd","pwd",(char *)NULL);
    perror("execlp made an error");
    exit(1);
  }
  else{
    waitpid(pid, NULL, 0);
  }
}
*/

int main() {
    char input[1024];

    while (1) {
        printf("srivya> ");
        fflush(stdout);

        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        char *args[100];
        int argc = 0;

        char *token = strtok(input, " ");

        while (token != NULL) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }

        args[argc] = NULL;

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            execvp(args[0], args);

            perror("execvp");
            exit(1);
        }

        waitpid(pid, NULL, 0);
    }
}

