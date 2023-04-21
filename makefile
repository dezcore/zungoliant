CC = gcc
CFLAGS = -Wall -g

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include
TEST_DIR = test

fifoDep = $(IDIR)/fifo.h $(SRC_DIR)/fifo.c
mainDep = $(IDIR)/testfile.h  $(IDIR)/testfifo.h $(SRC_DIR)/main.c
curlDep = $(IDIR)/curl.h $(SRC_DIR)/curl.c
parserDep = $(IDIR)/parser.h $(SRC_DIR)/parser.c 
fileDep = $(IDIR)/fifo.h $(IDIR)/file.h $(SRC_DIR)/file.c 
testfifoDep = $(IDIR)/fifo.h $(IDIR)/testfifo.h $(TEST_DIR)/testfifo.c
testfileDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h  $(IDIR)/file.h $(IDIR)/testfile.h $(TEST_DIR)/testfile.c
mainObj =  $(ODIR)/parser.o $(ODIR)/curl.o $(ODIR)/fifo.o $(ODIR)/file.o $(ODIR)/testfile.o $(ODIR)/testfifo.o $(ODIR)/main.o -lcurl -I/usr/local/include/myhtml/

all: $(BIN_DIR)/main
	./$(BIN_DIR)/main

$(BIN_DIR)/main: $(mainObj)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/main $(mainObj)

$(ODIR)/main.o: $(mainDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/main.c  -o $(ODIR)/main.o $(CFLAGS)

$(ODIR)/fifo.o: $(fifoDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/fifo.c -o $(ODIR)/fifo.o $(CFLAGS)

$(ODIR)/file.o: $(fileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/file.c -o $(ODIR)/file.o $(CFLAGS)

$(ODIR)/curl.o: $(curlDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/curl.c -o $(ODIR)/curl.o $(CFLAGS)

$(ODIR)/parser.o: $(parserDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/parser.c -o $(ODIR)/parser.o $(CFLAGS)

$(ODIR)/testfifo.o: $(testfifoDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testfifo.c -o $(ODIR)/testfifo.o $(CFLAGS)

$(ODIR)/testfile.o: $(testfileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testfile.c -o $(ODIR)/testfile.o $(CFLAGS)
	
clean:
	rm -rf $(SRC_DIR)/main $(ODIR)/*.o