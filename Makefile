# make  - to compile normal run
# make test - to compile for unit testing 

GTEST_DIR=~/EMBEDDED/googletest/googletest

COPTS=-Wall -funsigned-char  -fpermissive -fprofile-arcs -ftest-coverage
LDFLAGS=-lgcov --coverage

PROJ=ringbuffer

######### Main targets ##########
release: main.o $(PROJ).o
	gcc main.o $(PROJ).o -o release $(LDFLAGS)
	
test: Gtest_main.o ringbuffer_test_case.o $(PROJ).o libgtest.a
	g++  $(COPTS) $(LDFLAGS) -I $(GTEST_DIR)/include -pthread $(PROJ).o ringbuffer_test_case.o Gtest_main.o libgtest.a -o ring

########## Normal - Release ###########

$(PROJ).o: $(PROJ).c 
	gcc  -c $(PROJ).c
main.o: main.c
	gcc -c main.c
    
########## Unit test - test ########

Gtest_main.o: Gtest_main.c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) Gtest_main.c

$(PROJ).o: $(PROJ).c 
	g++ -g -c $(COPTS) $(PROJ).c -o $(PROJ).o

ringbuffer_test_case.o: ringbuffer_test_case.c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) $(COPTS) ringbuffer_test_case.c

########## Google Test framework ############
libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

########## Clean ######################
clean:
	rm -f *.o

