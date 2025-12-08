# Save as: worksheet1/Makefile
CC = gcc
ASM = nasm
CFLAGS = -m32
ASMFLAGS = -f elf

SRC_DIR = src
EXECUTABLES = task1 task1_2 task2_name task2_array task2_range

all: $(EXECUTABLES)

# Build asm_io.o
$(SRC_DIR)/asm_io.o: $(SRC_DIR)/asm_io.asm
	$(ASM) $(ASMFLAGS) $< -o $@

# Build driver.o
$(SRC_DIR)/driver.o: $(SRC_DIR)/driver.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build each task
task1: $(SRC_DIR)/driver.o $(SRC_DIR)/asm_io.o $(SRC_DIR)/task1.o
	$(CC) $(CFLAGS) $^ -o $@

task1_2: $(SRC_DIR)/driver.o $(SRC_DIR)/asm_io.o $(SRC_DIR)/task1_2.o
	$(CC) $(CFLAGS) $^ -o $@

task2_name: $(SRC_DIR)/driver.o $(SRC_DIR)/asm_io.o $(SRC_DIR)/task2_name.o
	$(CC) $(CFLAGS) $^ -o $@

task2_array: $(SRC_DIR)/driver.o $(SRC_DIR)/asm_io.o $(SRC_DIR)/task2_array.o
	$(CC) $(CFLAGS) $^ -o $@

task2_range: $(SRC_DIR)/driver.o $(SRC_DIR)/asm_io.o $(SRC_DIR)/task2_range.o
	$(CC) $(CFLAGS) $^ -o $@

# Assembly object files
%.o: %.asm
	$(ASM) $(ASFLAGS) $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXECUTABLES)

.PHONY: all clean