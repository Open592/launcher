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

The launcher only takes a single argument specifying the final location of the
`.prm` file. In the original code this was specified as a `game` argument, and
most likely supported launching their seperate games.

In Open592 we do not support multiple games, so this parameter is used purely
to support pointing to multiple seperate `.prm` files.

### Example:

```bash
# Using Linux platform as an example

# ~/.config/open592/game.prm
./bin/launcher game

# ~/.config/open592/game-test.prm
./bin/launcher game-test
```

## `runescape.prm`

This project depends on a configuration file which specifies items which will
be passed along to the JVM when initializing it.

### History

In the original installer Jagex placed the configuration file in a directory
named `runescape` which lived one directory above where the resulting executable
was placed.

```bash
# Original location of .exe
C:\Users\<USER_NAME>\AppData\Local\jagexlauncher\bin\JagexLauncher.exe

# Original location of .prm
C:\Users\<USER_NAME>\AppData\Local\jagexlauncher\runescape\runescape.prm
```

### Location

#### Windows

```bash
%LOCALAPPDATA%\open592\config\<PROFILE>.prm
```

#### OSX

```bash
~/Library/Application Support/open592/config/<PROFILE>.prm
```

#### Linux

For linux the final location of the configuration directory takes into account
a few user configurable environment variables.

If the user has specified `$XDG_CONFIG_HOME`
```bash
$XDG_CONFIG_HOME/open592/<PROFILE>.prm
```

If the user has not specified `$XDG_CONFIG_HOME`
```bash
$HOME/.config/open592/<PROFILE>.prm
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
