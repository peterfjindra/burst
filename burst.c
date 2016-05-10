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
#include <string.h>

#define BUFSIZE 4096
#define NUMLINES 500

char* filename(int filenum, char* basename);

int main(int argc, char* argv[]) {

	int infd;
	int linecount = 0;
	int outfd;
	char *contents = malloc((sizeof(char)*(BUFSIZE + 1)));
	char tempcontents[0];

	if(argc > 0){
		infd = open(argv[1], O_RDONLY);
	}

	if(infd < 0){
		perror("Input open error");
		return 1;
	}

	char buf[BUFSIZE];

	ssize_t bytesread;
	while((bytesread = read(infd, buf, BUFSIZE)) > 0){
		printf("%d\n", bytesread);//for debugging
		strcat(contents, buf);
	}

	if(bytesread == 0){
		puts("done reading the file"); //for debugging
	}

	else{
		puts("ERROR");
	}

	//now we read through contents to count 500 newlines and write to a file
	int index = 0;
	int i = 0;
	char tempchar;
	int lineswritten = 0;
	int filenum = 1;
	int passed = 0;
	char *newfilename = filename(filenum, argv[1]);
	puts(newfilename); //for debugging
/*	for(i = 0; i < strlen(argv[1]); i++){
		if(argv[i] != "."){
			if(passed){
				//strcat(ext, argv[i]);
				ext[strlen(ext) - 1] = argv[i];
			}
			else{
				//strcat(justname, argv[i]);
				justname[strlen(justname) - 1] = argv[i];
			}
		}
		else{
			passed = 1;
		}
	}
*/
	//passed = 0;
	//i = 0;

	//while((tempchar = contents[index]) != EOF && tempchar != '\0'){
	//	break;
	//}
	return 0;
}

/*
Function for generating a new filename with a number from the base filename.
Takes in the number and the basename and creates the new name.
*/
char* filename(int filenum, char* basename){
	char *curfile = malloc(sizeof(char)*(strlen(basename) + 1));
        const char delim[2] = ".";
        char *token;

        token = strtok(basename, delim);
        sprintf(curfile, "%s%d.", token, filenum);
        while((token = strtok(NULL, delim)) != NULL){
                strcat(curfile, token);
        }

	return curfile;
}
