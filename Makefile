CC = g++ -std=c++11
CFLAFS = -O3 -g
TESTFLAGS = -O0 -g
FILES = main.o String.o entry_list.o entry.o tree.o approximateMatching.o linkedList.o functions.o 
TESTFILES =  String.o entry_list.o entry.o tree.o approximateMatching.o linkedList.o functions.o 
TESTER = test.o
# Project Files

invSearchEngine: clean $(FILES)
	$(CC) $(CFLAFS) -o invSearchEngine $(FILES)

main.o:
	$(CC) $(CFLAFS) -c main.cpp

String.o:
	$(CC) $(CFLAFS) -c Data\ Structures/string/String.cpp

entry_list.o :
	$(CC) $(CFLAFS) -c Data\ Structures/entry/entry_list.cpp

entry.o :
	$(CC) $(CFLAFS) -c Data\ Structures/entry/entry.cpp

tree.o :
	$(CC) $(CFLAFS) -c Data\ Structures/tree/tree.cpp

approximateMatching.o :
	$(CC) $(CFLAFS) -c Data\ Structures/utils/approximateMatching.cpp
linkedList.o :
	$(CC) $(CFLAFS) -c Data\ Structures/linkedList/linkedList.cpp
functions.o :
	$(CC) $(CFLAFS) -c Functions/functions.cpp

# Testing Files

test.o :
	$(CC) $(CFLAFS) -c tests/test.cpp


# Commands
run:
	./invSearchEngine

test: clean_test $(TESTFILES) $(TESTER)
	$(CC) $(TESTFLAGS) -o test  $(TESTFILES) $(TESTER)
	./test


.PHONY: clean
clean_all: clean clean_test
clean:
	rm -f invSearchEngine $(FILES)
clean_test:
	rm -f test $(TESTER)