# ESORICS Tutorial: A Practical Introduction to Transient Execution Attacks

This repository contains all the practical parts of the tutorial, including the solutions. 
To ensure that you can run all the attacks on your system successfully, carefully read the requirements of the exercises. 

## Requirements
All of the provided frameworks contain Makefiles to build them. 
Therefore, a compiler toolchain (gcc, g++, ld, make) must be installed.

If no toolchain is installed, execute:

    sudo apt install build-essential

The first example provides an optional visualization of the histogram using Python and matplotlib. 
Therefore, make sure python3 and matplotlib is installed if you want to use the plot script:

    sudo apt install python3 python3-matplotlib

Except for ZombieLoad, all examples should work on any (modern) x86 CPU. 
They have been tested on Intel Core, Intel Xeon, and AMD Ryzen CPUs.
The ZombieLoad attack only works on Intel CPUs that are affected. 
Your CPU is affected if it reports `mds` as bug in `/proc/cpuinfo`:

    grep mds /proc/cpuinfo
    
The ZombieLoad attack further assumes that KASLR is disabled. 
While KASLR can be trivially broken using side-channel attacks, it makes the example easier to understand, more stable, and more difficult to weaponize. 
To disable KASLR, boot with `nokaslr` in your kernel command line. 
You can either edit that directly in the GRUB menu when booting, or using a tool such as [grub-customizer](https://launchpad.net/grub-customizer).

## Content

### Flush+Reload Histogram
Measure the access time of data that is cached and data that has to be fetched from main memory, and build a [histogram](https://en.wikipedia.org/wiki/Histogram). 

### Channel Encoding
Based on the timing differences from the first exercise, we can detect which part of a shared memory was accessed. 
We use that to covertly transmit data from one application to a second one by encoding it into the cache.
The cache encoding and decoding is an important part for all transient execution attacks. 

### Signals
For Meltdown-type attacks such as ZombieLoad, we need to suppress faults.
In this example, we show how we can suppress a segmentation fault and continue with the program.

### ZombieLoad
We mount a ZombieLoad attack that consists of all the parts from before: accessing an illegal address while suppressing faults, encoding the leaked data into the cache, and recovering it. 
The resulting attack leaks the values of loads and stores from any program on the sibling hyperthread.

### Spectre
In the last example, we implement a Spectre attack that mistrains the branch predictor to access inaccessible data. 
Again, the leaked data has to be encoded into the cache and then recovered from there.

## Building
Every example can be built by running

    make
    
To build the solution, run

    make solve



## Warnings
**Warning #1**: We are providing this code as-is. You are responsible for protecting yourself, your property and data, and others from any risks caused by this code. This code may cause unexpected and undesirable behavior to occur on your machine. 

**Warning #2**: This code is only for testing and educational purposes. Do not run it on any productive systems. Do not run it on any system that might be used by another person or entity.
