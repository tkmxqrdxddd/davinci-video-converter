{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "davinci-video-converter";

  buildInputs = with pkgs; [
    gcc14
    cmake
    make
    ffmpeg
    pkg-config
    clang-tools
  ];

  shellHook = ''
    export CXX=g++
    export CC=gcc
    echo "DaVinci Video Converter development environment loaded"
    echo "Available commands:"
    echo "  cmake --preset debug   - Configure (Debug)"
    echo "  cmake --build build/debug  - Build"
    echo "  ctest --preset debug   - Run tests"
  '';
}
