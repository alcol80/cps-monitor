CXX:=clang++
# LDFLAGS:=-L /usr/local/ -l ppl -l gmp -l gmpxx
LDFLAGS:=-l ppl -l gmp -l gmpxx

TEST_FLAGS:=--success

SRC_DIR:=src
BUILD_DIR:=build

TEST_BUILD_DIR:=$(BUILD_DIR)/Test
TEST_TARGET:=$(TEST_BUILD_DIR)/test

TEST_SRC:=$(wildcard $(SRC_DIR)/*.cpp)
TEST_OBJ:=$(patsubst $(SRC_DIR)/%,$(TEST_BUILD_DIR)/%,$(TEST_SRC:.cpp=.o))

test: $(TEST_TARGET)
	time $< $(TEST_FLAGS)

build-test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(TEST_BUILD_DIR):
	mkdir -p $@

$(TEST_BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(TEST_BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(SRC_DIR):
	mkdir -p $@

fetch-catch: $(SRC_DIR)
	wget -O $(SRC_DIR)/catch.hpp https://raw.githubusercontent.com/philsquared/Catch/master/single_include/catch.hpp
