CC = g++ -std=c++11
CFLAFS = -O3 -g
FILES = main.o String.o entry_list.o entry.o 

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

run:
	./invSearchEngine

.PHONY: clean
clean:
	rm -f invSearchEngine $(FILES)