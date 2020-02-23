BIN = linkedList
OBJ = main.o linkedList.o

$(BIN) : $(OBJ)
	cc $(OBJ) -o $(BIN)

main.o : main.c linkedList.h
	cc -c main.c -o main.o

linkedList.o : linkedList.c linkedList.h
	cc -c linkedList.c -o linkedList.o

clean :
	rm -f $(BIN) $(OBJ)