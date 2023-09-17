THISDIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
CXXFLAGS += -I$(THISDIR)/../include -I$(THISDIR)/../third_party/ --std=c++23 -Wall -pedantic

all : test
test : test.cpp
	$(CXX) $(CXXFLAGS) test.cpp -o test $(LINK)

.PHONY : clean


clean :
	rm -rf ./test
	rm -rf ./test_cov
	rm -rf ./default.profdata
	rm -rf ./default.profraw
