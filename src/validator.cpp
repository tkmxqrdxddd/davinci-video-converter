#include "validator.hpp"
#include <filesystem>

namespace fs = std::filesystem;

std::optional<std::string> validate_config(const Config& config) {
    if (config.input_path.empty()) {
        return "Input path is required";
    }

    if (config.output_path.empty()) {
        return "Output path is required";
    }

    if (!fs::exists(config.input_path)) {
        return "Input file does not exist: " + config.input_path;
    }

    if (config.crf < 0 || config.crf > 51) {
        return "CRF must be between 0 and 51";
    }

    return std::nullopt;
}
