#include "../src/include/parser.hpp"
#include <iostream>
#include <cassert>
#include <cstring>

void test_parse_help() {
    // Help triggers print_usage and exits, so we skip this test
    std::cout << "test_parse_help: skipped (exits on --help)" << std::endl;
}

void test_parse_default_values() {
    char* args[] = {(char*)"program", (char*)"input.mp4", (char*)"output.mp4", nullptr};
    Config config = parse_arguments(3, args);

    assert(config.input_path == "input.mp4");
    assert(config.output_path == "output.mp4");
    assert(config.codec == "h264");
    assert(config.quality == "medium");
    assert(config.crf == 23);
    assert(config.verbose == false);

    std::cout << "test_parse_default_values: PASSED" << std::endl;
}

void test_parse_custom_values() {
    char* args[] = {
        (char*)"program",
        (char*)"input.mov",
        (char*)"output.mkv",
        (char*)"-c", (char*)"hevc",
        (char*)"-q", (char*)"slow",
        (char*)"-r", (char*)"18",
        (char*)"-v",
        nullptr
    };
    Config config = parse_arguments(10, args);

    assert(config.input_path == "input.mov");
    assert(config.output_path == "output.mkv");
    assert(config.codec == "hevc");
    assert(config.quality == "slow");
    assert(config.crf == 18);
    assert(config.verbose == true);

    std::cout << "test_parse_custom_values: PASSED" << std::endl;
}

void test_parse_long_options() {
    char* args[] = {
        (char*)"program",
        (char*)"src.mp4",
        (char*)"dst.mp4",
        (char*)"--codec", (char*)"prores",
        (char*)"--quality", (char*)"fast",
        (char*)"--crf", (char*)"28",
        (char*)"--verbose",
        nullptr
    };
    Config config = parse_arguments(10, args);

    assert(config.input_path == "src.mp4");
    assert(config.output_path == "dst.mp4");
    assert(config.codec == "prores");
    assert(config.quality == "fast");
    assert(config.crf == 28);
    assert(config.verbose == true);

    std::cout << "test_parse_long_options: PASSED" << std::endl;
}

int main() {
    std::cout << "=== Parser Tests ===" << std::endl;
    
    test_parse_default_values();
    test_parse_custom_values();
    test_parse_long_options();
    
    std::cout << "All parser tests passed!" << std::endl;
    return 0;
}
