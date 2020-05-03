% Building a Bare Bones OS from Scratch

This is an attempt to build a simple bare bones OS from scratch. At least in the beginning of the project, it will follow along the tutorial <https://wiki.osdev.org/Bare_Bones>.  
The OS will be written for 32 bit i686 architecture.

# Development environment

Preceding the actual OS development is the setup of an suited development environment.

## Cross-Compiler

The development of an OS requires a working cross-compiler as not to link in any libs of the host system and so forth. The compiler to be used is GNU gcc. It has to be set up to cross compile C code for i686-elf.  
The host system compiler used dfor this project is ```gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0``` as of May 03 2020. The cross compiler is to be build for the i686-elf platform.

### Build dependencies

```
$ sudo apt install \
	build-essential \
	bison \
	flex \
	libgmp3-dev \
	libmpc-dev \
	libmpfr-dev \
	texinfo \
	libcloog-isl-dev \
	libisl-dev
```

#### Problems

```
Paketlisten werden gelesen... Fertig
Abhängigkeitsbaum wird aufgebaut.
Statusinformationen werden eingelesen.... Fertig
build-essential ist schon die neueste Version (12.4ubuntu1).
texinfo ist schon die neueste Version (6.5.0.dfsg.1-2).
texinfo wurde als manuell installiert festgelegt.
Einige Pakete konnten nicht installiert werden. Das kann bedeuten, dass
Sie eine unmögliche Situation angefordert haben oder, wenn Sie die
Unstable-Distribution verwenden, dass einige erforderliche Pakete noch
nicht erstellt wurden oder Incoming noch nicht verlassen haben.
Die folgenden Informationen helfen Ihnen vielleicht, die Situation zu lösen:

Die folgenden Pakete haben unerfüllte Abhängigkeiten:
 libcloog-isl-dev : Hängt ab von: libisl-0.18-dev soll aber nicht installiert werden
E: Probleme können nicht korrigiert werden, Sie haben zurückgehaltene defekte Pakete.
```

Tried to uninstall libisl* again and just install libcloog-isl-dev which seemed to work.  


### Sources

GCC: ftp://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-9.3.0/  
binutils: https://mirrors.ocf.berkeley.edu/gnu/binutils/  

### Preparation

```
$ export PREFIX="$HOME/bin/cross"
$ export TARGET=i686-elf
$ export PATH="$PREFIX/bin:$PATH"
```

### Building binutils

Directory structure:

```
/osdev/deps/binutils/binutils-x.xx.x
                    /binutils-build
           /gcc/gcc-x.xx.x
           /build-gcc
```

Building:

```
$ cd $HOME/lab/osdev/deps/binutils
 
$ mkdir build-binutils
$ cd build-binutils
$ ../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
$ make
$ make install
```

### Building GCC

The directory structure is the same as for building binutils.  
The actual build:  

```
$ cd $HOME/lab/osdev/deps/gcc

# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
$ which -- $TARGET-as || echo $TARGET-as is not in the PATH
 
$ mkdir build-gcc
$ cd build-gcc
$ ../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
$ make all-gcc
$ make all-target-libgcc
$ make install-gcc
$ make install-target-libgcc
```

## OS Source structure
```
boot.s		// kernel entry point, sets up processor environment
kernel.c	// actual kernel routines
linker.ld	// for linking the above files
```

## Booting the OS

For now I will not write a custom bootloader and use GRUB instead. For GRUB to recognize the kernel, a multiboot header has to be set up.  

## build.s

The file contains the code to be run right after the bootloader hands control to the custom kernel. Right now, it only contains:  

- the multiboot header nessecary for GRUB to recognize the kernel as multiboot compatible
- 16 KiB stack setup and the
- call to the kernel main function

When the kernels main function returns to this file, the system will halt.

## kernel.c

This file contains the actual kernel code, which cannot do much at this time. It is a freestanding C program and can not make use of commonly used  C libraries such as stdlib.h. It implementa a few simple routines to initialize the terminal and write strings to it via the VGA text mode buffer. This will have to be replaced eventually, as the VGA text mode buffer as well as the BIOS itself are pretty much deprecated at this point.

## linker.ld

This file contains a linker script describing the layout of the final OS binary.

# TODO

- Implement newline handling
- Implement scrolling
- refactor and restructure the project
