#
# 'make'        build executable file 'VideoConverter'
# 'make clean'  removes all .o and executable files
#

# define the Cpp compiler to use
CXX = g++

# define any compile-time flags
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# define output directory
OUTPUT = output

# define source directory
SRC = src

# define the main executable name
MAIN = VideoConverter

# define the C source files
SOURCES = $(wildcard $(SRC)/*.cpp)

# define the C object files
OBJECTS = $(SOURCES:.cpp=.o)

OUTPUTMAIN = $(OUTPUT)/$(MAIN)

all: $(OUTPUT) $(OUTPUTMAIN)
	@echo "Building executable: $(MAIN)"
	@echo Executing 'all' complete!

$(OUTPUT):
	mkdir -p $(OUTPUT)

$(OUTPUTMAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUTMAIN) $(OBJECTS)

.PHONY: clean
clean:
	@echo "Cleaning up..."
	rm -f $(OUTPUTMAIN)
	rm -f $(OBJECTS)
	@echo Cleanup complete!

run: all
	@echo "Running executable: $(OUTPUTMAIN)"
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!
