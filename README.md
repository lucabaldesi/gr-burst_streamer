# GNURadio burst streamer plugin

This code is a plugin for GNURadio. It provides a block, called _burst streamer_ able to mux your bursty streams with a zero source.

## Building and installing

```
mkdir build
cd build
cmake ..
make && make install
```

## Packaging

This plugin comes with packaging scripts for Arch Linux and Ubuntu.
**Warning**, the packaging scripts are very minimal and **do not** respect the packaging policies of neither Arch Linux nor Ubuntu.

Arch Linux:

```
cd deploy
makepkg -si
```

Ubuntu

```
cd deploy
./gr-burst_streamer.buildeb
```
