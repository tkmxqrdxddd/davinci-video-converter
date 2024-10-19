#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <filesystem>

class VideoConverter {
public:
    void startConversion(const std::string &inputFile, const std::string &outputFile);

private:
    bool conversionInProgress = false;
};

void VideoConverter::startConversion(const std::string &inputFile, const std::string &outputFile) {
    if (conversionInProgress) {
        std::cerr << "Error: Conversion already in progress." << std::endl;
        return;
    }

    if (inputFile.empty()) {
        std::cerr << "Error: Please provide an input file name." << std::endl;
        return;
    }

    // Determine the output path
    std::filesystem::path outputPath;
    if (outputFile.empty()) {
        // If no output file is specified, create one in the current directory
        outputPath = std::filesystem::current_path() / (std::filesystem::path(inputFile).stem().string() + ".mov");
    } else {
        outputPath = std::filesystem::path(outputFile);
        if (outputPath.extension() != ".mov") {
            outputPath += ".mov";
        }
    }

    conversionInProgress = true;
    std::cout << "Starting conversion..." << std::endl;

    std::thread([this, inputFile, outputPath]() {
        std::string command = "ffmpeg -i \"" + inputFile + "\" -c:v dnxhd -profile:v dnxhr_hq -pix_fmt yuv422p -c:a alac \"" + outputPath.string() + "\" 2> /dev/null";
        int result = std::system(command.c_str());
        conversionInProgress = false;

        if (result == 0) {
            std::cout << "Video conversion completed successfully." << std::endl;
        } else {
            std::cerr << "Error: Conversion failed with exit code " << result << std::endl;
        }
    }).detach();
}

void printHelp() {
    std::cout << "Usage: davinci-convert /path/to/video [--output /path/to/output/folder]\n";
    std::cout << "Options:\n";
    std::cout << "  /path/to/video        Path to the input video file.\n";
    std::cout << "  --output /path/to/output/folder Path to the output video file (optional).\n";
    std::cout << "  --help                Show this help message.\n";
}

int main(int argc, char *argv[]) {
    VideoConverter converter;
    std::string inputFile, outputFile;

    if (argc < 2) {
        printHelp();
        return 1;
    }

    // The first argument is the input file
    inputFile = argv[1];

    // Parse the remaining arguments
    for (int i = 2; i < argc; i++) {
        if (std::strcmp(argv[i], "--output") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (std::strcmp(argv[i], "--help") == 0) {
            printHelp();
            return 0;
        } else {
            std::cerr << "Unknown option: " << argv[i] << std::endl;
            printHelp();
            return 1;
        }
    }

    converter.startConversion(inputFile, outputFile);

    // Keep the application running until the conversion is done
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
