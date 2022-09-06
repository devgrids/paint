# [Paint](https://github.com/devgrids/paint) 🚀

## Getting Started
Paint has a single dependency: cmake, which is used to generate platform-specific makefiles or project files. Start by cloning this repository, making sure to pass the --recursive flag to grab all the dependencies. If you forgot, then you can git submodule update --init instead.

```bash
git clone --recursive https://github.com/devgrids/paint.git
```
or
```bash
git clone https://github.com/devgrids/paint.git
git submodule update --init --recursive
```
## Build 🛠️
Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 17 2022" -B "build"
```
