## Project

Recovery of images captured by a camera that are cut into UDP packet with a fictitious protocol.

## Deployment

Things to do to compile the code (I'm using Qt 5.11 on Ubuntu 18.04 LTS x64 on VirtualBox):

## Built With
* [Qt5](https://www.qt.io/) - The C++ library
* [Qt Creator](https://www.qt.io/download-qt-installer) - The Qt IDE

### Qt5 dependencies
* Install g++: sudo apt-get install build-essential
* Install generic font configuration library - runtime: sudo apt-get install libfontconfig1
* Install OpenGL libraries: sudo apt-get install mesa-common-dev libglu1-mesa-dev

### Qt5 + QtCreator
* [Qt Creator x64](http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run)
* [Qt Creator x86](http://download.qt.io/official_releases/online_installers/qt-unified-linux-x86-online.run)

## Installation
During the installation, check the boxes:
* Qt 5.11.0 (main option)
** Qt 5.11.0 - Desktop gcc 64(or 32)-bit and
** All Qt XX dependencies, Charts, ..., Script (All are not necessary, but not knowing the exercice, I don't take any risk)
* Tools (main option)
* Qt Creator 4.6.1 is mandatory but I prefer to note it too

If you have any problems with kits (consists of a set of values that define one environment, such as a device, compiler, Qt version, and debugger command to use, ...) declarations, please follow this link : https://doc.qt.io/qtcreator/creator-targets.html
