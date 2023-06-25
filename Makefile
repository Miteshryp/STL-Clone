CXX=gcc
WORKSPACE=./

# INCLUDE_DIR=$(WORKSPACE)/include
# TEST_DIR=$(WORKSPACE)/tests
# LIB_DIR=$(WORKSPACE)/lib
# CXX_STD=c++20

INCLUDE_DIR=$(WORKSPACE)
TEST_DIR=$(WORKSPACE)/tests
LIB_DIR=$(WORKSPACE)/lib
CXX_STD=c++20

run: $(TEST_DIR)/main.cpp
	make build_main
	./a.out

build_main: $(TEST_DIR)/main.cpp
	$(CXX) -I $(INCLUDE_DIR) $(TEST_DIR)/main.cpp -std=$(CXX_STD)

run_tests:
	echo $(CXX)

build_test:
	$(CXX) -I $(INCLUDE_DIR)


