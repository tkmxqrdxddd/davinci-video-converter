{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "davinci-video-converter";
  
  buildInputs = with pkgs; [
    gcc13
    make
    ffmpeg
    pkg-config
  ];
  
  shellHook = ''
    export CXX=g++
    export CC=gcc
    echo "DaVinci Video Converter development environment loaded"
    echo "Available commands:"
    echo "  make        - Build the project"
    echo "  make clean  - Clean build artifacts"
    echo "  make test   - Run tests"
  '';
}
