#!/bin/bash

set -e

echo "Building DaVinci Video Converter..."

make clean
make

echo "Build complete! Binary: ./davinci-video-converter"
