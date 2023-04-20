CC = gcc
CFLAGS = -Wall -g

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include
TEST_DIR = test

all: $(BIN_DIR)/main
	./$(BIN_DIR)/main

$(BIN_DIR)/main: $(ODIR)/fifo.o $(ODIR)/testfifo.o $(ODIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/main $(ODIR)/fifo.o $(ODIR)/testfifo.o $(ODIR)/main.o 

$(ODIR)/main.o: $(IDIR)/testfifo.h $(SRC_DIR)/main.c
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/main.c  -o $(ODIR)/main.o $(CFLAGS)

$(ODIR)/fifo.o: $(IDIR)/fifo.h $(SRC_DIR)/fifo.c
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/fifo.c -o $(ODIR)/fifo.o $(CFLAGS)

$(ODIR)/testfifo.o: $(IDIR)/fifo.h $(IDIR)/testfifo.h $(TEST_DIR)/testfifo.c
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testfifo.c -o $(ODIR)/testfifo.o $(CFLAGS)
	
clean:
	rm -rf $(SRC_DIR)/main $(ODIR)/*.o