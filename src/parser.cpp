#include "parser.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>

void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " [options] <input> <output>\n"
              << "Options:\n"
              << "  -c, --codec <codec>     Video codec (h264, h265, prores) [default: h264]\n"
              << "  -q, --quality <qual>    Quality preset (fast, medium, slow) [default: medium]\n"
              << "  -r, --crf <value>       CRF value 0-51 [default: 23]\n"
              << "  -v, --verbose           Enable verbose output\n"
              << "  -h, --help              Show this help message\n";
}

Config parse_arguments(int argc, char* argv[]) {
    Config config;
    std::vector<std::string> positional_args;
    
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            print_usage(argv[0]);
            std::exit(0);
        } else if (arg == "-c" || arg == "--codec") {
            if (i + 1 < argc) {
                config.codec = argv[++i];
            }
        } else if (arg == "-q" || arg == "--quality") {
            if (i + 1 < argc) {
                config.quality = argv[++i];
            }
        } else if (arg == "-r" || arg == "--crf") {
            if (i + 1 < argc) {
                try {
                    config.crf = std::stoi(argv[++i]);
                } catch (const std::exception& e) {
                    std::cerr << "Error: Invalid CRF value" << std::endl;
                    std::exit(1);
                }
            }
        } else if (arg == "-v" || arg == "--verbose") {
            config.verbose = true;
        } else if (arg[0] != '-') {
            positional_args.push_back(arg);
        } else {
            std::cerr << "Error: Unknown option: " << arg << std::endl;
            print_usage(argv[0]);
            std::exit(1);
        }
    }
    
    if (positional_args.size() >= 1) {
        config.input_path = positional_args[0];
    }
    if (positional_args.size() >= 2) {
        config.output_path = positional_args[1];
    }
    
    return config;
}
