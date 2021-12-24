CFLAGS = -Wall -pthread -lm
CC = gcc -std=c99
ECHO = echo "going to compile for target $@"
PROG = ex3_q1
GIVEN = ex3_q1_given

all: $(PROG) test

$(PROG).o: $(PROG).c $(PROG).h
	@$(ECHO)
	$(CC) $(CFLAGS) -c $(PROG).c -o $(PROG).o

$(GIVEN).o: $(GIVEN).c $(GIVEN).h
	@$(ECHO)
	$(CC) $(CFLAGS) -c $(GIVEN).c -o $(GIVEN).o

$(PROG): $(PROG).o $(GIVEN).o
	$(CC) $(CFLAGS) $(GIVEN).o $(PROG).o -o $(PROG)

test: $(PROG)
	./$(PROG) > out.log 2> err.log

clean:
	rm -rf $(PROG) *.log *.o *.tx