CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2  cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) Story.o Page.o Choice.o helperFunction.o myException.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o
	g++ $(CPPFLAGS) -o $@ $^
%.o: %.c
	g++ $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

Story.o: Story.hpp 
Page.o: Page.hpp
Choice.o: Choice.hpp 
myException.o: myException.hpp
helperFunction.o: helperFunction.hpp

