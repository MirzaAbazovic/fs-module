# How to make executable from c code 

Compiling C programs requires you to work with four kinds of files:

* Regular source code files. These files contain function definitions, and have names which end in ".c" by convention.

* Header files. These files contain function declarations (also known as function prototypes) and various preprocessor statements. They are used to allow source code files to access externally-defined functions. Header files end in ".h" by convention.

* Object files. These files are produced as the output of the compiler. They consist of function definitions in binary form, but they are not executable by themselves. Object files end in ".o" by convention, although on some operating systems (e.g. Windows, MS-DOS), they often end in ".obj".

* Binary executables. These are produced as the output of a program called a "linker". The linker links together a number of object files to produce a binary file which can be directly executed. Binary executables have no special suffix on Unix operating systems, although they generally end in ".exe" on Windows.

There are other kinds of files as well, notably **libraries** (".a" files) and **shared libraries** (".so" files), but you won't normally need to deal with them directly.

Simle example in hello folder with one source file.

```bash
cd hello
gcc -o hello hello.c
./hello
```
Process of creating executable or library:

![Compilation process](images/GCC_CompilationProcess.png)

## Prepocessor

Before the C compiler starts compiling a source code file, the file is processed by a preprocessor.
 
 This is in reality a separate program (normally called "cpp", for "C preprocessor"), but it is invoked automatically by the compiler before compilation proper begins. 
 
 What the preprocessor does is **convert the source code file you write into another source code file (you can think of it as a "modified" or "expanded" source code file)**. That modified file may exist as a real file in the file system, or it may only be stored in memory for a short time before being sent to the compiler.

```bash
cd hello
gcc -E hello.c
```

gcc -E only invokes the preprocessor without compiling or using the linker.

**Preprocessor commands start with the pound sign ("#").**

1. **#define** is used to define constants.

```c
 #define BIGNUM 1000000
 ```

2. **#include** is used to access function definitions defined outside of a source code file. For instance:

```c
#include <stdio.h>
```

Causes the preprocessor to paste the contents of <stdio.h> into the source code file at the location of the #include statement before it gets compiled. #include is almost always used to include header files, which are files which mainly contain function declarations and #define statements.
#include statements are thus the way to re-use previously-written code in your C programs.

## Compiler

Compilation: the compiler takes the pre-processor's output and produces an object file from it. This step doesn't create anything the user can actually run. 
The compiler merely produces the machine language instructions that correspond to the source code file that was compiled.
The compilation step is performed on each output of the preprocessor. The compiler parses the pure source code (now without any preprocessor directives) and converts it into assembly code. Then invokes underlying back-end(assembler in toolchain) that assembles that code into machine code producing actual binary file in some format(ELF, COFF, a.out, ...). This object file contains the compiled code (in binary form) of the symbols defined in the input. Symbols in object files are referred to by name.

Compilers usually let you stop compilation at this point. This is very useful because with it you can compile each source code file separately. The advantage this provides is that you don't need to recompile everything if you only change a single file.

The produced object files can be put in special archives called static libraries, for easier reusing later on.

It's at this stage that "regular" compiler errors, like syntax errors or failed overload resolution errors, are reported.
gcc -c <file-name>.c will produce <file-name>.o

```bash
cd hello
gcc -c hello.c
```

 This tells the compiler to run the preprocessor on the file foo.c and then compile it into the object code file foo.o. **The -c option means to compile the source code file into an object file but not to invoke the linker**. If your entire program is in one source code file, you can instead do this:

```bash
gcc -o hello.c
```

