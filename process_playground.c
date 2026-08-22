#include <stdio.h>
#include <unistd.h>

int func(){
  pid_t pid=fork();
  if(pid==0){
    int child_pid=getpid();
    int parent_pid=getppid();
    printf("This is the child function \n");
    printf("Child pid : %d \n", child_pid);
    printf("Parent pid : %d \n", parent_pid);
  }
  else if(pid>0){
    printf("this is the parent function");
    int child_pid=getpid();
    int parent_pid=getppid();
    printf("Child pid : %d \n", child_pid);
    printf("Parent pid : %d \n", parent_pid);
  }
  else{
    printf("error making children");
  }
}

int main(){
  func();
}
