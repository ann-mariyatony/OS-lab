#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/types.h> 

int main() {
    pid_t pid; 
    pid = fork();   

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
              printf("24SJPCCSL407 ");
        
    } 
    else {
     wait(NULL);  // Wait for child to complete
        printf("Operating Systems Lab\n");  // Parent process
    }
    return 0;
}
