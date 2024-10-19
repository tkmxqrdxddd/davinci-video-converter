# Davinci Video Converter

This is a simple tool that converts your `.mp4` videos into a format that DaVinci Resolve uses on Linux. The application utilizes `ffmpeg` for video conversion.

## Features

- Convert `.mp4` videos to DNxHD format.
- Simple command-line interface for user input.

## Prerequisites

Before building and running the application, ensure you have the following installed:

- `g++` (GNU C++ Compiler)
- `make` (Build automation tool)
- `ffmpeg` (Multimedia framework for handling video, audio, and other multimedia files)

## Installation

### Using the Build Script

1. Clone the repository:
   ```bash
   git clone (https://github.com/tkmxqrdxddd/davinci-video-converter)
   cd davinci-video-converter
   ```

2. Run the build script to install dependencies and build the project:
   ```bash
   ./build.sh
   ```

   This script will automatically install the required dependencies based on your Linux distribution and build the project. It will also install the application to `/usr/bin`, making it accessible from anywhere.

### Manual Installation

If you prefer to install manually, follow these steps:

1. Install the required dependencies (if not already installed):
   - For Debian-based systems:
     ```bash
     sudo apt-get install -y build-essential ffmpeg
     ```
   - For Red Hat-based systems:
     ```bash
     sudo dnf install -y gcc-c++ ffmpeg make
     ```
   - For Arch Linux:
     ```bash
     sudo pacman -Syu --noconfirm base-devel ffmpeg
     ```
   - For openSUSE:
     ```bash
     sudo zypper install -y gcc-c++ ffmpeg make
     ```
   - For Alpine Linux:
     ```bash
     sudo apk add --no-cache g++ ffmpeg make
     ```

2. Build the project using `make`:
   ```bash
   make
   ```

   This will create an executable named `davinci-convert` in the `output` directory.

3. Install the application:
   ```bash
   make install
   ```

## Running the Program

To run the program, use the following command:

```bash
davinci-convert
```

### Usage

1. When prompted, enter the input file path of the `.mp4` video you want to convert.
2. Enter the desired output file path (including the filename and extension) for the converted video.
3. The program will start the conversion process. You will see messages indicating the progress.
4. Once the conversion is complete, you will receive a success message.

### Cleaning Up

To clean up the generated files (object files and the executable), run:
```bash
make clean
```

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request. Any contributions, bug reports, or feature requests are welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project uses `ffmpeg` for video conversion. For more information, visit the [FFmpeg website](https://ffmpeg.org/).
