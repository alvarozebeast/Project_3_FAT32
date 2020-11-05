#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "parser.c"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>




void printInfo(int, int, int, int, int, int, int);
char *get_input(void); 

int main(){

	int fd = open("fat32.img", O_RDONLY);
	// unsigned short (2 bytes)
	// unsigned int (4 bytes)
	unsigned short BytsPerSec = 0, SecPerClus = 0, RsvdSecCnt = 0, NumFATs = 0;
	int RootClus = 0, TotSec32 = 0, FATSz32 = 0;

	lseek(fd, 11, SEEK_CUR);
	read(fd, &BytsPerSec, 2);
	read(fd, &SecPerClus, 1);
	read(fd, &RsvdSecCnt, 2);
	read(fd, &NumFATs, 2);
	lseek(fd, 14, SEEK_CUR);
	read(fd, &TotSec32, 4);
	read(fd, &FATSz32, 4);
	lseek(fd, 4, SEEK_CUR);
	read(fd, &RootClus, 4);


	if (fd == -1)
		printf("Error opening file");
	else{
		while(1){
			
			
			
			printf("$ ");
			char* input = get_input();
			tokenlist *tokens = get_tokens(input);
			
			//printf("Whole input: %s\n", input);
			// for (int i = 0; i < tokens->size; i++) 
			// {
			// 		printf("token %d: (%s)\n", i, tokens->items[i]);
			// }

			if(strcmp(tokens->items[0], "exit") == 0){
				free(input);
				printf("Exiting Program\n");
				break; 
			}
			if(strcmp(input, "info") == 0){

				printInfo(BytsPerSec, SecPerClus, RsvdSecCnt, NumFATs, TotSec32, FATSz32,RootClus); 
			}
			if(strcmp(input, "cd") == 0){
				printf("Change Directory\n");
			}
		
			free(input);
			free_tokens(tokens);
		} // End of While
	} // End of Else

	if (close(fd) < 0)
	{
		exit(1);
	}  
	printf("Closed the fd. \n");

    return 0; 
}

void printInfo(int bps, int spc, int rsc, int noF, int totS, int szF, int rc){

    printf("bytes per sector: %d\nsectors per cluster: %d\nreseverd sector count: %d\nnumber of FATs: %d\ntotal sectors: %d\nFATsize: %d\nroot cluster: %d\n", bps, spc, rsc, noF, totS, szF, rc);

}
