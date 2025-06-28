CXX = gcc
CFLAGS = -Wall -Wextra -lm
EXEC = subnetter

SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/flat.c $(SRC_DIR)/flsm.c $(SRC_DIR)/main.c $(SRC_DIR)/utils.c $(SRC_DIR)/vlsm.c
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(EXEC)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CXX) -c $< -o $@

clean:
	rm -f $(EXEC) *.gdb $(BUILD_DIR)/*.o

.PHONY: all clean