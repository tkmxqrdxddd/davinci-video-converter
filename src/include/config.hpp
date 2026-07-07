#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

enum class Codec { h264, h265, prores };
enum class Quality { fast, medium, slow };

struct Config {
    std::string input_path;
    std::string output_path;
    Codec codec = Codec::h264;
    Quality quality = Quality::medium;
    int crf = 23;
    bool verbose = false;
    bool overwrite = false;
};

#endif // CONFIG_HPP
