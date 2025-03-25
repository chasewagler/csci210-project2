#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]) { 
	//check if dir is empty
	if (strcmp(pathName, "/") == 0) {
		printf("MKDIR ERROR: no valid path provided\n");
		return;
	}

        struct NODE* currentChild = cwd->childPtr;
	
	//check for duplicate dir
        while (currentChild != NULL) {
        	if (strcmp(currentChild->name, pathName) == 0) {
        		printf("MKDIR ERROR: directory %s already exists\n", pathName);
        		return;
        	}
        currentChild = currentChild->siblingPtr;
    	}

	//new node
    	struct NODE* newPath = (struct NODE*) malloc(sizeof(struct NODE));

	newPath->childPtr = NULL;
    	newPath->fileType = 'D';
    	strncpy(newPath->name, pathName, 64);
    	newPath->parentPtr = cwd;
    	newPath->siblingPtr = NULL;

    	//insert node
    	if (cwd->childPtr == NULL) {
        	cwd->childPtr = newPath;
    	} else {
        	struct NODE* temp = cwd->childPtr;
        	while (temp->siblingPtr != NULL) {
            		temp = temp->siblingPtr;
        	}
        	temp->siblingPtr = newPath;
    	}

    	printf("MKDIR SUCCESS: directory %s successfully created\n", pathName);
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName) {
	struct NODE* currentNode = (pathName[0] == '/') ? root : cwd;
	//struct NODE* currentNode = cwd; // if it's a relative path, or root if it's an absolute path
	char* tempPathName = strdup(pathName);
	char * currentDirName = strtok(tempPathName,"/"); // refer to the tokenization example at /u/pa/nb/tolgacan/210/spring25/strtokex.c
	while (currentDirName != NULL) { // while there are still tokens
		struct NODE* child = currentNode->childPtr;
		while (child != NULL) {
			if (strcmp(child->name,currentDirName)!=0) {
				child = child->siblingPtr;
			}
			else break; // directory found among the children of currentNode
		}
		if (child == NULL) // not found
		{
			printf("ERROR: directory %s does not exist\n", dirName);
			free(tempPathName);
			return NULL;
		}
		currentNode = child; // we traverse the tree to the next depth with this assignment
		currentDirName = strtok(NULL,"/"); // now in the next iteration look for the next directory name
	}
	free(tempPathName);
	// currentNode at this point will point to the parent of "baseName" which is what we want
	return currentNode;
}

//compile with `gcc *.c *.o -o proj_2`
