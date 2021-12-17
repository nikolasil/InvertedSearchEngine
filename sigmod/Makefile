# Copyright (c) 2013 KAUST - InfoCloud Group (All Rights Reserved)
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
#
# Authors: Amin Allam  <amin.allam@kaust.edu.sa>,
#          Fuad Jamour <fuad.jamour@kaust.edu.sa>
#
# Current version: 1.0 (initial release)
	

# Build targets (your implementation targets should go in IMPL_O)
TEST_O=test_driver/test.o 
IMPL_O=ref_impl/core.o

# Compiler flags
CC  = gcc
CXX = g++
CFLAGS=-O3 -fPIC -Wall -g -I. -I./include
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpthread

# The programs that will be built
PROGRAMS=testdriver
FILES = String.o hashTable.o bucket.o exactInfoList.o heInfoList.o BK_Tree.o hammingArray.o MatchArray.o MatchTree.o ResultList.o DocumentList.o structs.o
# The name of the library that will be built
LIBRARY=core

TESTER = test.o

# Build all programs
all: clean $(PROGRAMS)
test :  $(IMPL_O)  $(FILES) $(TESTER)
	$(CXX) $(CFLAFS) -o test  $(IMPL_O)  $(FILES) $(TESTER) -lcrypto
lib: $(IMPL_O) $(FILES)
	$(CXX) $(CXXFLAGS) -shared -o lib$(LIBRARY).so $(IMPL_O) $(FILES)  -I /usr/local/Cellar/openssl@3/3.0.0_1/include/ -L  /usr/local/Cellar/openssl@3/3.0.0_1/lib/ -lcrypto

testdriver: lib $(TEST_O) $(FILES)
	$(CXX) $(CXXFLAGS) -o testdriver $(TEST_O) ./lib$(LIBRARY).so $(FILES) -lcrypto

hashTable.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/hashTable/hashTable.cpp

bucket.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/hashTable/bucket.cpp

exactInfoList.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/queryList/exactInfoList.cpp

heInfoList.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/queryList/heInfoList.cpp
	
BK_Tree.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/tree/BK_Tree.cpp
	
hammingArray.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/tree/hammingArray.cpp

MatchArray.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/MatchArray/MatchArray.cpp

MatchTree.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/MatchArray/MatchTree.cpp

ResultList.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/MatchArray/ResultList.cpp
DocumentList.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/DocumentList/DocumentList.cpp

String.o:
	$(CXX) $(CXXFLAGS) -c ../Data\ Structures/string/String.cpp
structs.o:
	$(CXX) $(CXXFLAGS) -c ref_impl/structs.cpp

#Test files
test.o :
	$(CXX) $(CFLAFS) -c ../tests/test.cpp
clean:
	rm -f $(PROGRAMS) lib$(LIBRARY).so
	find . -name '*.o' -print | xargs rm -f
clean_test:
	rm -f test $(FILES) $(TESTER)