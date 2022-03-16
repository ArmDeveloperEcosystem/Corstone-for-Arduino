#!/bin/bash -e

GREEN="\033[0;32m"
RESET="\e[0m"

ARDUINO_VERSION=1.8.19

echo -e "${GREEN}*** Installing Arduino IDE ... ***${RESET}"
curl -L -o /tmp/arduino-${ARDUINO_VERSION}-linux64.tar.xz https://downloads.arduino.cc/arduino-${ARDUINO_VERSION}-linux64.tar.xz
tar xfv /tmp/arduino-${ARDUINO_VERSION}-linux64.tar.xz -C ~/
pushd ~/arduino-${ARDUINO_VERSION}
sudo ./install.sh
popd

echo -e "${GREEN}*** Installing arduino-cli ... ***${RESET}"
mkdir -p ~/bin
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/bin sh

echo -e "${GREEN}*** Installing Arduino libraries ***${RESET}"
~/bin/arduino-cli lib install Ethernet Arduino_TensorFlowLite

echo -e "${GREEN}*** Building Open IoT SDK ***${RESET}"
git submodule init
git submodule update
pushd system
./build.sh
popd

echo -e "${GREEN}*** Linking Corstone for Arduino ***${RESET}"
mkdir -p ~/Arduino/hardware/arm
ln -sf $PWD ~/Arduino/hardware/arm/corstone

echo -e "${GREEN}*** Done! ***${RESET}"
