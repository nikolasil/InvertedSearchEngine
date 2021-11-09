CC = g++ -std=c++11
CFLAFS = -O3 -g
FILES = main.o String.o entry_list.o entry.o tree.o approximateMatching.o linkedList.o functions.o

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

run:
	./invSearchEngine

.PHONY: clean
clean:
	rm -f invSearchEngine $(FILES)