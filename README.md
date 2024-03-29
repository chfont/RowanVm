# Rowan VM

Rowan is a small assembly language and virtual machine developed as a project intended for becoming familiar with implementing these technologies. The assembly language is very small, meaning that while you can implement many things, it is not always easy due to needing workarounds for some actions. In the future, I plan to extend the instruction set and virtual machine in order to support more common actions and optimize execution. 

#### Building / Installing

The only requirements for building the project is a C++ compiler supporting C++17, and CMake, for building the project. A separate CMake file is provided for the unit tests, and this has the additional requirement of GoogleTest/GTest, a C++ unit testing framework. 

To build, navigate to the directory containing the CMakeLists.txt file, and enter `cmake --build .` in a terminal or command prompt. This will attempt to compile the project, putting the executable in a folder called `bin`, in that same directory.

To assemble source code into a binary, the command syntax is `<ExecutableName> <FileName>`, where ExecutableName is the name of the compiled executable (rowan-asm by default), and FileName is the name of the source code file.
To run the virtual machine on a binary file, the command syntax is the same as above (default executable name is rowan-vm).

To run unit tests, simply run the executable built for unit tests, with no arguments.

#### Assembly Language

The assembly language is a small RISC-based language, emphasizing small, simple instructions. Comments are written as in other common assembly languages: `; A comment is a semicolon followed by text, going until the end of the line`.

```
;This is an example program, to show the syntax of the language
;A comprehensive language spec can be found in language.md

ldc ra 0  ; set register a to 0
ldc rb 10
ldc rc 1
LOOP:     ; This is a label
cjump le rb ra END
add ra rc
pr ra     ; Print ra to the screen
jump LOOP
END:
```

