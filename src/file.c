#include "../include/file.h"

const char *welcomeMsg = "!THIS IS READ ONLY FILE! \n\nhello! this file is a storage used for fnd cache counter\nthe Value : ";

int cacheCount() {
    char values[] = {'1','2','3','4'}; // possible values
    char buffer = '0';
    int returnValue = 0;

    const char *home = getenv("HOME"); // get the home path
    const char *file = "/.cache/fnd/cacheClearingCounter"; // path where the file should go

    char *dir = concatStrings(home, "/.cache/fnd"); // create a full path to the directory
    if (createDirctory(dir) != 0) { free(dir); return -1; } // if creating the dir fails return -1
    char *filePath = concatStrings(home,file);                // create the string for the full path

    int fd = open(filePath, O_CREAT | O_RDWR , 00600); // open the file fd or create it
    if ( fd < 0 ) {
        perror("failed to open/create file");
        returnValue = -1;
        goto exit;
    }

    unsigned int sizeNeeded = snprintf(NULL, 0, "%s" , welcomeMsg );

    struct stat statbuff;
    fstat(fd , &statbuff);

    if (statbuff.st_size == 0) {   // if file is empty,
	write(fd, welcomeMsg , sizeNeeded);
	write(fd, &values[0] , 1);
	goto exit;
    } else {
	lseek(fd, sizeNeeded , SEEK_SET); // go to after the string
	read(fd , &buffer , 1);
    	}

    writeValue(fd , buffer , sizeNeeded , values);
    returnValue = buffer - '0';

    exit:
    free(dir);
    free(filePath);
    if (fd >= 0)close(fd);
    return returnValue;
}

int writeValue(int fd , char buffer , unsigned int size , char *values) {
    lseek(fd, size, SEEK_SET);
    switch (buffer) {
        case'1':
        if (write(fd, &values[1] ,sizeof buffer) < 0 ) return -1;
        break;
        case'2':
        if (write(fd, &values[2] ,sizeof buffer) < 0 ) return -1;
        break;
        case'3':
        if (write(fd, &values[3] ,sizeof buffer) < 0 ) return -1;
        break;
        case'4':
        if (write(fd, &values[0] ,sizeof buffer) < 0 ) return -1;
        break;
        default:
        if (write(fd, &values[0] ,sizeof buffer) < 0 ) return -1;
        break;
    }
    return 0;
}

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
