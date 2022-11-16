CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 #cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) Page.h Story.h myException.h helperFunction.h
all: $(PROGS)
story-step%: story-step%.o Page.o Story.o myException.o helperFunction.o
	gcc -o $@ $^
%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

Page.o: Page.h
Story.o: Story.h
myException.o: myException.h
helperFunction.o: helperFunction.h

