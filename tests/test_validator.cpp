#include <catch2/catch_test_macros.hpp>
#include "validator.hpp"

TEST_CASE("Valid config passes validation", "[validator]") {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";

    auto error = validate_config(config);
    REQUIRE_FALSE(error.has_value());
}

TEST_CASE("Missing input path fails validation", "[validator]") {
    Config config;
    config.input_path = "";
    config.output_path = "tests/output.mp4";

    auto error = validate_config(config);
    REQUIRE(error.has_value());
}

TEST_CASE("Missing output path fails validation", "[validator]") {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "";

    auto error = validate_config(config);
    REQUIRE(error.has_value());
}

TEST_CASE("CRF out of range fails validation", "[validator]") {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";

    SECTION("CRF below 0") {
        config.crf = -1;
        REQUIRE(validate_config(config).has_value());
    }

    SECTION("CRF above 51") {
        config.crf = 60;
        REQUIRE(validate_config(config).has_value());
    }

    SECTION("CRF at minimum boundary") {
        config.crf = 0;
        REQUIRE_FALSE(validate_config(config).has_value());
    }

    SECTION("CRF at maximum boundary") {
        config.crf = 51;
        REQUIRE_FALSE(validate_config(config).has_value());
    }
}

TEST_CASE("Non-existent input file fails validation", "[validator]") {
    Config config;
    config.input_path = "tests/nonexistent.mp4";
    config.output_path = "tests/output.mp4";

    auto error = validate_config(config);
    REQUIRE(error.has_value());
}

TEST_CASE("All valid codecs pass validation", "[validator]") {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";

    SECTION("h264") {
        config.codec = Codec::h264;
        REQUIRE_FALSE(validate_config(config).has_value());
    }

    SECTION("h265") {
        config.codec = Codec::h265;
        REQUIRE_FALSE(validate_config(config).has_value());
    }

    SECTION("prores") {
        config.codec = Codec::prores;
        REQUIRE_FALSE(validate_config(config).has_value());
    }
}

TEST_CASE("All valid qualities pass validation", "[validator]") {
    Config config;
    config.input_path = "tests/input.mp4";
    config.output_path = "tests/output.mp4";

    SECTION("fast") {
        config.quality = Quality::fast;
        REQUIRE_FALSE(validate_config(config).has_value());
    }

    SECTION("medium") {
        config.quality = Quality::medium;
        REQUIRE_FALSE(validate_config(config).has_value());
    }

    SECTION("slow") {
        config.quality = Quality::slow;
        REQUIRE_FALSE(validate_config(config).has_value());
    }
}
