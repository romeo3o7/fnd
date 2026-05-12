#include <fcntl.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int task(char*path,char *argument[]) {
    pid_t childProcess = fork();
	if (childProcess == 0) {
	    execvp(path, argument); // here child is gone if succesful
	    perror("child failed, execv stage\n"); // this part is only reached when the child fails
	    exit(EXIT_FAILURE);
	} else if (childProcess == -1) {
	    fprintf(stderr, "child failed , fork stage\n");
	    return -1;
	    }
	// parent
	int childProcessStatus;
	waitpid(childProcess, &childProcessStatus , 0); // wait for the child to run and read its exit status
	if (WIFEXITED(childProcessStatus)) { // if the child exited normally
	    return WEXITSTATUS(childProcessStatus); //return its status to be read in main
	}
	if (WIFSIGNALED(childProcessStatus)) { // if child interputted
	    fprintf(stderr, "child killed by signal %d\n", WTERMSIG(childProcessStatus));
	    return -1;
	}
	return -1;
}
int silentTask(char *path, char *args[]) {
    pid_t child = fork();
    if (child == 0) {
        int devNull = open("/dev/null", O_WRONLY);
        dup2(devNull, STDOUT_FILENO);
        dup2(devNull, STDERR_FILENO);
        close(devNull);
        execvp(path, args);
        exit(EXIT_FAILURE);
    }
    if (child == -1) return -1;
    int status;
    waitpid(child, &status, 0);
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    return -1;
}
