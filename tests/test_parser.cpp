#include "parser.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Parse --version", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"--version", nullptr};
    auto result = parse_arguments(2, args, help_requested);
    REQUIRE_FALSE(result.has_value());
    REQUIRE(help_requested == true);
}

TEST_CASE("Parse --help", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"--help", nullptr};
    auto result = parse_arguments(2, args, help_requested);
    REQUIRE_FALSE(result.has_value());
    REQUIRE(help_requested == true);
}

TEST_CASE("Parse default values", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"input.mp4", (char*)"output.mp4", nullptr};
    auto result = parse_arguments(3, args, help_requested);
    REQUIRE(result.has_value());
    Config config = *result;

    REQUIRE(config.input_path == "input.mp4");
    REQUIRE(config.output_path == "output.mp4");
    REQUIRE(config.codec == Codec::h264);
    REQUIRE(config.quality == Quality::medium);
    REQUIRE(config.crf == 23);
    REQUIRE(config.verbose == false);
}

TEST_CASE("Parse short options with custom values", "[parser]") {
    bool help_requested = false;
    char* args[] = {
        (char*)"program", (char*)"input.mov", (char*)"output.mkv", (char*)"-c", (char*)"h265",
        (char*)"-q",      (char*)"slow",      (char*)"-r",         (char*)"18", (char*)"-v",
        nullptr};
    auto result = parse_arguments(10, args, help_requested);
    REQUIRE(result.has_value());
    Config config = *result;

    REQUIRE(config.input_path == "input.mov");
    REQUIRE(config.output_path == "output.mkv");
    REQUIRE(config.codec == Codec::h265);
    REQUIRE(config.quality == Quality::slow);
    REQUIRE(config.crf == 18);
    REQUIRE(config.verbose == true);
}

TEST_CASE("Parse --overwrite flag", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"in.mp4", (char*)"out.mp4", (char*)"-y", nullptr};
    auto result = parse_arguments(4, args, help_requested);
    REQUIRE(result.has_value());
    REQUIRE((*result).overwrite == true);
}

TEST_CASE("Parse long overwrite flag", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"in.mp4", (char*)"out.mp4", (char*)"--overwrite",
                    nullptr};
    auto result = parse_arguments(4, args, help_requested);
    REQUIRE(result.has_value());
    REQUIRE((*result).overwrite == true);
}

TEST_CASE("Parse long options with custom values", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"src.mp4",   (char*)"dst.mp4", (char*)"--codec",
                    (char*)"prores",  (char*)"--quality", (char*)"fast",    (char*)"--crf",
                    (char*)"28",      (char*)"--verbose", nullptr};
    auto result = parse_arguments(10, args, help_requested);
    REQUIRE(result.has_value());
    Config config = *result;

    REQUIRE(config.input_path == "src.mp4");
    REQUIRE(config.output_path == "dst.mp4");
    REQUIRE(config.codec == Codec::prores);
    REQUIRE(config.quality == Quality::fast);
    REQUIRE(config.crf == 28);
    REQUIRE(config.verbose == true);
}

TEST_CASE("Parse invalid codec returns error", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"in.mp4",        (char*)"out.mp4",
                    (char*)"-c",      (char*)"invalid_codec", nullptr};
    auto result = parse_arguments(5, args, help_requested);
    REQUIRE_FALSE(result.has_value());
    REQUIRE_FALSE(help_requested);
}

TEST_CASE("Parse missing option value returns error", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"in.mp4", (char*)"out.mp4", (char*)"-c", nullptr};
    auto result = parse_arguments(4, args, help_requested);
    REQUIRE_FALSE(result.has_value());
    REQUIRE_FALSE(help_requested);
}

TEST_CASE("Parse unknown option returns error", "[parser]") {
    bool help_requested = false;
    char* args[] = {(char*)"program", (char*)"in.mp4", (char*)"out.mp4", (char*)"--unknown",
                    nullptr};
    auto result = parse_arguments(4, args, help_requested);
    REQUIRE_FALSE(result.has_value());
    REQUIRE_FALSE(help_requested);
}
