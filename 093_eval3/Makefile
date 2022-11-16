CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2  #cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa-step1.o story.o page.o helperFunction.o myException.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o 
	g++ -o $@ $^
%.o: %.c
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

cyoa-step1.o: cyoa-step1.cpp
cyoa-step2.o: cyoa-step2.cpp
story.o: Story.h
page.o: Page.h
myException.o: myException.h
helperFunction.o: helperFunction.h

