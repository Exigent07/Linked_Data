# Command-Line Tool for Doubly Linked List Operations

## Overview

This command-line tool allows users to interact with a doubly linked list via a set of commands. It supports reading integer data from a file, printing the data, loading the data into a doubly linked list while handling duplicates, and other utility commands such as clearing the screen and displaying help.

## Usage

The tool can be run in two modes:
1. Interactive Mode
2. File Operation Mode

### Interactive Mode

In interactive mode, users can enter commands directly to manipulate the linked list and perform other operations.

#### Command to Start Interactive Mode

```sh
./doubleLinked.exe --interactive
```

or

```sh
./doubleLinked.exe -i
```

Once in interactive mode, the following commands are available:

- **help**: Displays the help information for interactive commands.
- **read**: Prompts the user to enter a filename and reads integer data from the file.
- **print**: Prints the data read from the file.
- **load**: Loads the data into the linked list, moving duplicates to the front.
- **clear**: Clears the screen.
- **quit / exit**: Exits the interactive mode.

### File Operation Mode

In file operation mode, the tool performs a specific action on the data read from the file and then exits.

#### Command to Start File Operation Mode

```sh
./doubleLinked.exe --file <filename> --action <action>
```

or

```sh
./doubleLinked.exe -f <filename> -a <action>
```

#### Actions

- **0**: Reads data from the file and prints it.
- **1**: Reads data from the file, loads it into the linked list, and then prints the list.

Handles interactive mode, allowing the user to enter commands to manipulate the linked list and perform other operations.

## Example Usage

### Starting Interactive Mode

```sh
./doubleLinked.exe --interactive
```

### Reading Data from a File and Printing It

```sh
./doubleLinked.exe --file data.txt --action 0
```

### Reading Data from a File and Loading It into the Linked List

```sh
./doubleLinked.exe --file data.txt --action 1
```

## Error Handling

The tool includes various error checks and will display appropriate error messages for issues such as insufficient arguments, failed file operations, and invalid commands.

## Notes

- The tool assumes the file contains integers separated by spaces.
- The linked list operations are optimized for handling duplicate values by moving duplicates to the front of the list.

```

Save this content to a file named `README.md`. This file provides a comprehensive guide to using the command-line tool, detailing its functionalities, commands, and error handling.