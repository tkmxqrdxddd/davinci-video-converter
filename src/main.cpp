#include <iostream>
#include "config.hpp"
#include "parser.hpp"
#include "validator.hpp"
#include "converter.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    Config config = parse_arguments(argc, argv);
    
    std::string error;
    if (!validate_config(config, error)) {
        std::cerr << "Error: " << error << std::endl;
        return 1;
    }
    
    std::string command = build_ffmpeg_command(config);
    
    if (execute_conversion(command, config.verbose) != 0) {
        return 1;
    }
    
    std::cout << "Conversion completed successfully!" << std::endl;
    return 0;
}
