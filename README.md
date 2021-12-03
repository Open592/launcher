# Launcher
Cross platform JVM game launcher.

## Background

Being a browser based MMORPG, RuneScape was delivered, for a large majority of
it's early years, as an `<Applet />`. As the downsides of this approach became
apparent it became obvious that delivering the game as an executable which
users could run from their desktop was needed.

On 25 May 2010 the game client was officially released. This allowed users
to download and install RuneScape on their computer.

While Open592 intends to target the 592 revision of RuneScape, which came
before the game client's release, the inability to run `<Applet />`'s within
any modern browsers makes this project nessessary.

## Overview

### Arguments

The launcher only takes a single string argument which specifies which game is
being loaded. Within the code the only difference is the directory and filename
with which the launcher finds the `.prm` file. This in effect changes the
class-path and class which is loaded by the JVM.

### Launcher

The launcher was a very simple C++ based program which originally only ran on
Windows. All it did was 5 things:
  - Accept a string parameter specifying which game was being launched
  - Read parameters from a simple `.prm` file
  - Load the JVM
  - Pass the loaded parameters to the JVM
  - Read the Applet viewer class path from the parameters file
  - Pass the game parameter to the `main` method
  - Execute the `main` method of the Applet viewer

### `runescape.prm`

This is the settings file for the Launcher. Below is an explanation of the
options and their usage:

| Property | Description |
| --- | --- |
|`-Djava.class.path`| Class path to the Applet Viewer|
|`-Dsun.java2d.noddraw`| [Turn off the Java 2D system's use of DirectDraw and Direct3D completely](https://docs.oracle.com/javase/7/docs/technotes/guides/2d/flags.html#noddraw)|
|`-Djava.net.preferIPv4Stack`| Prefer IPv4 in cases where IPv6 is available.|
|`-Dcom.jagex.config`|URL of launcher configuration|
|`-Xmx128m`|Specify the java memory allocation pool max size|
|`jagexappletviewer`|The Applet viewer class|

### AppletViewer

The AppletViewer set up an environment where you could run simple `<Applet />`
based applications within a desktop environment.

A _currently incomplete_ list of features which the AppletViewer performed:
  - Handle hand-off from the launcher. (Which provides, along with JVM options, `com.jagex.config`, which points to a `.ws` file containing launcher parameters
  - Set the icon
  - Load the configuration from the website (currently 404's)
  - Load the `browsercontrol.dll` native library which handles the advertisment shown to the user
  - Load the `loader` JAR and execute it.