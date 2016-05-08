/*

	burst.c

	A program for splitting up a file.

	Peter Jindra
	peterfjindra@gmail.com
	pfj2@zips.uakron.edu

*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>

#define BUFSIZE 4096

int main(int argc, char* argv[]) {

	int infd;

	if(argc > 0){
		infd = open(argv[1], O_RDONLY);
	}

	if(infd < 0){
		perror("Input open error");
		return 1;
	}

	char buf[BUFSIZE];

	ssize_t bytesread;
	while(bytesread = read(infd, buf, BUFSIZE) > 0);

	if(bytesread == 0){
		puts("done reading the file");
	}

	else{
		puts("ERROR");
	}


	return 0;
}
