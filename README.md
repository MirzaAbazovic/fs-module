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

## Prepocessor

Before the C compiler starts compiling a source code file, the file is processed by a preprocessor.
 
 This is in reality a separate program (normally called "cpp", for "C preprocessor"), but it is invoked automatically by the compiler before compilation proper begins. 
 
 What the preprocessor does is **convert the source code file you write into another source code file (you can think of it as a "modified" or "expanded" source code file)**. That modified file may exist as a real file in the file system, or it may only be stored in memory for a short time before being sent to the compiler.

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

 For instance, if you compile (but don't link) three separate files, you will have three object files created as output, each with the name <filename>.o or <filename>.obj. Each of these files contains a translation of your source code file into a machine language file -- but you can't run them yet! You need to turn them into executables your operating system can use. That's where the linker comes in.

## Linking

The linker is what produces the final compilation output from the object files the compiler produced. This **output can be either a shared (or dynamic) library (and while the name is similar, they haven't got much in common with static libraries mentioned earlier) or an executable**.

It links all the object files by **replacing the references to undefined symbols with the correct addresses**. Each of these symbols can be **defined in other object files or in libraries**. If they are defined in libraries other than the standard library, you need to tell the linker about them.

At this stage the **most common errors are missing definitions or duplicate definitions**. The former means that either the definitions don't exist (i.e. they are not written), or that the object files or libraries where they reside were not given to the linker. The latter is obvious: the same symbol was defined in two different object files or libraries.

# Complex projects

When You have big/complex project you divide code into multiple files, for example: 
main.c
stack.c
stack.h

# Build FreeSWITCH (FS) from source

# Write and use FS module
 

References:

* http://courses.cms.caltech.edu/cs11/material/c/mike/misc/compiling_c.html
* https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf
* https://stackoverflow.com/questions/6264249/how-does-the-compilation-linking-process-work