CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
INCLUDES = -Isrc/include
TARGET = davinci-video-converter

SRCS = src/main.cpp src/parser.cpp src/validator.cpp src/converter.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

src/main.o: src/main.cpp src/include/config.hpp src/include/parser.hpp src/include/validator.hpp src/include/converter.hpp
src/parser.o: src/parser.cpp src/include/parser.hpp src/include/config.hpp
src/validator.o: src/validator.cpp src/include/validator.hpp src/include/config.hpp
src/converter.o: src/converter.cpp src/include/converter.hpp src/include/config.hpp

clean:
	rm -f $(TARGET) $(OBJS)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)

test: $(TARGET) build_tests
	@echo "Running integration tests..."
	@./$(TARGET) --help
	@echo "Test: Help command passed"
	@./$(TARGET) 2>&1 | grep -q "Usage:" && echo "Test: No args passed" || (echo "Test failed" && exit 1)
	@echo "Running unit tests..."
	@./tests/test_parser
	@./tests/test_validator
	@./tests/test_converter
	@echo "All tests passed!"

build_tests: test_parser_bin test_validator_bin test_converter_bin

test_parser_bin: tests/test_parser.cpp src/parser.cpp src/include/config.hpp
	@mkdir -p tests
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o tests/test_parser tests/test_parser.cpp src/parser.cpp

test_validator_bin: tests/test_validator.cpp src/validator.cpp src/include/config.hpp
	@mkdir -p tests
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o tests/test_validator tests/test_validator.cpp src/validator.cpp

test_converter_bin: tests/test_converter.cpp src/converter.cpp src/include/config.hpp
	@mkdir -p tests
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o tests/test_converter tests/test_converter.cpp src/converter.cpp

clean-tests:
	rm -f tests/test_parser tests/test_validator tests/test_converter

.PHONY: all clean install uninstall test build_tests clean-tests
