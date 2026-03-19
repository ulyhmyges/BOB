CFLAGS += -std=c11 -Wall -Wextra \
          -g -Og \
          -fsanitize=address,undefined -fno-omit-frame-pointer \
		  -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wformat=2 

# 	  -Wpedantic        # strict ISO C compliance
# 		-Wshadow          # warns if a variable shadows another
# 		-Wconversion      # implicit type conversions (can be noisy)
# 		-Wsign-conversion # signed/unsigned mistakes
# 		-Wformat=2        # extra printf/scanf checks
all: clean build run

build:
	@echo Build...
	$(CC) $(CFLAGS) *.c -o main
run:
	@echo Execute the game Binding Of Briatte...
	./main

clean:
	rm -f main

