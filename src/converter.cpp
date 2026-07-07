#include "converter.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unistd.h>
#include <sys/wait.h>

static std::string_view codec_to_ffmpeg(Codec codec) {
    switch (codec) {
        case Codec::h264:  return "libx264";
        case Codec::h265:  return "libx265";
        case Codec::prores: return "prores_ks";
    }
    return "libx264";
}

static std::string_view quality_to_preset(Quality quality) {
    switch (quality) {
        case Quality::fast:   return "fast";
        case Quality::medium: return "medium";
        case Quality::slow:   return "slow";
    }
    return "medium";
}

static std::vector<std::string> build_ffmpeg_args(const Config& config) {
    std::vector<std::string> args;
    args.reserve(18);

    args.push_back("ffmpeg");
    args.push_back("-i");
    args.push_back(config.input_path);

    args.push_back("-c:v");
    args.push_back(std::string(codec_to_ffmpeg(config.codec)));
    args.push_back("-preset");
    args.push_back(std::string(quality_to_preset(config.quality)));
    args.push_back("-crf");
    args.push_back(std::to_string(config.crf));
    args.push_back("-c:a");
    args.push_back("copy");

    if (config.verbose) {
        args.push_back("-loglevel");
        args.push_back("verbose");
    }

    if (config.overwrite) {
        args.push_back("-y");
    }

    args.push_back(config.output_path);

    return args;
}

std::string build_ffmpeg_command(const Config& config) {
    std::ostringstream cmd;
    cmd << "ffmpeg -i \"" << config.input_path << "\""
        << " -c:v " << codec_to_ffmpeg(config.codec)
        << " -preset " << quality_to_preset(config.quality)
        << " -crf " << config.crf
        << " -c:a copy";

    if (config.verbose) {
        cmd << " -loglevel verbose";
    }

    if (config.overwrite) {
        cmd << " -y";
    }

    cmd << " \"" << config.output_path << "\"";

    return cmd.str();
}

int execute_conversion(const Config& config, bool verbose) {
    auto args = build_ffmpeg_args(config);

    if (verbose) {
        std::cout << "Executing: " << build_ffmpeg_command(config) << std::endl;
    }

    std::vector<char*> argv;
    for (const auto& a : args) {
        argv.push_back(const_cast<char*>(a.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv.data());
        std::cerr << "Error: Failed to execute ffmpeg" << std::endl;
        _exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code != 0) {
                std::cerr << "Error: ffmpeg failed with exit code " << exit_code << std::endl;
                return 1;
            }
            return 0;
        }
        std::cerr << "Error: ffmpeg terminated abnormally" << std::endl;
        return 1;
    }
    std::cerr << "Error: fork failed" << std::endl;
    return 1;
}
