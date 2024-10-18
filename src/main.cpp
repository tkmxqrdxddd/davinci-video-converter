#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>

class VideoConverter {
private:
    bool conversionInProgress;

public:
    VideoConverter() : conversionInProgress(false) {}

    void startConversion(const std::string &inputFile, const std::string &outputFile) {
        if (conversionInProgress) {
            std::cerr << "Error: Conversion already in progress." << std::endl;
            return;
        }

        if (inputFile.empty() || outputFile.empty()) {
            std::cerr << "Error: Please enter both input and output file names." << std::endl;
            return;
        }

        conversionInProgress = true;
        std::cout << "Starting conversion..." << std::endl;

        std::thread conversionThread([this, inputFile, outputFile]() {
            std::string command = "ffmpeg -i \"" + inputFile + "\" -c:v dnxhd -profile:v dnxhr_hq -pix_fmt yuv422p -c:a alac \"" + outputFile + "\"";
            int result = std::system(command.c_str());
            conversionInProgress = false;

            if (result == 0) {
                std::cout << "Video conversion completed successfully." << std::endl;
            } else {
                std::cerr << "Error: Conversion failed with exit code " << result << std::endl;
            }
        });

        conversionThread.detach(); // Detach the thread to allow it to run independently
    }
};

int main() {
    VideoConverter converter;
    std::string inputFile, outputFile;

    std::cout << "Welcome to the Video Converter!" << std::endl;
    std::cout << "Enter the input file path: ";
    std::getline(std::cin, inputFile);
    std::cout << "Enter the output file path: ";
    std::getline(std::cin, outputFile);

    converter.startConversion(inputFile, outputFile);

    // Keep the application running until the conversion is done
    std::cout << "Press Enter to exit..." << std::endl;
    std::cin.get();

    return 0;
}
