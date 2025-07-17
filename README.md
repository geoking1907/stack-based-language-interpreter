# Stack-Based Language Interpreter
![CPP Version](https://img.shields.io/badge/C++-17%2B-blue)
![Tests](https://img.shields.io/badge/tests-passing-brightgreen)

This C++ program implements a simple stack-based interpreter that reads and executes a custom language. The interpreter supports basic stack operations, arithmetic calculations, I/O operations, and conditional jumps.

## Features
* Stack Operations: `push`, `pop`, `dup`, `swap`, `over`, `rot`, `top` (outputs the top value), `abs`
* Arithmetic Operations: `add`, `sub`, `mul`, `div`, `mod`
* I/O Commands: `write` (output strings/values), `read` (input numbers)
* Control Flow: Conditional jumps (`goto(=0)`, `goto(>0`), `goto(<0)`) and labels
* Program Structure: Support for labels and line-based execution

## Supported Instructions
| **Command**                 | **Description**                                   |
|-----------------------------|-------------------------------------------------|
| push `N`                    | Push integer `N` onto the stack                  |
| pop	                        | Remove top element from stack                   |
| dup	                        | Duplicate top stack element                     |
| swap	                       | Swap top two stack elements                     |
| over	                       | Copy second stack element to top                |
| rot	                        | Rotate top three elements (`c, b, a` → `b, a, c`)  |
| abs	                        | Replace top element with its absolute value     |
| add / sub / mul / div / mod | Arithmetic operations (uses top two elements)   |
| write `STR`	                  | Output string `STR` (supports multi-word strings) |
| read	                       | Read integer from stdin and push to stack       |
| top	                        | Print top element without popping               |
| goto(=0) `L`                | Jump to label `L` if top element `= 0`            |
| goto(>0) `L`                | Jump to label `L` if top element `> 0`             |
| goto(<0) `L`                | Jump to label `L` if top element `< 0`             |
| return	                     | Terminate program execution                     |
| LABEL:	                     | Define jump target (must end with colon)        |

## Usage
1. Compile the program
2. Create a program file (e.g., program.ssb):
```asm
read
abs
goto(=0) Gt

Loop:
push 2
sub
goto(=0) Gt
goto(>0) Loop
write "odd"
return

Gt:
write "even"
return
```
3. Run the interpreter passing `program.ssb` as an argument

## Requirements
* C++17 compatible compiler
* Standard Library headers: `<iostream>`, `<fstream>`, `<sstream>`, `<string>`, `<vector>`, `<map>`