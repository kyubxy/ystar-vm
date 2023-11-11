# ystar-virtualmachine
> A stack based process virtual machine that executes yprime assembly 

*This project is part of a collection of projects that comprise the ystar project, read 
more about it [here](https://www.youtube.com/watch?v=dQw4w9WgXcQ)*.

## Overview
ystar-vm is a process virtual machine that uses stack based memory to run yprime
assembly on desktop computers. It stores all data as 32 bit integers and is
being written by someone who knows nothing about CPUs.

This individual project is comprised of both the actual virtual machine and a
GUI visualiser that displays internal information about the CPU.

There's also a [docs](https://www.youtube.com/watch?v=dQw4w9WgXcQ) folder that
might contain more useful information.

## Usage
Eventually, I'll build a compiler that can take plaintext yprime assembly or even
full ystar code that compiles into bytecode. For now you will have to refer to
the instruction table, write the integers in plaintext to a file and use 
`binarypacker.py` to encode the base 10 instructions to binary.

```
./tools/binarypacker.py inputfile bytecode.ybc
```

To run the bytecode, simply run the VM as follows

```
./yvm bytecode.ybc
```

To execute the assembly line by line, use the interactive flag `-i`

```
./yvm -i bytecode.ybc
```

Follow the on screen prompts to step through the code.

### Visualiser
Packaged with the virtual machine also is a GUI visualiser. This program displays
information such as the progam stack and all stack frames currently allocated.
Run the visualiser with the command

```
./yvmvis bytecode.ybc
```

### Dependencies
- SDL2 (only used by the visualiser)

## Compilation
This program uses make with gcc.

**Virtual machine**
```
make vm
```

**Visualiser** 
```
make vis
```
## Supported Environments
basically just linux but I'll probs also support windows and maybe mac when i feel like it. for now just use wsl lol