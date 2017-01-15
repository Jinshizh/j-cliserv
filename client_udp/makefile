CC = gcc
EXEC = j-client-udp
OBJS = j-client-udp.o str_cli_udp.o error.o

$(EXEC): $(OBJS)
	$(CC) -g -o $(EXEC) $(OBJS)
j-client-udp.o:j-client-udp.c ../lib/unp.h
	$(CC) -g -c $<
str_cli_udp.o:str_cli_udp.c ../lib/unp.h
	$(CC) -g -c $<
error.o:error.c ../lib/unp.h
	$(CC) -g -c $<

clean:
	rm -rf $(EXEC) *.o
