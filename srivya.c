
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


typedef int (*builtin_func)(char **args);


struct builtin {
    char *name;
    builtin_func func;
};




int builtin_cd(char **args) {

    if (args[1] == NULL) {

        char *home = getenv("HOME");

        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }

        if (chdir(home) != 0) {
            perror("cd");
            return 1;
        }

        return 0;
    }

    if (args[2] != NULL) {
        fprintf(stderr, "cd: too many arguments\n");
        return 1;
    }

  
    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}



struct builtin builtins[] = {
    {"cd", builtin_cd}
};




builtin_func find_builtin(char *name) {

    int num_builtins = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < num_builtins; i++) {

        if (strcmp(name, builtins[i].name) == 0) {
            return builtins[i].func;
        }
    }

    return NULL;
}



int main() {

    char input[1024];

    while (1) {

        printf("srivvya> ");
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

        char *output_file = NULL; 
        for (int i = 0; i < argc; i++) { 
          if (strcmp(args[i], ">") == 0) {
            if (i + 1 >= argc) { 
              fprintf(stderr, "syntax error: expected filename after >\n"); 
              continue; 
            } 
            output_file = args[i + 1]; 
            args[i] = NULL; 
            argc = i; 
            break; 
          }
        }
        builtin_func func = find_builtin(args[0]);

        if (func != NULL) {

            func(args);

            continue;
        }


        // Otherwise, execute it as an external command
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }


        if (pid == 0) {
          if (output_file != NULL) { 
              int fd = open( output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644 );
              if (fd < 0) { 
                perror("open"); 
                exit(1); 
              } 
              if (dup2(fd, STDOUT_FILENO) < 0) { 
                perror("dup2"); 
                close(fd); 
                exit(1); 
              } 
              close(fd); 
            }
  
            execvp(args[0], args);

            perror("execvp");
            exit(1);
        }

        waitpid(pid, NULL, 0);
    }

    return 0;
}


