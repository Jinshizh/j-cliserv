CC = gcc
EXEC = j-server-udp
OBJS = j-server-udp.o str_echo_udp.o error.o

$(EXEC): $(OBJS)
	$(CC) -g -o $(EXEC) $(OBJS)
j-server-udp.o:j-server-udp.c ../lib/unp.h
	$(CC) -g -c $<
str_echo_udp.o:str_echo_udp.c ../lib/unp.h
	$(CC) -g -c $<
error.o:error.c ../lib/unp.h
	$(CC) -g -c $<

clean:
	rm -rf $(EXEC) *.o
