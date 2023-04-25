CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include
TEST_DIR = test
LDFLAGS = -lmyhtml -lcurl -ljson-c

fifoDep = $(IDIR)/fifo.h $(SRC_DIR)/fifo.c
curlDep = $(IDIR)/curl.h $(SRC_DIR)/curl.c
fileDep = $(IDIR)/fifo.h $(IDIR)/file.h $(SRC_DIR)/file.c
zregexDep = $(IDIR)/file.h $(IDIR)/zregex.h $(SRC_DIR)/zregex.c
parserDep = $(IDIR)/file.h $(IDIR)/parser.h $(SRC_DIR)/parser.c 
mainDep = $(IDIR)/testzregex.h $(IDIR)/testfile.h  $(IDIR)/testfifo.h $(SRC_DIR)/main.c


testfifoDep = $(IDIR)/fifo.h $(IDIR)/testfifo.h $(TEST_DIR)/testfifo.c
testzregexDep = $(IDIR)/zregex.h $(IDIR)/testzregex.h $(TEST_DIR)/testzregex.c
testfileDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h  $(IDIR)/file.h $(IDIR)/testfile.h $(TEST_DIR)/testfile.c

mainObj = $(ODIR)/zregex.o $(ODIR)/fifo.o $(ODIR)/file.o $(ODIR)/parser.o $(ODIR)/curl.o $(ODIR)/testzregex.o $(ODIR)/testfile.o $(ODIR)/testfifo.o $(ODIR)/main.o

all: $(BIN_DIR)/main
	./$(BIN_DIR)/main

$(BIN_DIR)/main: $(mainObj)
	@mkdir -p $(BIN_DIR)
	$(CC) $(mainObj) $(LDFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main

$(ODIR)/main.o: $(mainDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/main.c  -o $(ODIR)/main.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/fifo.o: $(fifoDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/fifo.c -o $(ODIR)/fifo.o $(CFLAGS)

$(ODIR)/file.o: $(fileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/file.c -o $(ODIR)/file.o $(CFLAGS)

$(ODIR)/zregex.o: $(zregexDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/zregex.c -o $(ODIR)/zregex.o $(CFLAGS)

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

$(ODIR)/testzregex.o: $(testzregexDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testzregex.c -o $(ODIR)/testzregex.o $(CFLAGS)
	
clean:
	rm -rf $(SRC_DIR)/main $(ODIR)/*.o