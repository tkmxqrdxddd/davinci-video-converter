#include "../src/include/validator.hpp"
#include <iostream>
#include <cassert>

void test_valid_config() {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";
    config.codec = "h264";
    config.quality = "medium";
    config.crf = 23;

    std::string error;
    bool result = validate_config(config, error);

    assert(result == true);
    assert(error.empty());

    std::cout << "test_valid_config: PASSED" << std::endl;
}

void test_missing_input() {
    Config config;
    config.input_path = "";
    config.output_path = "tests/output.mp4";

    std::string error;
    bool result = validate_config(config, error);

    assert(result == false);
    assert(!error.empty());

    std::cout << "test_missing_input: PASSED" << std::endl;
}

void test_missing_output() {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "";

    std::string error;
    bool result = validate_config(config, error);

    assert(result == false);
    assert(!error.empty());

    std::cout << "test_missing_output: PASSED" << std::endl;
}

void test_invalid_codec() {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";
    config.codec = "invalid_codec";

    std::string error;
    bool result = validate_config(config, error);

    assert(result == false);
    assert(!error.empty());

    std::cout << "test_invalid_codec: PASSED" << std::endl;
}

void test_invalid_quality() {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";
    config.quality = "ultra_invalid";

    std::string error;
    bool result = validate_config(config, error);

    assert(result == false);
    assert(!error.empty());

    std::cout << "test_invalid_quality: PASSED" << std::endl;
}

void test_crf_range() {
    // CRF too low
    Config config1;
    config1.input_path = "tests/input.mp4";
    config1.output_path = "tests/output.mp4";
    config1.crf = -1;

    std::string error1;
    assert(validate_config(config1, error1) == false);

    // CRF too high
    Config config2;
    config2.input_path = "tests/input.mp4";
    config2.output_path = "tests/output.mp4";
    config2.crf = 60;

    std::string error2;
    assert(validate_config(config2, error2) == false);

    std::cout << "test_crf_range: PASSED" << std::endl;
}

void test_valid_codecs() {
    const char* valid_codecs[] = {"h264", "h265", "prores"};

    for (const char* codec : valid_codecs) {
        Config config;
        config.input_path = "tests/input.mp4";
        config.output_path = "tests/output.mp4";
        config.codec = codec;

        std::string error;
        bool result = validate_config(config, error);
        assert(result == true);
    }

    std::cout << "test_valid_codecs: PASSED" << std::endl;
}

void test_valid_qualities() {
    const char* valid_qualities[] = {"fast", "medium", "slow"};

    for (const char* quality : valid_qualities) {
        Config config;
        config.input_path = "tests/input.mp4";
        config.output_path = "tests/output.mp4";
        config.quality = quality;

        std::string error;
        bool result = validate_config(config, error);
        assert(result == true);
    }

    std::cout << "test_valid_qualities: PASSED" << std::endl;
}

int main() {
    std::cout << "=== Validator Tests ===" << std::endl;
    
    test_valid_config();
    test_missing_input();
    test_missing_output();
    test_invalid_codec();
    test_invalid_quality();
    test_crf_range();
    test_valid_codecs();
    test_valid_qualities();
    
    std::cout << "All validator tests passed!" << std::endl;
    return 0;
}
