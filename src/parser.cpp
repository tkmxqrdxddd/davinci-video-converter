#include "parser.hpp"
#include <iostream>
#include <optional>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, Codec> codec_map = {
    {"h264", Codec::h264},
    {"h265", Codec::h265},
    {"prores", Codec::prores},
};

static const std::unordered_map<std::string, Quality> quality_map = {
    {"fast", Quality::fast},
    {"medium", Quality::medium},
    {"slow", Quality::slow},
};

void print_usage(const char* program_name) {
    std::cout
        << "Usage: " << program_name << " [options] <input> <output>\n"
        << "Options:\n"
        << "  -c, --codec <codec>       Video codec (h264, h265, prores) [default: h264]\n"
        << "  -q, --quality <qual>      Quality preset (fast, medium, slow) [default: medium]\n"
        << "  -r, --crf <value>         CRF value 0-51 [default: 23]\n"
        << "  -y, --overwrite           Overwrite output file without asking\n"
        << "  -v, --verbose             Enable verbose output\n"
        << "  -h, --help                Show this help message\n"
        << "      --version             Show version information\n";
}

std::optional<Config> parse_arguments(int argc, char* argv[], bool& help_requested) {
    help_requested = false;
    Config config;
    std::vector<std::string> positional_args;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_usage(argv[0]);
            help_requested = true;
            return std::nullopt;
        } else if (arg == "--version") {
            std::cout << "davinci-video-converter " << PROJECT_VERSION << std::endl;
            help_requested = true;
            return std::nullopt;
        } else if (arg == "-c" || arg == "--codec") {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                std::cerr << "Error: Option " << arg << " requires a value" << std::endl;
                print_usage(argv[0]);
                return std::nullopt;
            }
            std::string val = argv[++i];
            auto it = codec_map.find(val);
            if (it == codec_map.end()) {
                std::cerr << "Error: Invalid codec '" << val
                          << "'. Valid options: h264, h265, prores" << std::endl;
                return std::nullopt;
            }
            config.codec = it->second;
        } else if (arg == "-q" || arg == "--quality") {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                std::cerr << "Error: Option " << arg << " requires a value" << std::endl;
                print_usage(argv[0]);
                return std::nullopt;
            }
            std::string val = argv[++i];
            auto it = quality_map.find(val);
            if (it == quality_map.end()) {
                std::cerr << "Error: Invalid quality '" << val
                          << "'. Valid options: fast, medium, slow" << std::endl;
                return std::nullopt;
            }
            config.quality = it->second;
        } else if (arg == "-r" || arg == "--crf") {
            if (i + 1 >= argc || argv[i + 1][0] == '-') {
                std::cerr << "Error: Option " << arg << " requires a value" << std::endl;
                print_usage(argv[0]);
                return std::nullopt;
            }
            try {
                config.crf = std::stoi(argv[++i]);
            } catch (const std::exception&) {
                std::cerr << "Error: Invalid CRF value" << std::endl;
                return std::nullopt;
            }
        } else if (arg == "-y" || arg == "--overwrite") {
            config.overwrite = true;
        } else if (arg == "-v" || arg == "--verbose") {
            config.verbose = true;
        } else if (arg[0] != '-') {
            positional_args.push_back(arg);
        } else {
            std::cerr << "Error: Unknown option: " << arg << std::endl;
            print_usage(argv[0]);
            return std::nullopt;
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
