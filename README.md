# DaVinci Video Converter

A command-line video conversion tool optimized for DaVinci Resolve workflows.

## Features

- Convert videos using various codecs (H.264, H.265, ProRes)
- Quality presets for different use cases
- CRF-based quality control
- Verbose output for debugging

## Development Environment

### DevContainer (Podman)

This project includes a DevContainer configuration for use with Podman. To use it:

1. Install the Dev Containers extension in VS Code
2. Configure VS Code to use Podman:
   - Set `remote.containers.defaultDockerCommand` to `podman` in VS Code settings
3. Reopen the project in the container (Ctrl+Shift+P → "Dev Containers: Reopen in Container")

The container includes all necessary dependencies (g++, make, ffmpeg).

### Nix Shell

For Nix users, enter the development shell:

```bash
nix-shell
```

This provides a development environment with g++, make, and ffmpeg.

## Building

### Using Make

```bash
make
```

### Using build.sh

```bash
./build.sh
```

### Clean Build

```bash
make clean
```

## Usage

```bash
./davinci-video-converter [options] <input> <output>
```

### Options

| Option | Description | Default |
|--------|-------------|---------|
| `-c, --codec <codec>` | Video codec (h264, h265, prores) | h264 |
| `-q, --quality <qual>` | Quality preset (fast, medium, slow) | medium |
| `-r, --crf <value>` | CRF value 0-51 | 23 |
| `-v, --verbose` | Enable verbose output | false |
| `-h, --help` | Show help message | - |

### Examples

Convert with default settings:
```bash
./davinci-video-converter input.mp4 output.mp4
```

Convert with H.265 codec and slow preset:
```bash
./davinci-video-converter -c h265 -q slow input.mp4 output.mp4
```

Convert with custom CRF value:
```bash
./davinci-video-converter -r 18 input.mp4 output.mp4
```

Verbose conversion:
```bash
./davinci-video-converter -v input.mp4 output.mp4
```

## Testing

Run the built-in tests:

```bash
make test
```

## Installation

```bash
sudo make install
```

## Uninstallation

```bash
sudo make uninstall
```

## Project Structure

```
davinci-video-converter/
├── .devcontainer/
│   └── devcontainer.json    # DevContainer configuration for Podman
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
├── shell.nix                # Nix development environment
├── Makefile                 # Build configuration
├── build.sh                 # Build script
└── README.md
```

## License

MIT
