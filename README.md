# CLI
Command-Line Interpreter in C

## Purpose
The framework is designed to receive the user input and parse it to store the different arguments of the command-line in an array of pointer.

## Principle
The framework divides the arguments of the command-line using the blank spaces between them.

Arguments containing a blank space are recognized by the use of double quotes.

The arguments identified by the parser are then stored in an array of pointers. This array can be used in the application. 
