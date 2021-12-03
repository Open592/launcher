# Contributing to the launcher

## Introduction

Thank you for your interest in contributing to this project. Before contributing
please read through the [README](README.md) and familiarize yourself with the
purpose of this application.

## Building the project

This project is built similar to any other C++ project which uses CMAKE as it's
build system.

In order to build the project I recommend following the following steps:

```bash
# From the root directory of the project
mkdir build; cd build
cmake ../
make
# You should now have an executable within the "bin" directory
./bin/launcher
```

## Launcher arguments

To allow for dynamically specifying the operator and game name, the launcher
requires two arguments to be passed when executing:
- [0] :: Operator Name :: Name of the game operator (Ex: jagex)
- [1] :: Game Name :: Name of the game (Ex: runescape)

### Example:

```bash
./bin/launcher jagex runescape
```

## `runescape.prm`

This project depends on a configuration file which specifies items which will
be passed along to the JVM when initializing it.

### History

In the original installer Jagex placed the configuration file in a directory
named `runescape` which lived one directory above where the resulting executable
was placed.

```bash
# Example of original location of exe/.prm
C:\Users\<USER_NAME>\AppData\Local\jagexlauncher\bin\JagexLauncher.exe
C:\Users\<USER_NAME>\AppData\Local\jagexlauncher\runescape\runescape.prm
```

### Location

For Open592 the location of the `.prm` file depends on a few things:
- The dynamic operator and game name
- The platform we are running on

For our supported platform these will be the locations of the `.prm` file
(taking into account dynamic operator and game names)

```bash
# Windows
C:\Users\<USER_NAME>\AppData\Local\<OPERATOR_NAME>launcher\config\<GAME_NAME>.prm

# Linux/OSX
~/.config/<OPERATOR_NAME>launcher/<GAME_NAME>.prm
```

## Setting up your editor

Please make sure to have your editor set up with integrations for the following
applications:

- editorconfig
- clang-format

This will prevent you from creating pull requests which don't follow the style
conventions of the project.

## Making a pull request

We accept contributions to this project in the form of pull requests against
the `develop` branch.

Please before making a pull request, insure your branch is up to date with the
active `develop` branch.

```bash
git remote add upstream git@github.com:Open592/launcher.git
git fetch --all

# If required
git rebase upstream/develop
```

## Solutions to issues

### `error: invalid boolean`

An error similar to the one found below is the result of having an old version
of clang-format. I recommend upgrading to clang-format 13.

```bash
YAML:11:18: error: invalid boolean
AlignOperands:   DontAlign
                 ^~~~~~~~~
Error reading <DIR>launcher/src/.clang-format: Invalid argument
```
