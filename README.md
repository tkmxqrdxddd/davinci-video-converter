# DaVinci Video Converter

A command-line video conversion tool optimized for DaVinci Resolve workflows.

## Features

- Convert videos using various codecs (H.264, H.265, ProRes)
- Quality presets for different use cases
- CRF-based quality control
- Overwrite protection
- Verbose output for debugging

## Development Environment

### DevContainer (Podman/Docker)

This project includes a DevContainer configuration for use with Podman or Docker. To use it:

1. Install the Dev Containers extension in VS Code
2. Configure VS Code to use Podman (optional):
   - Set `remote.containers.defaultDockerCommand` to `podman` in VS Code settings
3. Reopen the project in the container (Ctrl+Shift+P → "Dev Containers: Reopen in Container")

The container includes all necessary dependencies (g++, cmake, make, ffmpeg).

### Nix Shell

For Nix users, enter the development shell:

```bash
nix-shell
```

This provides a development environment with g++, cmake, make, and ffmpeg.

## Building

### Using CMake

```bash
# Debug build (with sanitizers)
cmake --preset debug
cmake --build build/debug

# Release build
cmake --preset release
cmake --build build/release
```

### Using build.sh

```bash
# Debug build (default)
./build.sh

# Release build
./build.sh release
```

## Usage

```bash
./build/debug/davinci-video-converter [options] <input> <output>
```

### Options

| Option | Description | Default |
|--------|-------------|---------|
| `-c, --codec <codec>` | Video codec (h264, h265, prores) | h264 |
| `-q, --quality <qual>` | Quality preset (fast, medium, slow) | medium |
| `-r, --crf <value>` | CRF value 0-51 | 23 |
| `-y, --overwrite` | Overwrite output file without asking | false |
| `-v, --verbose` | Enable verbose output | false |
| `-h, --help` | Show this help message | - |
| `--version` | Show version information | - |

### Examples

Convert with default settings:
```bash
./build/debug/davinci-video-converter input.mp4 output.mp4
```

Convert with H.265 codec and slow preset:
```bash
./build/debug/davinci-video-converter -c h265 -q slow input.mp4 output.mp4
```

Convert with custom CRF value:
```bash
./build/debug/davinci-video-converter -r 18 input.mp4 output.mp4
```

Overwrite output without prompting:
```bash
./build/debug/davinci-video-converter -y input.mp4 output.mp4
```

Verbose conversion:
```bash
./build/debug/davinci-video-converter -v input.mp4 output.mp4
```

## Testing

Run the unit tests:

```bash
cmake --preset debug
cmake --build build/debug
ctest --preset debug
```

## Installation

```bash
sudo cmake --install build/release
```

## Project Structure

```
davinci-video-converter/
├── .devcontainer/
│   └── devcontainer.json    # DevContainer configuration
├── .github/workflows/
│   ├── ci.yml               # CI pipeline
│   ├── release.yml          # Release pipeline
│   ├── security.yml         # Security scanning
│   └── build-deb.yml        # DEB packaging
├── src/
│   ├── include/
│   │   ├── config.hpp       # Configuration struct definition
│   │   ├── converter.hpp    # Converter module interface
│   │   ├── parser.hpp       # Argument parser interface
│   │   └── validator.hpp    # Validator module interface
│   ├── main.cpp             # Main entry point
│   ├── parser.cpp           # Argument parsing implementation
│   ├── validator.cpp        # Configuration validation
│   └── converter.cpp        # FFmpeg command building and execution
├── tests/
│   ├── CMakeLists.txt       # Test build configuration
│   ├── test_parser.cpp      # Parser unit tests
│   ├── test_validator.cpp   # Validator unit tests
│   └── test_converter.cpp   # Converter unit tests
├── CMakeLists.txt           # Build configuration
├── CMakePresets.json        # CMake presets (Debug/Release)
├── build.sh                 # Convenience build script
├── shell.nix                # Nix development environment
├── .clang-format            # Code formatting rules
├── .clang-tidy              # Static analysis rules
└── .editorconfig            # Editor configuration
```

## License

MIT
