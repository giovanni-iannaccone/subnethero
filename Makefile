CXX = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm 

EXEC = subnethero
TEST_EXEC = bin/tests

BUILD_DIR = build
SRC_DIR = src
TESTS_DIR = tests

SRCS = $(SRC_DIR)/flat.c $(SRC_DIR)/flsm.c $(SRC_DIR)/lookup.c $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/vlsm.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TESTS = $(SRC_DIR)/flat.c $(SRC_DIR)/flsm.c $(SRC_DIR)/utils.c $(SRC_DIR)/vlsm.c $(TESTS_DIR)/tests.c
TEST_OBJS = $(TESTS:$(TESTS_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@

clean:
	rm -f $(EXEC) *.gdb $(BUILD_DIR)/*.o

tests: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) -o $(TEST_EXEC)
	@./bin/tests
	@rm -rf ./bin/test

$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@

.PHONY: all clean tests