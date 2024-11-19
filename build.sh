#!/bin/bash

set -e  # Exit immediately if a command exits with a non-zero status
set -u  # Treat unset variables as an error when substituting
set -o pipefail  # Prevent errors in a pipeline from being masked

# Function to install dependencies for Debian-based systems
install_debian_dependencies() {
    echo "Installing dependencies for Debian-based systems..."
    sudo apt-get update
    sudo apt-get install -y build-essential ffmpeg || {
        echo "Failed to install dependencies for Debian-based systems."
        exit 1
    }
}

# Function to install dependencies for Red Hat-based systems
install_redhat_dependencies() {
    echo "Installing dependencies for Red Hat-based systems..."
    sudo dnf install -y gcc-c++ ffmpeg make || {
        echo "Failed to install dependencies for Red Hat-based systems."
        exit 1
    }
}

# Function to install dependencies for Arch Linux
install_arch_dependencies() {
    echo "Installing dependencies for Arch Linux..."
    sudo pacman -S --noconfirm base-devel ffmpeg || {
        echo "Failed to install dependencies for Arch Linux."
        exit 1
    }
}

# Function to install dependencies for openSUSE
install_opensuse_dependencies() {
    echo "Installing dependencies for openSUSE..."
    sudo zypper install -y gcc-c++ ffmpeg make || {
        echo "Failed to install dependencies for openSUSE."
        exit 1
    }
}

# Function to install dependencies for Alpine Linux
install_alpine_dependencies() {
    echo "Installing dependencies for Alpine Linux..."
    sudo apk add --no-cache g++ ffmpeg make || {
        echo "Failed to install dependencies for Alpine Linux."
        exit 1
    }
}

# Check the package manager and install dependencies accordingly
if [ -f /etc/debian_version ]; then
    install_debian_dependencies
elif [ -f /etc/redhat-release ]; then
    install_redhat_dependencies
elif [ -f /etc/arch-release ]; then
    install_arch_dependencies
elif [ -f /etc/os-release ]; then
    . /etc/os-release
    case "$ID" in
        opensuse*)
            install_opensuse_dependencies
            ;;
        alpine)
            install_alpine_dependencies
            ;;
        *)
            echo "Unsupported distribution: $ID. Please install the required packages manually."
            exit 1
            ;;
    esac
else
    echo "Unsupported distribution. Please install the required packages manually."
    exit 1
fi

# Build the project
echo "Building the project..."
make

# Check if the build was successful
if [ $? -eq 0 ]; then
    echo "Build completed successfully."
else
    echo "Build failed. Please check the output for errors."
    exit 1
fi

# Install the application
echo "Installing the application..."
make install

# Inform the user about the executable
echo "You can run the application using 'davinci-convert'"
