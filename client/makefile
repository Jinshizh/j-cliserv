CC = gcc
EXEC = j-client
OBJS = j-client.o str_cli.o error.o readline.o

$(EXEC): $(OBJS)
	$(CC) -g -o $(EXEC) $(OBJS)
j-client.o:j-client.c ../lib/unp.h
	$(CC) -g -c $<
str_cli.o:str_cli.c ../lib/unp.h ../lib/sum.h
	$(CC) -g -c $<
error.o:error.c ../lib/unp.h
	$(CC) -g -c $<
readline.o:readline.c ../lib/unp.h
	$(CC) -g -c $<
clean:
	rm -rf $(EXEC) *.o
