#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "story-step1.h"
//any functions you want your main to use

// helper function to call perror
void callError(char * message);
// according to different mode, replace template with target word
void replaceTemplate(file * temp, int flag);
// find  word in target string
char * findWord(char * target, int flag);
// find tempName in catArray
category_t * findName(catarray_t * catArray, char * tempName);
#endif
