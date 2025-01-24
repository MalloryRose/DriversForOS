# Compiler and flags
CC = wcl
CFLAGS = -ml       # Large memory model for real mode
LIB_NAME = drivers.lib
TEST_SRC = ../tests.c
TEST_EXE = ../tests.exe

# Source files
DRIVER_SRC = mouse.c vga.c
DRIVER_OBJ = mouse.obj vga.obj
HEADERS = mouse.h vga.h

# Build all targets
all: $(LIB_NAME) $(TEST_EXE)

# Create the static library
$(LIB_NAME): $(DRIVER_OBJ)
	@echo Creating $(LIB_NAME) from $(DRIVER_OBJ)
	!if exist $(LIB_NAME) del $(LIB_NAME)
	wlib /q $(LIB_NAME) $(DRIVER_OBJ)

# Compile driver object files
mouse.obj: mouse.c $(HEADERS)
	@echo Compiling mouse.c
	$(CC) $(CFLAGS) -c mouse.c

vga.obj: vga.c $(HEADERS)
	@echo Compiling vga.c
	$(CC) $(CFLAGS) -c vga.c

# Compile and link tests.c with drivers.lib to create tests.exe
$(TEST_EXE): $(TEST_SRC) $(LIB_NAME)
	@echo Compiling and linking $(TEST_SRC) with $(LIB_NAME) to create $(TEST_EXE)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_NAME) -fe=$(TEST_EXE)

# Clean up build files
clean:
	@echo Cleaning up...
	del *.obj
	del *.lib
	del $(TEST_EXE)
