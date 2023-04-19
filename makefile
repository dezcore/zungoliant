CC = gcc
CFLAGS = -Wall -g

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include

all: $(BIN_DIR)/main
	./$(BIN_DIR)/main

$(BIN_DIR)/main: $(ODIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/main $(ODIR)/main.o 

$(ODIR)/main.o:  $(SRC_DIR)/main.c
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/main.c  -o $(ODIR)/main.o $(CFLAGS)
	
clean:
	rm -rf $(SRC_DIR)/main $(ODIR)/*.o