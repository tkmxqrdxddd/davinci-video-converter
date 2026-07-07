#!/bin/bash

set -e

BUILD_TYPE="${1:-debug}"

echo "Building DaVinci Video Converter ($BUILD_TYPE)..."

cmake --preset "$BUILD_TYPE"
cmake --build "build/$BUILD_TYPE"

echo "Build complete! Binary: ./build/$BUILD_TYPE/davinci-video-converter"
