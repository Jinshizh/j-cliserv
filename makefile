CC = gcc
EXEC = j-server
OBJS = j-server.o str_echo.o

$(EXEC): $(OBJS)
	$(CC) -g -o $(EXEC) $(OBJS)
j-server.o:j-server.c lib/unp.h
	$(CC) -g -c $<
str_echo.o:str_echo.c lib/unp.h
	$(CC) -g -c $<
clean:
	rm -rf $(EXEC) *.o
