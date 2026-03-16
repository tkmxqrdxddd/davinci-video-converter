#include "converter.hpp"
#include <sstream>
#include <cstdlib>
#include <iostream>

std::string build_ffmpeg_command(const Config& config) {
    std::stringstream cmd;
    cmd << "ffmpeg -i \"" << config.input_path << "\"";
    
    if (config.codec == "h264") {
        cmd << " -c:v libx264";
    } else if (config.codec == "h265") {
        cmd << " -c:v libx265";
    } else if (config.codec == "prores") {
        cmd << " -c:v prores_ks";
    }
    
    cmd << " -preset " << config.quality;
    cmd << " -crf " << config.crf;
    cmd << " -c:a copy";
    
    if (config.verbose) {
        cmd << " -loglevel verbose";
    }
    
    cmd << " \"" << config.output_path << "\"";
    
    return cmd.str();
}

int execute_conversion(const std::string& command, bool verbose) {
    if (verbose) {
        std::cout << "Executing: " << command << std::endl;
    }
    
    int result = std::system(command.c_str());
    
    if (result != 0) {
        std::cerr << "Error: ffmpeg command failed with exit code " << result << std::endl;
        return 1;
    }
    
    return 0;
}
