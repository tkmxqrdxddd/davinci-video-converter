#include "../src/include/converter.hpp"
#include <iostream>
#include <cassert>
#include <regex>

void test_build_command_basic() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("ffmpeg") != std::string::npos);
    assert(command.find("-i \"input.mp4\"") != std::string::npos);
    assert(command.find("-c:v libx264") != std::string::npos);
    assert(command.find("\"output.mp4\"") != std::string::npos);

    std::cout << "test_build_command_basic: PASSED" << std::endl;
}

void test_build_command_custom_codec() {
    Config config;
    config.input_path = "input.mov";
    config.output_path = "output.mkv";
    config.codec = "h265";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-c:v libx265") != std::string::npos);
    assert(command.find("-i \"input.mov\"") != std::string::npos);
    assert(command.find("\"output.mkv\"") != std::string::npos);

    std::cout << "test_build_command_custom_codec: PASSED" << std::endl;
}

void test_build_command_with_crf() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.crf = 18;

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-crf 18") != std::string::npos);

    std::cout << "test_build_command_with_crf: PASSED" << std::endl;
}

void test_build_command_quality_preset() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.quality = "slow";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-preset slow") != std::string::npos);

    std::cout << "test_build_command_quality_preset: PASSED" << std::endl;
}

void test_build_command_fast_quality() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.quality = "fast";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-preset fast") != std::string::npos);

    std::cout << "test_build_command_fast_quality: PASSED" << std::endl;
}

void test_build_command_medium_quality() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.quality = "medium";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-preset medium") != std::string::npos);

    std::cout << "test_build_command_medium_quality: PASSED" << std::endl;
}

void test_build_command_prores() {
    Config config;
    config.input_path = "input.mov";
    config.output_path = "output.mov";
    config.codec = "prores";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-c:v prores_ks") != std::string::npos);

    std::cout << "test_build_command_prores: PASSED" << std::endl;
}

void test_build_command_verbose() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.verbose = true;

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-loglevel verbose") != std::string::npos);

    std::cout << "test_build_command_verbose: PASSED" << std::endl;
}

void test_build_command_audio_copy() {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    std::string command = build_ffmpeg_command(config);

    assert(command.find("-c:a copy") != std::string::npos);

    std::cout << "test_build_command_audio_copy: PASSED" << std::endl;
}

int main() {
    std::cout << "=== Converter Tests ===" << std::endl;

    test_build_command_basic();
    test_build_command_custom_codec();
    test_build_command_with_crf();
    test_build_command_quality_preset();
    test_build_command_fast_quality();
    test_build_command_medium_quality();
    test_build_command_prores();
    test_build_command_verbose();
    test_build_command_audio_copy();

    std::cout << "All converter tests passed!" << std::endl;
    return 0;
}
