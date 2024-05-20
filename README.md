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

## Functions

### `create()`

Creates a new doubly linked list and initializes it with a dummy node.

### `insertAtHead(DoublyList* list, int data)`

Inserts a new node with the given data at the head (beginning) of the doubly linked list.

### `insertAtTail(DoublyList* list, int data)`

Inserts a new node with the given data at the tail (end) of the doubly linked list.

### `printList(DoublyList* list)`

Prints the data of each node in the doubly linked list from the head to the tail.

### `readData(const char *filename, int *numValues)`

Reads integer data from a file and stores it in an array. Returns the array and the number of values read.

### `printData(const char *filename, int *values, int *numValues)`

Prints the values read from a file.

### `insertUniqueValues(DoublyList* list, int* values, int numValues)`

Inserts values from an array into the linked list. If a value already exists in the list, it moves that value to the front instead of inserting it again.

### `printHelp(const char* progName, const char* mode)`

Prints the help information for the tool.

### `interactiveMode(DoublyList* list)`

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