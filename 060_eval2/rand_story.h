#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "story-step1.h"
//any functions you want your main to use

// helper function to call perror
void callError(char * message);

// according to different mode, replace template with target word
void replaceTemplate(file * temp, catarray_t * catArray, int flag);

// find  word in target string
char * findWord(char * target, catarray_t * catArray, category_t * previous, int flag);

// validate a line (step2)
void validLineStep2(char * line);

// getcatarray from input file (step2)
catarray_t * getCatArray(FILE * f);

// helperfunction to free (step2)
void helperFreeStep2(catarray_t * catArray);

// get template from input (step1)
file * getTemplate(FILE * f);

// find tempName in catArray (step1)
category_t * findName(catarray_t * catArray, char * tempName);

void addToPrevious(char * target, category_t * previous);

// helperfunction to print (step1)
void helperPrintStep1(file * temp);

// helperfunction to free memory
void helperFreeStep1(file * temp);
#endif
