CXX=g++
CXX_STD=c++20

WORKSPACE=./
INCLUDE_DIR=$(WORKSPACE)
TEST_DIR=$(WORKSPACE)tests/
LIB_DIR=$(WORKSPACE)lib/
TESTING_LIB=-lcriterion

run: $(TEST_DIR)/main.cpp
	make build_main
	./a.out

build_main_debug: $(TEST_DIR)main.cpp
	$(CXX) -I $(INCLUDE_DIR) $(TEST_DIR)/main.cpp -std=$(CXX_STD) -g

build_main_prod: $(TEST_DIR)main.cpp
	$(CXX) -I $(INCLUDE_DIR) $(TEST_DIR)/main.cpp -std=$(CXX_STD) -O3

# run_tests:
# 	$(CXX) -I $(INCLUDE_DIR) -lc

build_test:
	$(CXX) -I $(INCLUDE_DIR) -std=$(CXX_STD) $(TEST_DIR) $(TESTING_LIB)


