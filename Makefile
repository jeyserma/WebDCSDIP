
BIN_DIR  = bin
INT_DIR  = interface
SRC_DIR  = src
OBJ_DIR  = obj
LIB_DIR  = lib

CC = g++ -std=c++11

LFLAGS       := -Llib -L/usr/lib -L$(LIB_DIR) -lncurses -lpthread -lrt 
CFLAGS       := -ggdb -fPIC -DLINUX -Wall -funsigned-char -I$(INC_DIR) -I$(LIB_DIR) -DUNIX -DLINUX -I$(INT_DIR)


$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

dip:  dip.o
	    g++ $(CFLAGS) $(OBJ_DIR)/dip.o ./DIPSoftware/lib64/libdip.so -o $(BIN_DIR)/dip $(LFLAGS) 
dip.o:
	$(CC) $(CFLAGS) -c $(SRC_DIR)/dip.cpp -o $(OBJ_DIR)/dip.o	

clean:
	rm $(BIN_DIR)/*
	rm $(OBJ_DIR)/*

remove:
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*
