#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include "config.hpp"
#include <string>

std::string build_ffmpeg_command(const Config& config);
int execute_conversion(const Config& config, bool verbose);

#endif // CONVERTER_HPP
