#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "myfs.h"

#define MAX_INODES 16
#define MAX_BLOCKS 16
#define MAX_DIRS 8
#define ROOT_INODE 0

#define MAXLINE 128
#define MAXPATH 128

// Inode table 
struct inode itable[MAX_INODES];

/* The data blocks are implemented as an 2d array of dir_entry structs.
 * You can think of it as an array of blocks where each block is an array of 
 * directory entries.
 */
struct dir_entry blocks[MAX_BLOCKS][MAX_DIRS];

/* Populate itable and blocks from the open file handle fp
 * You can expect that the input file data format is correct 
 *
 * Note: this is kind of a hack to find a quick way to represent
 * the file system and read it into memory.  It is not elegant or particularly
 * readable. It also takes advantage of the fact that global variables are 
 * initialized to 0.
 */
void populate_fs( FILE *fp) {
    int i = 0;

    // read the inode table
    while(fscanf(fp, "[ %c, %d ] ", &itable[i].type, &itable[i].block_no) > 0) {
        i++;
    }

    // read the blocks
    char line[MAXLINE]; 
    i = 0;  // block index
    int j = 0;
    while((fgets(line, MAXLINE, fp)) != NULL) {
        line[strlen(line) - 1] = '\0';
        
        if(line[0] == '\0')  {
            i++;
            j = 0;
        } else {
            char *ptr = strtok(line, " ");

            strncpy(blocks[i][j].name, line, 8);
            ptr = strtok(NULL, " ");
            blocks[i][j].inode = (int)strtod(ptr, NULL);
            j++;
        }
    }
}


/* Returns the inode number for the element at the end of the path
 * if it exists.  If there is any error, return -1.
 * Possible errors include:
 *   - The path is not an absolute path
 *   - An element on the path cannot be found
 */
int path_lookup(char *path) {
    if(path[0] != '/') {
        fprintf(stderr, "Not an absolute path\n");
        return -1;
    } 

	// TODO: complete this function and any helper functions

    return -1;
}


int main(int argc, char **argv) {

    if(argc != 3) {
        fprintf(stderr, "USAGE: myfs fs_file path_to_search\n");
        exit(1);
    }
    /* first argument is a path to a text file containing a 
     * a text representation of a file system.  
     * You can expect that lines are terminated with \n.
     */
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("fopen");
        exit(1);
    }
    // Load the text file into the inodes and blocks data structures
    populate_fs(fp);

    int inode_no = path_lookup(argv[2]);

    if(inode_no == -1){
        printf("Path not found: %s\n", argv[2]);
    } else {
        printf("Inode is %d\n", inode_no);
    }
    return 0;
}
