CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I..

TESTS = test_dynamic.exe test_linkedlist.exe \
		test_arrayseq.exe test_listseq.exe \
		test_bitseq.exe test_mapreduce.exe\
		test_dynamicseq.exe

.PHONY: all clean run

all: $(TESTS)
test_dynamicseq.exe: DynamicSequence_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_dynamic.exe: DynamicArray_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_linkedlist.exe: LinkedList_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_arrayseq.exe: ArraySequence_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_listseq.exe: ListSequence_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_bitseq.exe: BitSequence_test.cpp 
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $^ -o $@

test_mapreduce.exe: MapReduce_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $^ -o $@

run: $(TESTS)

clean:
	del *.exe 2> nul