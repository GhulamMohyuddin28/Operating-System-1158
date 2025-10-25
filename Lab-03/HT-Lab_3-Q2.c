#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process runs the "date" command
        execlp("date", "date", NULL);
    }
    else if (pid > 0)
    {
        // Parent waits for the child process to finish
        wait(NULL);
        printf("Child finished\n");
    }
    else
    {
        // Error handling
        perror("fork failed");
    }
    return 0;
}