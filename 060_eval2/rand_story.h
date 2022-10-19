#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include "story-step1.h"
//any functions you want your main to use

void callError(char * message);
void replaceTemplate(file * temp, int flag);
char * findWord(char * target, int flag);
#endif
