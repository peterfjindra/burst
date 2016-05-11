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
#include <ctype.h>
#include <getopt.h>

#define BUFSIZE 4096

char* filename(int filenum, char* basename, char* ext);

extern char* optarg;
extern int optind, opterr, optopt;

struct option_ext {
  const char* name;
  int has_arg;
  int* flag;
  int val;
  int val2;
};

struct option_ext longopts[] = {
	{"help",    no_argument, NULL, 'h', 2},
	{"version", no_argument, NULL, 'V', 4},
};

int main(int argc, char* argv[]) {
	int flag = 0;
	int oc;
	int option_result;
	int longindex;
	while ((oc = getopt_long(argc, argv, "hV:", (struct option*) longopts, &longindex)) != -1) {
		switch (oc) {
    		case 'h':
      			fprintf(stderr, "Be sure to specify your inut file and number of lines. e.g.:\n");
			fprintf(stderr, "./burst myfile.txt 400\n");
      			break;
    		case 'V':
      			fprintf(stderr, "You are using version 0.1 of burst.\n");
      			break;
		default:
			break;
		};
		return 0;
	}

	int infd;
	int linecount = 0;
	char *contents = malloc(BUFSIZE);
	char tempcontents[0];
	int maxlines = 0;
	int validnum = 1;

	if(argc > 1){
		infd = open(argv[1], O_RDONLY);
	}
	else{
		puts("please enter a file name as the first argument");
	}
	if(argc > 2){
 		for(int i = 0; i < strlen(argv[2]); i++){
			if(!isdigit(argv[2][i])){
				validnum = 0;
			}
		}
		if(validnum){
			maxlines = atoi(argv[2]);
		}
		else{
			maxlines = 500;
		}
	}
	else{
		maxlines = 500;
	}
	if(infd < 0){
		perror("Input open error");
		return 1;
	}

	char buf[BUFSIZE];

	ssize_t bytesread;
	while((bytesread = read(infd, buf, BUFSIZE)) > 0){
		printf("%d\n", bytesread);//for debugging
		contents = realloc(contents, sizeof(char)*strlen(contents) + BUFSIZE);
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
	char *basefilename = argv[1];
	int lineswritten = 0;
	int multiplier = 1; //number of times the content_perfile has been increased
	int filenum = 1;
	int passed = 0;

        const char delim[2] = ".";
        char *token;
        token = strtok(basefilename, delim);
	char *baseonly = token;
	token = strtok(NULL, delim);
	char *ext = token;

	char *newfilename = filename(filenum, baseonly, ext);
	//passed = 0;
	//i = 0;
	int outfd = STDOUT_FILENO;
	outfd = open(newfilename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	char *content_perfile = malloc(BUFSIZE);


	//the big while that loops through all of contents
	while((tempchar = contents[index]) != EOF && tempchar != '\0'){
		if(lineswritten == maxlines){
			puts("done with 500 lines. next file");
			//write to the file
			write(outfd, content_perfile, strlen(content_perfile));
			memset(content_perfile, 0, sizeof(content_perfile));
			lineswritten = 0;
			++filenum;
			newfilename = filename(filenum, baseonly, ext);
			outfd = open(newfilename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
			multiplier = 1;
		}
		if(tempchar == '\n'){
			++lineswritten;
		}
		if(sizeof(content_perfile) >= BUFSIZE*multiplier){
			content_perfile = realloc(content_perfile, sizeof(char)*(strlen(content_perfile) + BUFSIZE));
			++multiplier;
		}
		content_perfile[strlen(content_perfile)] = tempchar;
		content_perfile[strlen(content_perfile) + 1] = '\0';
		++index;
	}
	//write what's left to our last file
	write(outfd, content_perfile, strlen(content_perfile));
	//free(contents);
	//free(content_perfile);
	return 0;
}

/*
Function for generating a new filename with a number from the base filename.
Takes in the number and the basename and creates the new name.
*/
char* filename(int filenum, char* basename, char* ext){
	char *curfile = malloc(sizeof(char)*(strlen(basename) + 1 + strlen(ext)));
        sprintf(curfile, "%s%d.", basename, filenum);
	strcat(curfile, ext);
	puts(curfile);
	return curfile;
}
