#include "types.h"
#include <stdlib.h>
#include <string.h>

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){

	struct NODE* newPath = (struct NODE*) malloc(sizeof(struct NODE));
	newPath->childPtr = NULL;
	newPath->fileType = 'd';
	strncpy(newPath->name, 64, pathName);
	newPath->parentPtr = cwd;
	if (cwd->siblingPtr) {
		newPath->siblingPtr = cwd->siblingPtr;
	} else {
		newPath->siblingPtr = NULL;
	}

	cwd->childPtr = newPath;

	return;
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){
	struct NODE* currentNode = cwd; // if it's a relative path, or root if it's an absolute path
	char * currentDirName = strtok(pathName,"/"); // refer to the tokenization example at /u/pa/nb/tolgacan/210/spring25/strtokex.c
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
			printf("Directory does not exist");
			return NULL;
		}
		currentNode = child; // we traverse the tree to the next depth with this assignment
		currentDirName = strtok(NULL,"/"); // now in the next iteration look for the next directory name
	}
		return NULL;
}

//compile with `gcc -g -o main main.c` in project folder
