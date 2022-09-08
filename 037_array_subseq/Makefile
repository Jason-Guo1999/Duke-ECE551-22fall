CFLAGS: -std=gnu99 -pendatic -Wall
test: maxSeq.o test-subseq.o
	gcc -o $@ maxSeq.o test-subseq.o
maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c
test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c

.PHONY: clean
clean:
	rm -f test *.o *.c~ *.h~
