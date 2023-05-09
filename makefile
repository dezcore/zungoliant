CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include
SRC_DB_DIR = src/db
DB_IDIR = include/db
TEST_DIR = test
TEST_IDIR = include/test
LDFLAGS = -lmyhtml -lcurl -ljson-c

jsonDep = $(IDIR)/json.h $(SRC_DIR)/json.c
fifoDep = $(IDIR)/fifo.h $(SRC_DIR)/fifo.c
pageDep = $(IDIR)/page.h $(SRC_DIR)/page.c

dbDep = $(IDIR)/utility.h $(DB_IDIR)/db.h $(SRC_DB_DIR)/DB.c
fileDep = $(IDIR)/utility.h $(IDIR)/file.h $(SRC_DIR)/file.c
ybotDep = $(IDIR)/utility.h $(IDIR)/ybot.h $(SRC_DIR)/ybot.c
zregexDep = $(IDIR)/file.h $(IDIR)/zregex.h $(SRC_DIR)/zregex.c
parserDep = $(IDIR)/file.h $(IDIR)/parser.h $(SRC_DIR)/parser.c
curlDep = $(IDIR)/utility.h $(IDIR)/curl.h $(SRC_DIR)/curl.c 
utilityDep = $(IDIR)/parser.h $(IDIR)/fifo.h $(IDIR)/json.h $(IDIR)/curl.h $(IDIR)/file.h $(IDIR)/zregex.h $(IDIR)/page.h $(DB_IDIR)/db.h $(IDIR)/utility.h $(SRC_DIR)/utility.c

mainDep = $(IDIR)/ybot.h $(SRC_DIR)/main.c
mainObj = $(ODIR)/json.o $(ODIR)/zregex.o $(ODIR)/fifo.o $(ODIR)/file.o $(ODIR)/parser.o $(ODIR)/curl.o $(ODIR)/utility.o $(ODIR)/ybot.o $(ODIR)/page.o $(ODIR)/db.o $(ODIR)/main.o

testdbDep = $(DB_IDIR)/db.h $(TEST_IDIR)/testdb.h $(TEST_DIR)/testdb.c
testfifoDep = $(IDIR)/fifo.h $(IDIR)/testfifo.h $(TEST_DIR)/testfifo.c
testfileDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h  $(IDIR)/file.h $(IDIR)/testfile.h $(TEST_DIR)/testfile.c
testDep = $(IDIR)/testzregex.h $(IDIR)/testfile.h  $(IDIR)/testfifo.h $(TEST_DIR)/main.c
testyDep = $(IDIR)/utility.h $(IDIR)/testy.h $(TEST_DIR)/testy.c
testzregexDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h $(IDIR)/file.h $(IDIR)/json.h $(IDIR)/zregex.h $(IDIR)/utility.h $(IDIR)/testzregex.h $(TEST_DIR)/testzregex.c
testObjs = $(ODIR)/json.o $(ODIR)/zregex.o $(ODIR)/fifo.o $(ODIR)/file.o $(ODIR)/parser.o $(ODIR)/utility.o $(ODIR)/curl.o $(ODIR)/page.o $(ODIR)/db.o
testObj = $(testObjs) $(ODIR)/testy.o $(ODIR)/testzregex.o $(ODIR)/testfile.o $(ODIR)/testfifo.o $(ODIR)/testdb.o $(ODIR)/test.o

all: $(BIN_DIR)/main
	./$(BIN_DIR)/main

test: $(BIN_DIR)/test
	./$(BIN_DIR)/test

$(BIN_DIR)/main: $(mainObj)
	@mkdir -p $(BIN_DIR)
	$(CC) $(mainObj) $(LDFLAGS) $(LDFLAGS) -o $(BIN_DIR)/main

$(BIN_DIR)/test : $(testObj)
	@mkdir -p $(BIN_DIR)
	$(CC) $(testObj) $(LDFLAGS) $(LDFLAGS) -o $(BIN_DIR)/test

$(ODIR)/main.o: $(mainDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/main.c  -o $(ODIR)/main.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/test.o: $(testDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/main.c  -o $(ODIR)/test.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/fifo.o: $(fifoDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/fifo.c -o $(ODIR)/fifo.o $(CFLAGS)

$(ODIR)/page.o: $(pageDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/page.c -o $(ODIR)/page.o $(CFLAGS)

$(ODIR)/utility.o: $(utilityDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/utility.c -o $(ODIR)/utility.o $(CFLAGS)

$(ODIR)/json.o: $(jsonDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/json.c -o $(ODIR)/json.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/ybot.o: $(ybotDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/ybot.c -o $(ODIR)/ybot.o $(CFLAGS)

$(ODIR)/file.o: $(fileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/file.c -o $(ODIR)/file.o $(CFLAGS)

$(ODIR)/db.o: $(dbDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DB_DIR)/db.c -o $(ODIR)/db.o $(CFLAGS)

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

$(ODIR)/testdb.o: $(testdbDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testdb.c -o $(ODIR)/testdb.o $(CFLAGS)

$(ODIR)/testfile.o: $(testfileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testfile.c -o $(ODIR)/testfile.o $(CFLAGS)

$(ODIR)/testy.o: $(testyDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testy.c -o $(ODIR)/testy.o $(CFLAGS)

$(ODIR)/testzregex.o: $(testzregexDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(TEST_DIR)/testzregex.c -o $(ODIR)/testzregex.o $(CFLAGS)
	
clean:
	rm -rf $(SRC_DIR)/main $(ODIR)/*.o