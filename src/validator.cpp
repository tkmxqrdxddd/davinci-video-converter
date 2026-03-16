#include "validator.hpp"
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

bool validate_config(const Config& config, std::string& error) {
    if (config.input_path.empty()) {
        error = "Input path is required";
        return false;
    }
    
    if (config.output_path.empty()) {
        error = "Output path is required";
        return false;
    }
    
    if (!fs::exists(config.input_path)) {
        error = "Input file does not exist: " + config.input_path;
        return false;
    }
    
    const std::vector<std::string> valid_codecs = {"h264", "h265", "prores"};
    if (std::find(valid_codecs.begin(), valid_codecs.end(), config.codec) == valid_codecs.end()) {
        error = "Invalid codec: " + config.codec + ". Valid options: h264, h265, prores";
        return false;
    }
    
    const std::vector<std::string> valid_qualities = {"fast", "medium", "slow"};
    if (std::find(valid_qualities.begin(), valid_qualities.end(), config.quality) == valid_qualities.end()) {
        error = "Invalid quality preset: " + config.quality + ". Valid options: fast, medium, slow";
        return false;
    }
    
    if (config.crf < 0 || config.crf > 51) {
        error = "CRF must be between 0 and 51";
        return false;
    }
    
    return true;
}
