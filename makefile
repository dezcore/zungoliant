CC = gcc
CFLAGS = -Wall -g $(shell pkg-config --cflags json-c) -g $(shell pkg-config --cflags libmongoc-1.0)
LDFLAGS += $(shell pkg-config --libs json-c) $(shell pkg-config --libs libmongoc-1.0)
#MONGOFLAG = $(shell pkg-config --libs --cflags libmongoc-1.0)
#MONGOLIBS = -I/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0
#MONGOLIBS = -I/usr/local/include/libbson-1.0 -/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0
#-I/usr/local/include/libbson-1.0 -/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0

ODIR = obj
BIN_DIR = bin
SRC_DIR = src
LIBPATH = lib
IDIR = include
SRC_DB_DIR = src/db
SRC_YOUTUBE_DIR = src/youtube
DB_IDIR = include/db
YOUTUBE_IDIR = include/youtube

TEST_DIR = test
TEST_IDIR = include/test
LDFLAGS = -lmyhtml -lcurl -ljson-c -lmongoc-1.0 -lbson-1.0

jsonDep = $(IDIR)/json.h $(SRC_DIR)/json.c
fifoDep = $(IDIR)/fifo.h $(SRC_DIR)/fifo.c
curlDep = $(IDIR)/utility.h $(IDIR)/file.h $(IDIR)/curl.h $(SRC_DIR)/curl.c 
fileDep = $(IDIR)/utility.h $(IDIR)/file.h $(SRC_DIR)/file.c
parserDep = $(IDIR)/file.h $(IDIR)/parser.h $(SRC_DIR)/parser.c
zregexDep = $(IDIR)/file.h $(IDIR)/zregex.h $(SRC_DIR)/zregex.c
utilityDep = $(IDIR)/fifo.h $(IDIR)/json.h $(IDIR)/utility.h $(SRC_DIR)/utility.c

dbDep = $(IDIR)/utility.h $(DB_IDIR)/mongodb_bson.h $(DB_IDIR)/db.h $(SRC_DB_DIR)/db.c
mongodbbsonDep = $(DB_IDIR)/db.h $(IDIR)/utility.h $(DB_IDIR)/mongodb_bson.h $(SRC_DB_DIR)/mongodb_bson.c
ybotDep = $(IDIR)/utility.h $(YOUTUBE_IDIR)/page.h $(YOUTUBE_IDIR)/ybot.h $(SRC_YOUTUBE_DIR)/ybot.c
pageDep = $(IDIR)/utility.h $(IDIR)/file.h $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/zregex.h $(DB_IDIR)/mongodb_bson.h $(YOUTUBE_IDIR)/page.h $(SRC_YOUTUBE_DIR)/page.c

mainDep = $(YOUTUBE_IDIR)/ybot.h $(SRC_DIR)/main.c
mainObj = $(ODIR)/json.o $(ODIR)/fifo.o $(ODIR)/curl.o $(ODIR)/zregex.o $(ODIR)/parser.o $(ODIR)/utility.o $(ODIR)/file.o  $(ODIR)/mongodb_bson.o $(ODIR)/db.o $(ODIR)/page.o $(ODIR)/ybot.o $(ODIR)/main.o

testfifoDep = $(IDIR)/fifo.h $(IDIR)/testfifo.h $(TEST_DIR)/testfifo.c
testfileDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h  $(IDIR)/file.h $(IDIR)/testfile.h $(TEST_DIR)/testfile.c
testDep = $(IDIR)/testzregex.h $(IDIR)/testfile.h  $(IDIR)/testfifo.h $(TEST_DIR)/main.c
testyDep = $(IDIR)/utility.h $(YOUTUBE_IDIR)/page.h  $(IDIR)/testy.h $(TEST_DIR)/testy.c
testdbDep = $(IDIR)/utility.h $(YOUTUBE_IDIR)/page.h $(TEST_IDIR)/testdb.h $(TEST_DIR)/testdb.c
testzregexDep = $(IDIR)/parser.h $(IDIR)/curl.h $(IDIR)/fifo.h $(IDIR)/file.h $(IDIR)/json.h $(IDIR)/zregex.h $(IDIR)/utility.h $(IDIR)/testzregex.h $(TEST_DIR)/testzregex.c

testObjs = $(ODIR)/json.o $(ODIR)/zregex.o $(ODIR)/fifo.o $(ODIR)/file.o $(ODIR)/parser.o $(ODIR)/curl.o $(ODIR)/page.o $(ODIR)/utility.o $(ODIR)/mongodb_bson.o $(ODIR)/db.o 
testObj = $(testObjs) $(ODIR)/testy.o $(ODIR)/testzregex.o $(ODIR)/testfile.o $(ODIR)/testfifo.o $(ODIR)/testdb.o $(ODIR)/test.o

all: $(BIN_DIR)/main

test: $(BIN_DIR)/test

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
	$(CC) -c $(SRC_YOUTUBE_DIR)/page.c -o $(ODIR)/page.o $(CFLAGS)

$(ODIR)/utility.o: $(utilityDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/utility.c -o $(ODIR)/utility.o $(CFLAGS)

$(ODIR)/json.o: $(jsonDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/json.c -o $(ODIR)/json.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/ybot.o: $(ybotDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_YOUTUBE_DIR)/ybot.c -o $(ODIR)/ybot.o $(CFLAGS)

$(ODIR)/file.o: $(fileDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DIR)/file.c -o $(ODIR)/file.o $(CFLAGS)

$(ODIR)/db.o: $(dbDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DB_DIR)/db.c -o $(ODIR)/db.o $(CFLAGS) $(LDFLAGS)

$(ODIR)/mongodb_bson.o: $(mongodbbsonDep)
	@mkdir -p $(ODIR)
	$(CC) -c $(SRC_DB_DIR)/mongodb_bson.c -o $(ODIR)/mongodb_bson.o $(CFLAGS) $(LDFLAGS)

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