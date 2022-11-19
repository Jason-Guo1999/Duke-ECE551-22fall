CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2  cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) cyoa-step1.o cyoa-step2.o cyoa-step3.o cyoa-step4.o story.o page.o helperFunction.o myException.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o 
	g++ -o $@ $^
%.o: %.c
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)
	rm -f *.o

cyoa-step1.o: cyoa-step1.cpp
cyoa-step2.o: cyoa-step2.cpp
cyoa-step3.o: cyoa-step3.cpp
cyoa-step4.o: cyoa-step4.cpp
story.o: Story.h
page.o: Page.h
myException.o: myException.h
helperFunction.o: helperFunction.h

