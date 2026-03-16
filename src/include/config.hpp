#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

struct Config {
    std::string input_path;
    std::string output_path;
    std::string codec = "h264";
    std::string quality = "medium";
    int crf = 23;
    bool verbose = false;
};

#endif // CONFIG_HPP
