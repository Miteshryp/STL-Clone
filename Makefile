CXX=gcc
WORKSPACE=./

INCLUDE_DIR=$(WORKSPACE)/include
TEST_DIR=$(WORKSPACE)/tests
LIB_DIR=$(WORKSPACE)/lib

run_tests:
	echo $(CXX)

build_test:
	$(CXX) -I $(INCLUDE_DIR) 