This tells the compiler to **run the preprocessor on foo.c, compile it and then link it to create an executable called hello**. The -o option states that the next word on the line is the name of the binary executable file (program). If you don't specify the -o, i.e. if you **just type gcc foo.c, the executable will be named a.out for silly historical reasons.**

 For instance, if you compile (but don't link) three separate files, you will have three object files created as output, each with the name <filename>.o or <filename>.obj. Each of these files **contains a translation of your source code file into a machine language file -- but you can't run them yet!** You need to **turn them into executables your operating system can use. That's where the linker comes in.**

## Linking

**The job of the linker is to link together a bunch of object files (.o files) into a binary executable.**

The linker is what produces the final compilation output from the object files the compiler produced. This **output can be either a shared (or dynamic) library (and while the name is similar, they haven't got much in common with static libraries mentioned earlier) or an executable**.

It links all the object files by **replacing the references to undefined symbols with the correct addresses**. Each of these symbols can be **defined in other object files or in libraries**. If they are defined in libraries other than the standard library, you need to tell the linker about them.

**Like the preprocessor, the linker is a separate program called ld**. Also like the preprocessor, the linker is invoked automatically for you when you use the compiler. The normal way of using the linker is as follows:

```bash
gcc main.o lib1.o lib2.o -o myprog
```

This line tells the compiler to link together three object files (main.o, lib1.o, and lib2.o) into a binary executable file named myprog.

At this stage the **most common errors are missing definitions or duplicate definitions**. The former means that either the definitions don't exist (i.e. they are not written), or that the object files or libraries where they reside were not given to the linker. The latter is obvious: the same symbol was defined in two different object files or libraries.


# Complex projects

When You have big/complex project you divide code into multiple files, simplest example is with 3 files: 
* main.c
* stack.c
* stack.h

**A common convention in C programs is to write a header file (with .h suffix) for each source file (.c suffix) that you link to your main source code.** The logic is that the .c source file contains all of the code and the header file contains the function prototypes, that is, just a declaration of which functions can be found in the source file.

This is done for libraries that are provided by others, sometimes only as compiled binary "blobs" (i.e. you can't look at the source code). Pairing them with plain-text header files allows you see what functions are defined, and what arguments they take (and return).

```bash
cd multiple-files
gcc -Wall main.c stack.c -o my-app
./my-app
```

Compiles BOTH files... and makes executable my-app.
-Wall enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros.

```bash
gcc -c main.c #turns main.c into main.o
gcc -c stack.c #turns stack.c into stack.o
gcc -o stacktest stack.o main.o #takes stack.o and main.o and makes “stacktest” out of them - Called LINKING
```

Disadvantage is if you have a LOT of .c files, then it becomes tedious AND slow!

## Make and Makefiles tools for building

In software development, Make is a build automation tool that automatically builds executable programs and libraries from source code by reading files called Makefiles which specify how to derive the target program.

Most often, the makefile directs Make on how to compile and link a program. A makefile works upon the principle that files only need recreating if their dependencies are newer than the file being created/recreated. The makefile is recursively carried out (with dependency prepared before each target depending upon them) until everything has been updated (that requires updating) and the primary/ultimate target is complete. These instructions with their dependencies are specified in a makefile. If none of the files that are prerequisites have been changed since the last time the program was compiled, no actions take place. For large software projects, using Makefiles can substantially reduce build times if only a few source files have changed.

Structure of ```Makefile```
target: prerequisites
<TAB> recipe

You tell the Makefile:
* What you want to make
* How it goes about making it
And it figures out
* What needs to be (re) compiled and linked
* What order to do it in
You just type “make”
**Makefiles can be HUGELY complex**

Example of simple Makefile

```bash
CC = gcc #what compiler to use 
CFLAGS = -Wall #which flags to use
LDFLAGS =  # which libraries to use
OBJFILES = stack.o main.o #which object files are part of final program
TARGET = stacktest # name of final program

all: $(TARGET)

$(TARGET): $(OBJFILES)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
    rm -f $(OBJFILES) $(TARGET) *~
```

Just type “make” it will figure out which .c files need to be recompiled and turned into .o files
* If the .c file is newer than the .o file or
* the .o file does not exist

Figures out if the program needs to be relinked
* If any of the .o files changed or
* If the program does not exist

Or type "make clean"
Deletes:
* all the .o files
- all the ~ files (from emacs)
* the program itself
Leaves:
* .c files
* .h files
* Makefile

If you want to run or update a task when certain files are updated, the make utility can come in handy. The make utility requires a file, Makefile (or makefile), which defines set of tasks to be executed. You may have used make to compile a program from source code. Most open source projects use make to compile a final executable binary, which can then be installed using make install.

The following makefile can compile all C programs by using variables, patterns, and functions.
```bash

# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects
.PHONY = all clean
CC = gcc                        # compiler to use
LINKERFLAG = -lm
SRCS := $(wildcard *.c)
BINS := $(SRCS:%.c=%)

all: ${BINS}

%: %.o
        @echo "Checking.."
        ${CC} ${LINKERFLAG} $< -o $@

%.o: %.c
        @echo "Creating object.."
        ${CC} -c $<

clean:
        @echo "Cleaning up..."
        rm -rvf *.o ${BINS}
```
For more info see https://www.gnu.org/software/make/manual/make.pdf



# Libraries

## Static library

## Dynamic library

# Visual Studio Code as IDE for c developement


# FreeSWITCH (FS)

## Build FS from source

## Write and use FS module 

References:

* https://medium.com/@meghamohan/everything-you-want-to-know-about-gcc-fa5805452f96
* http://courses.cms.caltech.edu/cs11/material/c/mike/misc/compiling_c.html
* https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf
* https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work
* https://en.wikipedia.org/wiki/Makefile
* https://en.wikipedia.org/wiki/Make_(software)
* https://opensource.com/article/18/8/what-how-makefile
* https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html
* https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
* https://www.gribblelab.org/CBootCamp/12_Compiling_linking_Makefile_header_files.html
* http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
* https://medium.com/@meghamohan/all-about-static-libraries-in-c-cea57990c495
* https://medium.com/@meghamohan/everything-you-need-to-know-about-libraries-in-c-e8ad6138cbb4
