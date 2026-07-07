#include "converter.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("Build command with default settings", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    std::string command = build_ffmpeg_command(config);

    REQUIRE(command.find("ffmpeg") != std::string::npos);
    REQUIRE(command.find("-i \"input.mp4\"") != std::string::npos);
    REQUIRE(command.find("-c:v libx264") != std::string::npos);
    REQUIRE(command.find("\"output.mp4\"") != std::string::npos);
}

TEST_CASE("Build command with custom codec", "[converter]") {
    Config config;
    config.input_path = "input.mov";
    config.output_path = "output.mkv";

    SECTION("h265") {
        config.codec = Codec::h265;
        auto cmd = build_ffmpeg_command(config);
        REQUIRE(cmd.find("-c:v libx265") != std::string::npos);
    }

    SECTION("prores") {
        config.codec = Codec::prores;
        auto cmd = build_ffmpeg_command(config);
        REQUIRE(cmd.find("-c:v prores_ks") != std::string::npos);
    }
}

TEST_CASE("Build command includes CRF value", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.crf = 18;

    std::string command = build_ffmpeg_command(config);
    REQUIRE(command.find("-crf 18") != std::string::npos);
}

TEST_CASE("Build command includes quality preset", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    SECTION("fast") {
        config.quality = Quality::fast;
        REQUIRE(build_ffmpeg_command(config).find("-preset fast") != std::string::npos);
    }

    SECTION("medium") {
        config.quality = Quality::medium;
        REQUIRE(build_ffmpeg_command(config).find("-preset medium") != std::string::npos);
    }

    SECTION("slow") {
        config.quality = Quality::slow;
        REQUIRE(build_ffmpeg_command(config).find("-preset slow") != std::string::npos);
    }
}

TEST_CASE("Build command with verbose flag", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.verbose = true;

    std::string command = build_ffmpeg_command(config);
    REQUIRE(command.find("-loglevel verbose") != std::string::npos);
}

TEST_CASE("Build command includes audio copy", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    std::string command = build_ffmpeg_command(config);
    REQUIRE(command.find("-c:a copy") != std::string::npos);
}

TEST_CASE("Build command with overwrite flag", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";
    config.overwrite = true;

    std::string command = build_ffmpeg_command(config);
    REQUIRE(command.find(" -y ") != std::string::npos);
    REQUIRE(command.find("-y \"output.mp4\"") != std::string::npos);
}

TEST_CASE("Build command without overwrite does not include -y", "[converter]") {
    Config config;
    config.input_path = "input.mp4";
    config.output_path = "output.mp4";

    std::string command = build_ffmpeg_command(config);
    REQUIRE(command.find(" -y ") == std::string::npos);
}
