CC = g++ -std=c++11
CFLAFS = -O3 -g
FILES = main.o

invSearchEngine: clean $(FILES)
	$(CC) $(CFLAFS) -o invSearchEngine $(FILES)

main.o:
	$(CC) $(CFLAFS) -c main.cpp

.PHONY: clean
clean:
	rm -f invSearchEngine $(FILES)