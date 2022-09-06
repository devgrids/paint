# [Paint](https://github.com/devgrids/paint) 🚀

### Execute 🛠️

```bash
git clone --recursive https://github.com/devgrids/paint.git
```
or
```bash
git clone https://github.com/devgrids/paint.git
git submodule update --init --recursive
```
Now generate a project file or makefile for your platform. If you want to use a particular IDE, make sure it is installed; don't forget to set the Start-Up Project in Visual Studio or the Target in Xcode.

```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 17 2022" -B "build"
---