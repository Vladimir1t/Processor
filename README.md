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
- **String Sorting Utility**: Sorts strings in a text file. It is located in Onegin file.

---
## Modules
1. **Assembler Module**
   - **Assembler.cpp**: Converts assembly code into bytecode.
   - **Assembler.h**: Header file for the assembler module.

2. **CPU Module**
   - **CPU.cpp**: Executes the bytecode instructions.
   - **CPU.h**: Header file for the CPU module.
   - **Commands.h**: Defines the bytecode instructions and their numeric representations.

3. **Stack**
   - **Stack.h**: Implements a stack data structure.
   - **Stack.cpp**: Contains stack-related functions.

4. **Utility Functions**
   - **File_Size.cpp**: Calculates the size of a file.
   - **Onegin.h**: Implements string sorting utilities
     
---

## Files included 
1. **assembler.cpp**

   - This file contains the main functionality for assembling bytecode from source files.
   - It reads source files, divides text into strings, and creates bytecode based on defined commands.
   - It also handles error logging and file operations.
2. **assembler.h**

   - This header file contains structures and function declarations used by the assembler.
   - It includes definitions for registers, arguments, commands, and various modes for assembling bytecode.
3. **CPU.cpp**

   - The CPU module is responsible for executing the assembled bytecode.
   - It includes functions for executing commands such as PUSH, POP, ADD, SUB, DIV, MUL, and more.
   - It manages the CPU state, RAM memory, and executing instructions sequentially.
4. **CPU.h**

   - This header file contains declarations for the CPU module, including function prototypes and struct definitions.
   - It includes functions for CPU construction, destruction, executing commands, and managing memory.
5. **commands.h**

   - The commands header file defines all available commands for the Processor.
   - Each command has a unique identifier, such as PUSH, ADD, SUB, DIV, MUL, OUT, IN, POP, and more.
   - It includes the necessary structures and enums for handling commands.
6. **DSL.h**

   - This header file contains a Domain-Specific Language (DSL) for defining macros used in the Processor.
   - It defines macros for common tasks such as pushing and popping from the stack, math operations, jumps, and more.
   - These macros simplify the implementation of command execution.
7. **equation.txt, fib.txt, factorial.txt**
   - examples of executed programs.

---

## How to Compile
1. Ensure you have a C compiler installed (e.g., GCC).
2. Compile the modules separately (with Makefile):
   ```bash
   equation : Asm proc
	   Assembler\assembler.exe Programs\equation.txt Assembler\res_ass.txt
	   CPU\proc.exe
   fib : Asm proc
	   Assembler\assembler.exe Programs\fib.txt Assembler\res_ass.txt
	   CPU\proc.exe
   factorial : Asm proc
	   Assembler\assembler.exe Programs\factorial.txt Assembler\res_ass.txt
	   CPU\proc.exe
   
   proc : CPU\src\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp 
	   g++ -o CPU\proc CPU\src\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp
	
   Asm :  Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp 
	   g++ -o Assembler\assembler Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp
   ```
3. Each compilation will generate an executable file: `Assembler.exe`, `CPU.exe`.

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
