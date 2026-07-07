#include "config.hpp"
#include "converter.hpp"
#include "parser.hpp"
#include "validator.hpp"
#include <iostream>
#include <optional>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    bool help_requested = false;
    auto config_opt = parse_arguments(argc, argv, help_requested);
    if (!config_opt) {
        return help_requested ? 0 : 1;
    }
    Config config = *config_opt;

    auto error = validate_config(config);
    if (error) {
        std::cerr << "Error: " << *error << std::endl;
        return 1;
    }

    if (execute_conversion(config, config.verbose) != 0) {
        return 1;
    }

    std::cout << "Conversion completed successfully!" << std::endl;
    return 0;
}
