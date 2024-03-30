Below is the README file for the "Processor" C program, including information about the main program ("Processor"), an assembler program, a CPU program, a stack implementation, and some additional utility functions for file size handling and string sorting.

---

# Processor README

## Table of Contents
- [Overview](#overview)
- [Files Included](#files-included)
- [How to Compile](#how-to-compile)
- [Usage](#usage)
- [Additional Notes](#additional-notes)

---

## Overview
The "Processor" program is designed to execute bytecode instructions stored in a file. It consists of several modules:

- **Assembler**: Converts human-readable assembly code into bytecode.
- **CPU**: Executes the bytecode instructions.
- **Stack**: Implements a stack data structure used in the CPU.
- **File Size Utility**: Calculates the size of a file.
- **String Sorting Utility**: Sorts strings in a text file.

---

## Files Included
1. **Assembler Module**
   - **Assembler.cpp**: Converts assembly code into bytecode.
   - **Assembler.h**: Header file for the assembler module.

2. **CPU Module**
   - **CPU.cpp**: Executes the bytecode instructions.
   - **CPU.h**: Header file for the CPU module.
   - **Commands.h**: Defines the bytecode instructions and their numeric representations.

3. **Stack Module**
   - **Stack.h**: Implements a stack data structure.
   - **Stack.cpp**: Contains stack-related functions.

4. **Utility Functions**
   - **File_Size.cpp**: Calculates the size of a file.
   - **Onegin.h**: Implements string sorting utilities.

---

## How to Compile
1. Ensure you have a C compiler installed (e.g., GCC).
2. Compile the modules separately:
   ```bash
   gcc -o Assembler Assembler.cpp
   gcc -o CPU CPU.cpp
   gcc -o Stack Stack.cpp
   gcc -o File_Size File_Size.cpp
   ```
3. Each compilation will generate an executable file: `Assembler.exe`, `CPU.exe`, `Stack.exe`, and `File_Size.exe`.

---

## Usage
### Assembler
- Run the `Assembler` program:
  ```bash
  ./Assembler input_file.asm output_file.bin
  ```
  - `input_file.asm`: Assembly code file.
  - `output_file.bin`: Binary bytecode output file.

### CPU
- Run the `CPU` program:
  ```bash
  ./CPU
  ```
  - The CPU will execute the bytecode stored in `Log\result.txt`.

### Additional Utilities
- **Stack**: The stack module can be used in the CPU program for stack operations.
- **File Size**: Use the `File_Size` program to get the size of a file:
  ```bash
  ./File_Size file_name
  ```

---

## Additional Notes
- Ensure all necessary header files (`#include`) are correctly referenced in the source files.
- For debugging and error logging, check the log files generated:
  - `Log\error_assembler.txt`: Errors from the assembler.
  - `Log\error_CPU.txt`: Errors from the CPU.
  - `Log\error_file_stack.txt`: Errors from the stack module.
- Feel free to modify the source code to fit your specific requirements.

---

This README provides a brief overview and instructions for using the "Processor" program along with its modules. For more detailed information, refer to the individual source code files and their corresponding headers.
