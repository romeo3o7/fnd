#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int createDirctory(const char *s) {
    int exitStatus = mkdir(s,0700);
    if ( exitStatus == 0 ) {
        printf("succesfully created a dir: %s\n" , s);
        return 0;
    }
    else if (errno == EEXIST ) {
        return 0;
    }

    else if (errno == EDQUOT || errno == ENOSPC) {
        fprintf(stderr, "No Space\n");
        return 1;
    }

    else if (errno == ENOENT ) {
        fprintf(stderr ,"parent dirctories {.local AND share} don't exit \n");
        return 1;
    }

    return -1;
}

char * concatStrings(const char *s1 , const char *s2) {
    size_t sizeNedded = snprintf(NULL,0,"%s%s" , s1 , s2);
    char *result = malloc(sizeNedded + 1);
    snprintf(result,sizeNedded + 1,"%s%s" , s1 , s2);
    return result;
}

int readValue(int fd , int *buffer) {
    lseek(fd,0,SEEK_SET);
    return read(fd, buffer, sizeof(int));
}

void writeValue(int fd , int* value) {
    lseek(fd,0,SEEK_SET);
    write(fd , value , sizeof(int) );
}

int cacheCount() {
    int buffer = 0;
    const char *home = getenv("HOME"); // get the home path
    const char *file = "/.local/share/fnd/cacheClearingCounter"; // path where the file should go
    char *dir = concatStrings(home, "/.local/share/fnd");
    if (createDirctory(dir) != 0) return 1;
    char *filePath = concatStrings(home,file);
    int fd = open(filePath, O_CREAT | O_RDWR , 00600); // open the file or create it
    if ( fd < 0 ) {
        perror("failed to open/create file");
        goto exit;
    }
    int values[] = {1,2,3}; // possible values
    if (readValue(fd, &buffer) == 0) { //if file is empty
        writeValue(fd, &values[0]); // write 1 to the file
        goto exit;
    }

    if (buffer == 1) { writeValue(fd, &values[1]); }
    else if (buffer == 2) { writeValue(fd, &values[2]); }
    else if (buffer == 3) { writeValue(fd, &values[0]); }


    exit:
    free(dir);
    free(filePath);
    close(fd);

    return buffer;
}
