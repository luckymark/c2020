BIN = warehouse
OBJ = main.o goods.o

$(BIN) : $(OBJ)
	cc $(OBJ) -o $(BIN)

main.o : main.c goods.h
	cc -c main.c -o main.o

goods.o : goods.c goods.h
	cc -c goods.c -o goods.o

clean :
	rm -f $(BIN) $(OBJ)