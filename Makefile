#
# 'make'        build executable file 'davinci-convert'
# 'make clean'  removes all .o and executable files
#

# Define the C++ compiler to use
CXX = g++

# Define any compile-time flags	
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Define output directory
OUTPUT = output

# Define source directory
SRC = src

# Define the main executable name
MAIN = davinci-convert

# Define the C source files
SOURCES = $(wildcard $(SRC)/*.cpp)

# Define the C object files
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

install: all
	install -Dm755 $(OUTPUTMAIN) /usr/bin/davinci-convert
